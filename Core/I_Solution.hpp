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
#ifndef GCJFRAMEWORK_I_SOLUTION_HPP_INCLUDED
#define GCJFRAMEWORK_I_SOLUTION_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>

#include <iostream>
#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

/// Base class for a solution object.
class GCJCORE_DLL_LINK I_Solution
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_Solution interface
    /// @{ 
public:
    /// Gets the name of the solution.
    /// @return The name of the solution.
    virtual const std::string& getName() const = 0;

    /// Validates the solution against the sample inputs and outputs
    /// for the associated problem.
    /// @return True if validation is successful, False otherwise.
    virtual bool validate() const = 0;

    /// Executes the solution against a specified input type.
    /// Typically "small" or "large"
    /// @param[in] Type of input - { "validation", "small", "large" }
    /// @return True if the execution is successful (but not necessarily
    ///         correct), False otherwise.
    virtual bool execute(const std::string& _type) const = 0;
    /// @}

    /// @{ 'Structors
protected:
             I_Solution();
    virtual ~I_Solution();
    /// @}

};  // interface I_Solution

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_I_SOLUTION_HPP_INCLUDED

