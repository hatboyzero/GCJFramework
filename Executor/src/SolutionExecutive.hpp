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
#ifndef GCJFRAMEWORK_SOLUTION_EXECUTIVE_HPP_INCLUDED
#define GCJFRAMEWORK_SOLUTION_EXECUTIVE_HPP_INCLUDED

#include <GCJFramework/Utility/I_Environment.hpp>
#include <GCJFramework/Utility/I_ContestManager.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/shared_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_Contest;

class SolutionExecutive
{
    /// @name Types
    /// @{
public:
    typedef boost::shared_ptr<I_Contest>    pContest_type;
    /// @}

    /// @name SolutionExecutive implementation
    /// @{
public:
    void run(const std::string& _solution, const std::string& _type, bool _validate);
private:
    void validate(pContest_type _pContest);
    /// @}

    /// @name 'Structors
    /// @{
public:
     SolutionExecutive(const boost::filesystem::path& _configPath);
    ~SolutionExecutive();
    /// @}
    
    /// @name Member Variables
    /// @{
private:
    boost::filesystem::path                 m_configPath;
    I_Environment::pEnvironment_type        m_pEnvironment;
    I_ContestManager::pContestManager_type  m_pContestManager;
    /// @}

};  // class SolutionExecutive

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_SOLUTION_EXECUTIVE_HPP_INCLUDED
