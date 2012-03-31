//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Google Code Jam Solution Framework
//
// Copyright (C) 2012 Matthew Alan Gray
//
//  This software is licensed as described in the file license.txt, which you
//  should have received as part of this distribution.
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the terms described in the file license.txt.
//
//  @author Matthew Alan Gray <mgray@hatboystudios.com>
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include "ModuleService.hpp"
#include "ModuleInfo.hpp"

#include "../I_Module.hpp"
#include "../I_ModuleInfo.hpp"
#include "../I_ModuleManager.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/log/trivial.hpp>
#include <boost/thread/locks.hpp>

#include <iostream>
#include <sstream>

#include <stddef.h>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ModuleService::ModuleService()
:   m_moduleIdx()
,   m_modules()
,   m_moduleMutex()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ModuleService::~ModuleService()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ModuleService::pModule_type
ModuleService::load(const std::string& _moduleName)
{
    boost::lock_guard<boost::mutex> guard(m_moduleMutex);

    ModuleNameIdx_type::iterator iter = m_moduleIdx.find(_moduleName);
    if(iter != m_moduleIdx.end())
    {
        // Increment the reference count
        m_modules[iter->second]->incrementReferences();

        // Return the
        return iter->second;
    }

    pModuleInfo_type pModuleInfo(new ModuleInfo);

    I_ModuleManager* pModuleManager = &I_ModuleManager::getSingleton();

    boost::filesystem::path modulePath;
    if(!pModuleManager->findPath(_moduleName, modulePath))
    {
        std::stringstream stream;
        stream << "Module " << _moduleName << " not found in defined module search paths.";
        BOOST_LOG_TRIVIAL(error) << stream.str();

        throw std::exception(stream.str().c_str());
    }

    pModuleInfo->setName(_moduleName);

#ifdef _WIN32
    I_ModuleInfo::ModuleHandle_type hModule = LoadLibraryA(modulePath.string().c_str());
#else
    BOOST_LOG_TRIVIAL(info) << "dlopen " << modulePath.string().c_str();
    I_ModuleInfo::ModuleHandle_type hModule = dlopen(modulePath.string().c_str(), RTLD_NOW | RTLD_GLOBAL);
#endif // _WIN32

    if (hModule == NULL)
    {
        std::stringstream stream;
        stream << "Error loading module " << modulePath.string()
#ifndef _WIN32
            << dlerror()
#else
            << ": The module is probably missing dependencies not on the path.  Use depends.exe to figure it out."
#endif
            ;

        BOOST_LOG_TRIVIAL(error) << stream.str();
        throw std::exception(stream.str().c_str());
    }

    pModuleInfo->setHandle(hModule);

    // Get the "getModule" procedure
#if   defined _WIN32
    FARPROC proc = GetProcAddress(hModule, "getModule");
#else
    void* proc = dlsym(hModule, "getModule");
#endif

    // Check to make sure the procedure exists
    if (proc)
    {
        // Convert the procedure type to the assumed type
#ifdef _WIN32
        I_Module::proc_ptr_type pRealProc = (I_Module::proc_ptr_type)proc;
#else
        I_Module::QUERY_MODULE_FUNCTION_PTR pRealProc = reinterpret_cast<I_Module::QUERY_MODULE_FUNCTION_PTR>(proc);
#endif

        // Execute the procedure to get the I_Module for this module.
        pModule_type pModule = &(pRealProc());

        // Set the reference count to 1
        pModuleInfo->incrementReferences();

        // Put it in the index
        m_moduleIdx[_moduleName] = pModule;

        // Put it in the cache
        m_modules[pModule] = pModuleInfo;

        // And return it.
        return pModule;
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Error getting procedure address in module " << modulePath.string();

        // Not found, so return NULL
        return NULL;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
ModuleService::unload(pModule_type _pModule)
{
    boost::lock_guard<boost::mutex> guard(m_moduleMutex);

    // Use _pModule to get the module info
    pModuleInfo_type pModuleInfo = m_modules[_pModule];

    // Decrement the reference
    // If the count is zero, get the handle and unload the library
    if( pModuleInfo->decrementReferences() == 0 )
    {
        std::string moduleName = pModuleInfo->getName();

        // Remove module from the index
        ModuleNameIdx_type::iterator moduleIndexIterator = m_moduleIdx.find(moduleName);
        m_moduleIdx.erase(moduleIndexIterator);

        // Physically unload module
        I_ModuleInfo::ModuleHandle_type hModule = pModuleInfo->getHandle();

#ifdef _WIN32
        if( !FreeLibrary(hModule) )
#else
        if( dlclose(hModule) )
#endif // _WIN32
        {
            std::stringstream stream;
            stream << "Error unloading module " << moduleName;
            BOOST_LOG_TRIVIAL(error) << stream.str();
            throw std::exception(stream.str().c_str());
        }

        // Remove module from the cache
        Modules_type::iterator moduleIterator = m_modules.find(_pModule);
        m_modules.erase(moduleIterator);
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
