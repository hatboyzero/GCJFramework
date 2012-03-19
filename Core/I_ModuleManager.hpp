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
#ifndef GCJFRAMEWORK_I_MODULE_MANAGER_HPP_INCLUDED
#define GCJFRAMEWORK_I_MODULE_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>

#include <list>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_ModuleService;

class GCJCORE_DLL_LINK I_ModuleManager
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef boost::shared_ptr<I_ModuleService>  pService_type;
    /// @}

    /// @name I_ModuleManager interface
    /// @{
public:
    /// Load a module service
    virtual pService_type getService() = 0;

    /// Add a module search path
    virtual void addPath(const boost::filesystem::path& _modulePath) = 0;

    /// Drop a module search path
    virtual void dropPath(const boost::filesystem::path& _modulePath) = 0;

    /// Find module path if one exists
    virtual bool findPath(const std::string _moduleName, boost::filesystem::path &_modulePath) = 0;
    /// @}

    /// @name Static Instance
    /// @{
public:
    static I_ModuleManager& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ModuleManager();
    virtual ~I_ModuleManager();
    /// @}

};  // interface I_ModuleManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_I_MODULE_MANAGER_HPP_INCLUDED

