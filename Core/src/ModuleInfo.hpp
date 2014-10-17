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
#ifndef GCJFRAMEWORK_MODULE_INFO_HPP_INCLUDED
#define GCJFRAMEWORK_MODULE_INFO_HPP_INCLUDED

#include "../I_ModuleInfo.hpp"

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class ModuleInfo
:   public I_ModuleInfo
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ModuleInfo implementation
public:
    virtual void setName(const std::string _name);
    virtual std::string getName() const;

    virtual void setHandle(const ModuleHandle_type _handle);
    virtual ModuleHandle_type getHandle() const;

    virtual unsigned incrementReferences();
    virtual unsigned decrementReferences();
    /// @}

    /// @name 'Structors
    /// @{
public:
             ModuleInfo();
    virtual ~ModuleInfo();
    /// @}

    /// @name Member variables
    /// @{

    // Module name
    std::string         m_name;

    // Module handle
    ModuleHandle_type  m_hModule;

    // Module reference count
    unsigned            m_references;
    /// @}

};  // interface ModuleInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_MODULE_INFO_HPP_INCLUDED
