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
#ifndef GCJFRAMEWORK_MODULE_MANAGER_HPP_INCLUDED
#define GCJFRAMEWORK_MODULE_MANAGER_HPP_INCLUDED

#include "../I_ModuleManager.hpp"

#include <boost/shared_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Concrete implementation of I_ModuleManager
class ModuleManager
:   public I_ModuleManager
{
    /// @name Types
    /// @{
public:
    typedef std::list</*const*/ boost::filesystem::path>    ModulePaths_type;
    /// @}

    /// @name I_ModuleManager implementation
    /// @{
public:
    virtual pService_type getService();
    virtual void addPath(const boost::filesystem::path& _modulePath);
    virtual void dropPath(const boost::filesystem::path& _modulePath);
    virtual bool findPath(const std::string _moduleName, boost::filesystem::path &_modulePath);
    /// @}

    /// @name ModuleManager implementation
    /// @{
public:
    /// @}

    /// @name 'Structors
    /// @{
public:
             ModuleManager();
    virtual ~ModuleManager();
    /// @}

    /// @name Member variables
    /// @{
private:

    /// Module service
    pService_type       m_pModuleService;

    /// Module search paths
    ModulePaths_type    m_modulePaths;
    /// @}

};  // interface ModuleManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_MODULE_MANAGER_HPP_INCLUDED
