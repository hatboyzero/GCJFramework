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
#ifndef GCJFRAMEWORK_HTTP_MANAGER_HPP_INCLUDED
#define GCJFRAMEWORK_HTTP_MANAGER_HPP_INCLUDED

#include "../I_HTTPManager.hpp"

#include <curl/curl.h>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class HTTPManager
:   public I_HTTPManager
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_HTTPManager implementation
    /// @{
public:
    virtual pResponse_type get(const std::string& _host,
                               const std::string& _url,
                               pRequest_type _pRequest);

    virtual pResponse_type post(const std::string& _host,
                                const std::string& _url,
                                pRequest_type _pRequest);

    virtual pRequest_type createRequest();
    /// @}

    /// @name HTTPManager implementation
    /// @{
public:
private:
    void init();
    void cleanup();
    /// @}

    /// @name Inner Structures
    /// @{
public:
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    class Request
    :   public I_Request
    {
        /// @name Types
        /// @{
    public:
        /// @}

        /// @name I_Request implementation
        /// @{
    public:
        /// @}

        /// @name Request implementation
        /// @{
    public:
        /// @}

        /// @name 'Structors
        /// @{
    public:
                 Request();
        virtual ~Request();
        /// @}

        /// @name Member Variables
        /// @{
    private:
        /// @}

    };  // class Request
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    class Response
    :   public I_Response
    {
        /// @name Types
        /// @{
    public:
        /// @}

        /// @name I_Response implementation
        /// @{
    public:
        /// @}

        /// @name Response implementation
        /// @{
    public:
        /// @}

        /// @name 'Structors
        /// @{
    public:
                 Response();
        virtual ~Response();
        /// @}

        /// @name Member Variables
        /// @{
    private:
        /// @}

    };  // class Response
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    /// @}

    /// @name 'Structors
    /// @{
public:
             HTTPManager();
    virtual ~HTTPManager();
    /// @}

    /// @name Member Variables
    /// @{
private:
    CURL*       m_pCurlHandle;
    /// @}

};  // class I_HTTPManager

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_HTTP_MANAGER_HPP_INCLUDED
