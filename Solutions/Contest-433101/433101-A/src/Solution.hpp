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
#ifndef GCJFRAMEWORK_SOLUTION_HPP_INCLUDED
#define GCJFRAMEWORK_SOLUTION_HPP_INCLUDED

#include <GCJFramework/Core/I_Solution.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_Module;

class Solution
:   public I_Solution
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_Solution implementation
    /// @{
public:
    virtual const std::string& getName() const;
    virtual bool validate() const;
    virtual bool execute(const std::string& _type) const;
    /// @}

    /// @name Solution implementation
    /// @{
public:
    void reset() const;
    bool execute(std::istream& _inputStream, std::ostream& _outputStream) const;
    std::istream& getInput(const std::string& _type) const;
    std::istream& getValidationInput() const;
    std::ostream& getOutput(const std::string& _type) const;
    /// @}

    /// @name 'Structors
    /// @{
public:
             Solution(I_Module* _pModule);
    virtual ~Solution();
    /// @}

    /// @name Member Variables
    /// @{
private:
    I_Module*               m_pModule;
    mutable std::istream*   m_pIs;
    mutable std::ostream*   m_pOs;
    /// @}

};  // class Solution

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_SOLUTION_HPP_INCLUDED
