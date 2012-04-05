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
#include "HTTPManager.hpp"

#include <rapidjson/writer.h>
#include <rapidjson/genericwritestream.h>

#include <boost/log/trivial.hpp>
#include <boost/thread/locks.hpp>

#include <sstream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::HTTPManager()
:   m_pCurlHandle(NULL)
{
    try {
        init();
    } catch (std::exception& _e) {
        std::stringstream stream;
        stream << "Caught exception: " << _e.what();
        BOOST_LOG_TRIVIAL(error) << stream.str();
    } catch (...) {
        std::stringstream stream;
        stream << "Caught unknown exception.";
        BOOST_LOG_TRIVIAL(error) << stream.str();
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::~HTTPManager()
{
    try {
        cleanup();
    } catch (std::exception& _e) {
        std::stringstream stream;
        stream << "Caught exception: " << _e.what();
        BOOST_LOG_TRIVIAL(error) << stream.str();
    } catch (...) {
        std::stringstream stream;
        stream << "Caught unknown exception.";
        BOOST_LOG_TRIVIAL(error) << stream.str();
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::pResponse_type
HTTPManager::get(const std::string& _host,
                 const std::string& _url,
                 pRequest_type _pRequest)
{
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    struct Deleter
    {
        void
        operator()(I_Response* _pResponse)
        {
            Response* pResponse =
                dynamic_cast<Response*>(_pResponse);

            if (pResponse != NULL)
            {
                delete pResponse;
            }
        }
    };  // struct Deleter
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

    try
    {
        Response* pRawResponse = new Response();

        std::string encodedRequest = _pRequest->toPayloadString();
        curl_easy_setopt(m_pCurlHandle, CURLOPT_URL, (_host + _url + "?" + encodedRequest).c_str());
        curl_easy_setopt(m_pCurlHandle, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(m_pCurlHandle, CURLOPT_WRITEDATA, pRawResponse);
        CURLcode result = curl_easy_perform(m_pCurlHandle);

        return pResponse_type(pRawResponse, Deleter());
    } catch (std::exception& _e) {
        std::stringstream stream;
        stream << "Caught exception: " << _e.what();
        BOOST_LOG_TRIVIAL(error) << stream.str();
    } catch (...) {
        std::stringstream stream;
        stream << "Caught unknown exception.";
        BOOST_LOG_TRIVIAL(error) << stream.str();
    }

    return pResponse_type();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::pResponse_type
HTTPManager::post(const std::string& _host,
                  const std::string& _url,
                  pRequest_type _pRequest)
{
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    struct Deleter
    {
        void
        operator()(I_Response* _pResponse)
        {
            Response* pResponse =
                dynamic_cast<Response*>(_pResponse);

            if (pResponse != NULL)
            {
                delete pResponse;
            }
        }
    };  // struct Deleter
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

    try
    {
        Response* pRawResponse = new Response();

        curl_easy_setopt(m_pCurlHandle, CURLOPT_URL, (_host + _url).c_str());
        curl_easy_setopt(m_pCurlHandle, CURLOPT_POST, 1);
        curl_easy_setopt(m_pCurlHandle, CURLOPT_POSTFIELDS, _pRequest->toPayloadString().c_str());
        curl_easy_setopt(m_pCurlHandle, CURLOPT_WRITEDATA, pRawResponse);
        CURLcode result = curl_easy_perform(m_pCurlHandle);

        return pResponse_type(pRawResponse, Deleter());
    } catch (std::exception& _e) {
        std::stringstream stream;
        stream << "Caught exception: " << _e.what();
        BOOST_LOG_TRIVIAL(error) << stream.str();
    } catch (...) {
        std::stringstream stream;
        stream << "Caught unknown exception.";
        BOOST_LOG_TRIVIAL(error) << stream.str();
    }

    return pResponse_type();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::pResponse_type
HTTPManager::postFile(const std::string& _host,
                      const std::string& _url,
                      pRequest_type _pRequest,
                      const std::string& _name,
                      std::istream& _input)
{
    /// TODO Implement
    throw std::exception("Not implemented");
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::pRequest_type
HTTPManager::createRequest()
{
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    struct Deleter
    {
        void
        operator()(I_Request* _pRequest)
        {
            Request* pRequest =
                dynamic_cast<Request*>(_pRequest);

            if (pRequest != NULL)
            {
                delete pRequest;
            }
        }
    };  // struct Deleter
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

    return pRequest_type(
        new Request(),
        Deleter()
    );
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
HTTPManager::init()
{
    curl_global_init(CURL_GLOBAL_ALL);

    m_pCurlHandle = curl_easy_init();
    curl_easy_setopt(m_pCurlHandle, CURLOPT_WRITEFUNCTION, &HTTPManager::getResponse);
    curl_easy_setopt(m_pCurlHandle, CURLOPT_USERAGENT, "libcurl-agent/GCJFramework/0.1.0");

    curl_slist* pHeader = NULL;
    pHeader = curl_slist_append(pHeader, "Accept: application/xml,application/xhtml+xml,text/html,text/plain");
    pHeader = curl_slist_append(pHeader, "Accept-Encoding: gzip");
    pHeader = curl_slist_append(pHeader, "Accept-Language: en");
    pHeader = curl_slist_append(pHeader, "Accept-Charset: utf-8");
    curl_easy_setopt(m_pCurlHandle, CURLOPT_HTTPHEADER, pHeader);
    curl_easy_setopt(m_pCurlHandle, CURLOPT_HEADER, 1);
    curl_easy_setopt(m_pCurlHandle, CURLOPT_CAINFO, "cacert.pem");

}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
HTTPManager::cleanup()
{
    curl_easy_cleanup(m_pCurlHandle);
    curl_global_cleanup();
    m_pCurlHandle = NULL;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
std::size_t
HTTPManager::getResponse(void* _pData,
                         std::size_t _size,
                         std::size_t _nMemB,
                         void* _pUser)
{
    Response* pResponse = static_cast<Response*>(_pUser);

    std::size_t size = _size * _nMemB;
    pResponse->append(std::string((const char*)_pData, size));

    return size;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::Request::Request()
:   m_fields()
,   m_fieldsMutex()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::Request::~Request()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
HTTPManager::Request::setField(const std::string& _key, const std::string& _value)
{
    boost::lock_guard<boost::mutex> guard(m_fieldsMutex);

    m_fields[_key] = _value;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string
HTTPManager::Request::getField(const std::string& _key) const
{
    boost::lock_guard<boost::mutex> guard(m_fieldsMutex);

    Fields_type::const_iterator iter = m_fields.find(_key);
    if (iter != m_fields.end())
    {
        return iter->second;
    }

    std::stringstream stream;
    stream << "Field \"" << _key << "\" does not exist in request!";
    BOOST_LOG_TRIVIAL(warning) << stream.str();

    return std::string("");
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
HTTPManager::Request::getFields(I_FieldVisitor& _visitor) const
{
    boost::lock_guard<boost::mutex> guard(m_fieldsMutex);

    _visitor.begin();

    Fields_type::const_iterator iter = m_fields.begin();
    while (iter != m_fields.end())
    {
        _visitor.visit(iter->first, iter->second);
        iter++;
    }

    _visitor.end();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string
HTTPManager::Request::toPayloadString() const
{
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    class PayloadBuilder
    :   public I_FieldVisitor
    {
        /// @name Types
        /// @{
    public:
        /// @}

        /// @name I_FieldVisitor implementation
        /// @{
    public:
        virtual void begin()
        {
            m_separator = "";
        }

        virtual void visit(const std::string& _key, const std::string& _value)
        {
            std::stringstream stream;
            stream << m_separator << _key << "=" << _value;
            m_payload += stream.str();
            m_separator = "&";
        }

        virtual void end()
        {
        }
        /// @}

        /// @name 'Structors
        /// @{
    public:
        PayloadBuilder(std::string& _payload)
        :   m_payload(_payload)
        ,   m_separator()
        {
        }
        /// @}

        /// @name Member Variables
        /// @{
    private:
        std::string&    m_payload;
        std::string     m_separator;
        /// @}

    };  // class PayloadBuilder
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

    std::string payload;
    PayloadBuilder visitor(payload);
    getFields(visitor);

    return payload;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string
HTTPManager::Request::toJSONString() const
{
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    class JSONBuilder
    :   public I_FieldVisitor
    {
        /// @name Types
        /// @{
    public:
        /// @}

        /// @name I_FieldVisitor implementation
        /// @{
    public:
        virtual void begin()
        {
        }

        virtual void visit(const std::string& _key, const std::string& _value)
        {
            m_document[_key.c_str()].SetString(_value.c_str());
        }

        virtual void end()
        {
            std::stringstream stream;
            rapidjson::GenericWriteStream jsonGss(stream);
            rapidjson::Writer<rapidjson::GenericWriteStream> writer(jsonGss);
            m_document.Accept(writer);
            m_json = stream.str();
        }
        /// @}

        /// @name 'Structors
        /// @{
    public:
        JSONBuilder(std::string& _json)
        :   m_json(_json)
        ,   m_document()
        {
        }
        /// @}

        /// @name Member Variables
        /// @{
    private:
        std::string&        m_json;
        rapidjson::Document m_document;
        /// @}

    };  // class JSONBuilder
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

    std::string json;
    JSONBuilder visitor(json);
    getFields(visitor);

    return json;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::Response::Response()
:   m_response()
,   m_document()
,   m_documentMutex()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
HTTPManager::Response::~Response()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string
HTTPManager::Response::getField(const std::string& _key) const
{
    boost::lock_guard<boost::mutex> guard(m_documentMutex);

    if (!m_document[_key.c_str()].IsNull())
    {
        return m_document[_key.c_str()].GetString();
    }

    std::stringstream stream;
    stream << "Field \"" << _key << "\" does not exist in response!";
    BOOST_LOG_TRIVIAL(warning) << stream.str();

    return std::string("");
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
HTTPManager::Response::getFields(I_FieldVisitor& _visitor) const
{
    boost::lock_guard<boost::mutex> guard(m_documentMutex);

    _visitor.begin();

    rapidjson::Document::ConstMemberIterator iter = m_document.MemberBegin();
    while (iter != m_document.MemberEnd())
    {
        _visitor.visit(iter->name.GetString(), iter->value.GetString());
        iter++;
    }

    _visitor.end();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string
HTTPManager::Response::toString() const
{
    return m_response;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
HTTPManager::Response::append(const std::string& _data)
{
    m_response += _data;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
HTTPManager::Response::parse()
{
    if (m_document.Parse<0>(m_response.c_str()).HasParseError())
    {
        BOOST_LOG_TRIVIAL(info) << "Response is not parsable JSON";
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
