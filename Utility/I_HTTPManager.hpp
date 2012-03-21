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
#ifndef GCJFRAMEWORK_I_HTTP_MANAGER_HPP_INCLUDED
#define GCJFRAMEWORK_I_HTTP_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class I_HTTPManager
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    class I_Request;
    class I_Response;

    typedef boost::shared_ptr<I_Request>    pRequest_type;
    typedef boost::shared_ptr<I_Response>   pResponse_type;
    /// @}

    /// @name I_HTTPManager interface
    /// @{
public:
    virtual pResponse_type get(const std::string& _host,
                               const std::string& _url,
                               pRequest_type _pRequest) = 0;

    virtual pResponse_type post(const std::string& _host,
                                const std::string& _url,
                                pRequest_type _pRequest) = 0;

    virtual pRequest_type createRequest() = 0;
    /// @}

    /// @name Inner Structures
    /// @{
public:
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    class I_Request
    :   public boost::noncopyable
    {
        /// @name Types
        /// @{
    public:
        /// @}

        /// @name I_Request interface
        /// @{
    public:
        /// @}

        /// @name 'Structors
        /// @{
    protected:
                 I_Request();
        virtual ~I_Request();
        /// @}

    };  // interface I_Request
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    class I_Response
    :   public boost::noncopyable
    {
        /// @name Types
        /// @{
    public:
        /// @}

        /// @name I_Response interface
        /// @{
    public:
        /// @}

        /// @name 'Structors
        /// @{
    protected:
                 I_Response();
        virtual ~I_Response();
        /// @}

    };  // interface I_Response
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    /// @}

    /// @name Static Methods
    /// @{
public:
    I_HTTPManager& getSingleton();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_HTTPManager();
    virtual ~I_HTTPManager();
    /// @}

};  // interface I_HTTPManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_I_HTTP_MANAGER_HPP_INCLUDED
