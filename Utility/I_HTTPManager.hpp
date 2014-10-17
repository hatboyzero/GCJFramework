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
#ifndef GCJFRAMEWORK_I_HTTP_MANAGER_HPP_INCLUDED
#define GCJFRAMEWORK_I_HTTP_MANAGER_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class GCJUTILITY_DLL_LINK I_HTTPManager
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

    virtual pResponse_type postFile(const std::string& _host,
                                    const std::string& _url,
                                    pRequest_type _pRequest,
                                    const std::string& _name,
                                    std::istream& _input) = 0;

    virtual pRequest_type createRequest() = 0;
    /// @}

    /// @name Inner Structures
    /// @{
public:
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    struct I_FieldVisitor
    {
        virtual void begin() = 0;
        virtual void visit(const std::string& _key, const std::string& _value) = 0;
        virtual void end() = 0;
    };  // interface I_FieldVisitor
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
        virtual void setField(const std::string& _key, const std::string& _value) = 0;
        virtual const std::string getField(const std::string& _key) const = 0;
        virtual void getFields(I_FieldVisitor& _visitor) const = 0;
        virtual const std::string toPayloadString() const = 0;
        virtual const std::string toJSONString() const = 0;
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
        virtual const std::string getField(const std::string& _key) const = 0;
        virtual void getFields(I_FieldVisitor& _visitor) const = 0;
        virtual const std::string toString() const = 0;
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
    static I_HTTPManager& getSingleton();
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
