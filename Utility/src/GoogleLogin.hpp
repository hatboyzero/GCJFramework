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
#ifndef GCJFRAMEWORK_GOOGLE_LOGIN_HPP_INCLUDED
#define GCJFRAMEWORK_GOOGLE_LOGIN_HPP_INCLUDED

#include "../I_GoogleLogin.hpp"

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class GCJUTILITY_DLL_LINK GoogleLogin
:   public I_GoogleLogin
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_GoogleLogin implementation
    /// @{
public:
    virtual pSession_type login(const std::string& _accountType,
                                const std::string& _user,
                                const std::string& _password,
                                const std::string& _service,
                                const std::string& _source,
                                bool _secure);
    virtual const boost::posix_time::ptime& getExpirationTime(const Session& _session);
    virtual bool hasExpired(const Session& _session);
    /// @}

    /// @name GoogleLogin implementation
    /// @{
public:
    const std::string& getAuthToken(const std::string& _accountType,
                                    const std::string& _user,
                                    const std::string& _password,
                                    const std::string& _service,
                                    const std::string& _source);
    const std::string& getCookie(const std::string& _host,
                                 const std::string& service,
                                 const std::string& _authToken,
                                 bool _secure);
    pSession_type populateSession(const std::string& _authToken,
                                  const std::string& _cookie);
    pSession_type parseCookie(const std::string& _cookie);
    /// @}

    /// @name 'Structors
    /// @{
public:
             GoogleLogin();
    virtual ~GoogleLogin();
    /// @}

    /// @name Member Variables
    /// @{
private:
    /// @}

};  // class GoogleLogin

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_GOOGLE_LOGIN_HPP_INCLUDED
