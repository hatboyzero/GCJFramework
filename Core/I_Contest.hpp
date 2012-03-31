//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Google Code Jam Contest Framework
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
#ifndef GCJFRAMEWORK_I_CONTEST_HPP_INCLUDED
#define GCJFRAMEWORK_I_CONTEST_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_Solution;

class GCJCORE_DLL_LINK I_Contest
:   public boost::noncopyable
{
    /// @name Forward Declarations
    /// @{
public:
    struct I_SolutionVisitor;
    /// @}

    /// @name Types
    /// @{
public:
    typedef boost::shared_ptr<I_Solution>   pSolution_type;
    /// @}

    /// @name I_Contest interface
    /// @{ 
public:
    virtual const std::string& getName() const = 0;
    virtual bool loadSolutions() = 0;
    virtual pSolution_type getSolution(const std::string& _name) = 0;
    virtual void getSolutions(I_SolutionVisitor& _visitor) const = 0;
    /// @}

    /// @name Inner Structures
    /// @{
public:
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    struct I_SolutionVisitor
    {
        virtual void begin() = 0;
        virtual void visit(const I_Solution& _solution) = 0;
        virtual void end() = 0;
    };  // interface I_SolutionVisitor
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    /// @}

    /// @{ 'Structors
protected:
             I_Contest();
    virtual ~I_Contest();
    /// @}

};  // interface I_Contest

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_I_CONTEST_HPP_INCLUDED

