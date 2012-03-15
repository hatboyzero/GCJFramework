//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Google Code Jam Solution Framework
//
// Copyright (C) 2012 Matthew Alan Gray
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//  @author Matthew Alan Gray <mgray@hatboystudios.com>
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef GCJFRAMEWORK_I_MODULE_HPP_INCLUDED
#define GCJFRAMEWORK_I_MODULE_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>
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
/// A problem DLL should implement one of these
class GCJCORE_DLL_LINK I_Module
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef std::list<std::string>          SolutionNameCollection_type;
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
    /// Returns the names of the problems implemented by this module.
    virtual SolutionNameCollection_type& getSolutionNames() = 0;

    /// Returns a problem by name.
    /// For now, Solutions are all considered singletons. The problem should
    /// normally not be created until getSolution is called, in case the problem
    /// isn't required.
    /// @return The problem instance if the name is a valid problem name for this
    ///         module, otherwise an invalid boost::shared_ptr<> is returned.
    virtual pSolution_type getSolution(const std::string& _name) = 0;

    /// Destroys the problem.
    /// The framework will call this when it is finished with the problem.
    virtual void destroySolution(pSolution_type _pSolution) = 0;
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
