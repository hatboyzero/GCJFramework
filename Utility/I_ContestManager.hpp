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
#ifndef GCJFRAMEWORK_I_CONTEST_MANAGER_HPP_INCLUDED
#define GCJFRAMEWORK_I_CONTEST_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_Contest;

class GCJUTILITY_DLL_LINK I_ContestManager
:   public boost::noncopyable
{
    /// @name Forward Declarations
    /// @{
public:
    struct I_ContestVisitor;
    /// @}

    /// @name Types
    /// @{
public:
    typedef boost::shared_ptr<I_Contest>        pContest_type;
    typedef boost::shared_ptr<I_ContestManager> pContestManager_type;
    /// @}

    /// @name I_ContestManager interface
    /// @{
public:
    virtual bool setLocation(const boost::filesystem::path& _location) = 0;
    virtual bool loadContest(const std::string& _contestId) = 0;
    virtual pContest_type getContest(const std::string& _contestId) const = 0;
    virtual void getContests(I_ContestVisitor& _visitor) const = 0;
    /// @}

    /// @name Internal Structures
    /// @{
public:
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    struct I_ContestVisitor
    {
        virtual void begin() = 0;
        virtual void visit(pContest_type _pContest) = 0;
        virtual void end() = 0;
    };  // struct I_ContestVisitor
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    /// @}

    /// @name Static Methods
    /// @{
public:
    static pContestManager_type create();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_ContestManager();
    virtual ~I_ContestManager();
    /// @}

};  // interface ContestManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_CONTEST_MANAGER_HPP_INCLUDED
