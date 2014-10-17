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
#ifndef GCJFRAMEWORK_I_MODULE_HPP_INCLUDED
#define GCJFRAMEWORK_I_MODULE_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <list>

#ifdef HOST_POSIX
#include <dlfcn.h>
#endif //HOST_POSIX

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

// Forward declarations
class I_Solution;

/// Base class for a loadable problem module
/// A solution DLL should implement one of these
class GCJCORE_DLL_LINK I_Module
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef boost::shared_ptr<I_Solution>    pSolution_type;

#ifdef HOST_WIN32
    typedef I_Module& (*proc_ptr_type)();
#elif HOST_POSIX
    typedef I_Module& (*QUERY_MODULE_FUNCTION_PTR)();
#else
#error Unsupported platform in I_Module.hpp
#endif
    /// @}

    /// @name I_Module interface
    /// @{
public:
    /// Gets the name of the solution provided by this module.
    /// @return The name of the solution provided by this module.
    virtual const std::string& getName() const = 0;

    /// Sets the root path of the solution provided by this module.
    /// @param[in] _path The root path of the solution provided by this module.
    virtual void setPath(const boost::filesystem::path& _path) = 0;

    /// Gets the root path of the solution provided by this module.
    /// @return The root path of the solution provided by this module.
    virtual const boost::filesystem::path& getPath() const = 0;

    /// Returns a solution.
    /// For now, Solutions are all considered singletons. The problem should
    /// normally not be created until getSolution is called, in case the solution
    /// isn't required.
    /// @return The solution instance.
    virtual pSolution_type getSolution() = 0;
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_Module();
    virtual ~I_Module();
    /// @}

};  // interface I_Module

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_I_MODULE_HPP_INCLUDED
