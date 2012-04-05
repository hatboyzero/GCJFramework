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
#ifndef GCJFRAMEWORK_I_GOOGLE_LOGIN_HPP_INCLUDED
#define GCJFRAMEWORK_I_GOOGLE_LOGIN_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class GCJUTILITY_DLL_LINK I_GoogleLogin
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    struct Session;
    typedef boost::shared_ptr<Session>  pSession_type;
    /// @}

    /// @name GoogleLogin interface
    /// @{
public:
    virtual pSession_type login(const std::string& _accountType,
                                const std::string& _user,
                                const std::string& _password,
                                const std::string& _service,
                                const std::string& _source,
                                bool _secure) = 0;
    virtual const boost::posix_time::ptime& getExpirationTime(const Session& _session) = 0;
    virtual bool hasExpired(const Session& _session) = 0;
    /// @}

    /// @name Static methods
    /// @{
public:
    static I_GoogleLogin& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_GoogleLogin();
    virtual ~I_GoogleLogin();
    /// @}

};  // interface I_GoogleLogin

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_I_GOOGLE_LOGIN_HPP_INCLUDED
