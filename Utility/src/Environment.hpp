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
#ifndef GCJFRAMEWORK_ENVIRONMENT_HPP_INCLUDED
#define GCJFRAMEWORK_ENVIRONMENT_HPP_INCLUDED

#include "../I_Environment.hpp"

#include <rapidjson/document.h>

#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class Environment
:   public I_Environment
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name Environment implementation
    /// @{
public:
    virtual bool loadConfiguration(const boost::filesystem::path& _path);
    virtual bool loadConfiguration(std::istream& _input);
    virtual bool loadSessionInfo(const boost::filesystem::path& _path);
    virtual bool loadSessionInfo(std::istream& _input);
    virtual bool saveSessionInfo(const boost::filesystem::path& _path);
    virtual bool saveSessionInfo(std::ostream& _output);
    virtual const std::string operator[](const std::string& _key) const;
    /// @}

    /// @name 'Structors
    /// @{
public:
             Environment();
    virtual ~Environment();
    /// @}

    /// @name Member Variables
    /// @{
private:
    rapidjson::Document m_configuration;
    rapidjson::Document m_sessionInfo;
    /// @}

};  // class Environment

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_ENVIRONMENT_HPP_INCLUDED
