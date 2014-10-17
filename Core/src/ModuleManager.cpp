//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Google Code Jam Solution Framework
//
// Copyright (C) 2012-2014 Matthew Alan Gray
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
//  @author Matthew Alan Gray <matthew.alan.gray@gmail.com>
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#include "ModuleManager.hpp"
#include "ModuleService.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/log/trivial.hpp>

#include <iostream>
#include <sstream>

#include <stddef.h>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ModuleManager::ModuleManager()
:   m_pModuleService()
,   m_modulePaths()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ModuleManager::~ModuleManager()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
static boost::shared_ptr<I_ModuleService> sm_pModuleService;
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
I_ModuleManager::pService_type
ModuleManager::getService()
{
    if (sm_pModuleService.get() == NULL)
    {
        sm_pModuleService.reset(new ModuleService());
    }
    return sm_pModuleService;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
ModuleManager::addPath(const boost::filesystem::path& _modulePath)
{
    m_modulePaths.push_back(_modulePath);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
ModuleManager::dropPath(const boost::filesystem::path& _modulePath)
{
    ModulePaths_type::iterator iter;

    iter = m_modulePaths.begin();
    while( (*iter != _modulePath) &&
           (iter  != m_modulePaths.end()) )
    {
        iter++;
    }

    if( iter != m_modulePaths.end() )
        m_modulePaths.erase(iter);
    else
    {
        std::stringstream stream;
        stream << "Path " << _modulePath << " is not in the list of module search paths.";
        BOOST_LOG_TRIVIAL(error) << stream.str();

        throw std::exception(stream.str().c_str());
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
ModuleManager::findPath(const std::string _moduleName, boost::filesystem::path &_modulePath)
{
    bool modulePathFound = false;
    boost::filesystem::path modulePath;
    ModulePaths_type::iterator iter;

    if( m_modulePaths.empty() )
        return false;

    // Set the extension
    std::stringstream moduleName;

#if   defined _WIN32 || HOST_CYGWIN
    moduleName << _moduleName;
#ifdef _DEBUG
    moduleName << "_d";
#endif
    moduleName << ".dll";
#elif defined HOST_DARWIN
    moduleName << "lib" << _moduleName << ".dylib";
#else
    moduleName << "lib" << _moduleName << ".so";
#endif

    iter = m_modulePaths.begin();
    do
    {
        // Create the fully qualified path
        modulePath = *iter / boost::filesystem::path(moduleName.str());

        // Check if the path is valid
        modulePathFound = boost::filesystem::exists(modulePath);

        BOOST_LOG_TRIVIAL(info) << "Attempting " << modulePath.string();

        // Iterate path iterator
        iter++;

    }
    while( iter != m_modulePaths.end() &&
           !modulePathFound );

    if( modulePathFound )
    {
        _modulePath = modulePath;
        return true;
    }
    else
    {
        _modulePath = std::string("");
        return false;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

