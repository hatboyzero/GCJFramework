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
#ifndef GCJFRAMEWORK_MODULE_SERVICE_HPP_INCLUDED
#define GCJFRAMEWORK_MODULE_SERVICE_HPP_INCLUDED

#include "../I_ModuleInfo.hpp"
#include "../I_ModuleService.hpp"

#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>

#include <map>
#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class ModuleService
:   public I_ModuleService
{
    /// @name Types
    /// @{
public:
    typedef std::map<std::string, pModule_type>                         ModuleNameIdx_type;
    typedef boost::shared_ptr<I_ModuleInfo>                             pModuleInfo_type;
    typedef std::map<pModule_type, pModuleInfo_type>                    Modules_type;
    /// @}

    /// @name I_ModuleService implementation
    /// @{
public:
    virtual pModule_type load(const std::string& _moduleName);
    virtual void unload(pModule_type _pModule);
    /// @}

    /// @name 'Structors
    /// @{
public:
             ModuleService();
    virtual ~ModuleService();
    /// @}

    /// @name Member variables
    /// @{
private:
    ModuleNameIdx_type      m_moduleIdx;
    Modules_type            m_modules;
    boost::mutex            m_moduleMutex;
    /// @}

};  // interface ModuleService

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_MODULE_SERVICE_HPP_INCLUDED
