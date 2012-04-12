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
#ifndef GCJFRAMEWORK_CONTEST_MANAGER_HPP_INCLUDED
#define GCJFRAMEWORK_CONTEST_MANAGER_HPP_INCLUDED

#include "../I_ContestManager.hpp"

#include <boost/thread/mutex.hpp>

#include <map>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_Contest;

class ContestManager
:   public I_ContestManager
{
    /// @name ContestManager implementation
    /// @{
public:
    virtual bool setLocation(const boost::filesystem::path& _location);
    virtual bool loadContest(const std::string& _contestId);
    virtual bool generateContest(const std::string& _contestId);
    virtual pContest_type getContest(const std::string& _contestId) const;
    virtual void getContests(I_ContestVisitor& _visitor) const;
    /// @}

    /// @name 'Structors
    /// @{
public:
             ContestManager();
    virtual ~ContestManager();
    /// @}

    /// @name Member Variables
    /// @{
private:
    boost::filesystem::path         m_path;

    mutable boost::mutex            m_contestsMutex;
    typedef std::map<std::string,pContest_type> Contests_type;
    Contests_type                   m_contests;
    /// @}

};  // class ContestManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_CONTEST_MANAGER_HPP_INCLUDED
