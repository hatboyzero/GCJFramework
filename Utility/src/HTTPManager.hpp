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

#include <rapidjson/document.h>

#include <boost/thread/mutex.hpp>

#include <map>
#include <string>

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

    virtual pResponse_type postFile(const std::string& _host,
                                    const std::string& _url,
                                    pRequest_type _pRequest,
                                    const std::string& _name,
                                    std::istream& _input);

    virtual pRequest_type createRequest();
    /// @}

    /// @name HTTPManager implementation
    /// @{
public:
private:
    void init();
    void cleanup();

    static std::size_t getResponse(void* _pData, std::size_t _size, std::size_t _nMemB, void* _pUser);
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
        virtual void setField(const std::string& _key, const std::string& _value);
        virtual const std::string getField(const std::string& _key) const;
        virtual void getFields(I_FieldVisitor& _visitor) const;
        virtual const std::string toPayloadString() const;
        virtual const std::string toJSONString() const;
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
        typedef std::map<std::string, std::string>  Fields_type;
        Fields_type                 m_fields;
        mutable boost::mutex        m_fieldsMutex;
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
        virtual const std::string getField(const std::string& _key) const;
        virtual void getFields(I_FieldVisitor& _visitor) const;
        virtual const std::string toString() const;
        /// @}

        /// @name Response implementation
        /// @{
    public:
        void parse(const std::string& _json);
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
        std::string                 m_response;
        rapidjson::Document         m_document;
        mutable boost::mutex        m_documentMutex;
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
