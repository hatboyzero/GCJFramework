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
#ifndef GCJFRAMEWORK_I_MODULE_INFO_HPP_INCLUDED
#define GCJFRAMEWORK_I_MODULE_INFO_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>

#include <string>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class GCJCORE_DLL_LINK I_ModuleInfo
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
#if defined _WIN32
    typedef HMODULE     ModuleHandle_type;
#else
    typedef void*       ModuleHandle_type;
#endif // _WIN32
    /// @}

    /// @name I_ModuleInfo interface
    /// @{
public:
    virtual void setName(const std::string _name) = 0;
    virtual std::string getName() const = 0;

    virtual void setHandle(const ModuleHandle_type _handle) = 0;
    virtual ModuleHandle_type getHandle() const = 0;

    virtual unsigned incrementReferences() = 0;
    virtual unsigned decrementReferences() = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ModuleInfo();
    virtual ~I_ModuleInfo();
    /// @}

};  // interface I_ModuleInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_I_MODULE_INFO_HPP_INCLUDED
