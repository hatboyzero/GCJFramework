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
#include "Environment.hpp"

#include <rapidjson/prettywriter.h>
#include <rapidjson/genericreadstream.h>
#include <rapidjson/genericwritestream.h>

#include <boost/log/trivial.hpp>

#include <fstream>
#include <sstream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Environment::Environment()
:   m_configuration()
,   m_sessionInfo()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Environment::~Environment()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Environment::loadConfiguration(const boost::filesystem::path& _path)
{
    if (boost::filesystem::exists(_path))
    {
        std::ifstream ifs;
        ifs.open(_path.string(), std::ios_base::in|std::ios_base::binary);
        if (loadConfiguration(ifs))
        {
            BOOST_LOG_TRIVIAL(info) << "Loaded configuration from " << _path;
            return true;
        }
    }

    BOOST_LOG_TRIVIAL(error) << "Configuration file " << _path << " does not exist.";
    return false;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Environment::loadConfiguration(std::istream& _input)
{
    std::stringstream json;
    json << _input.rdbuf();
    if (m_configuration.Parse<0>(json.str().c_str()).HasParseError())
    {
        BOOST_LOG_TRIVIAL(error) << "JSON parsing error when loading configuration from input stream";
        return false;
    }

    return true;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Environment::loadSessionInfo(const boost::filesystem::path& _path)
{
    if (boost::filesystem::exists(_path))
    {
        std::ifstream ifs;
        ifs.open(_path.string(), std::ios_base::in | std::ios_base::binary);
        if (loadSessionInfo(ifs))
        {
            BOOST_LOG_TRIVIAL(info) << "Loaded session info from " << _path;
            return true;
        }
    }

    BOOST_LOG_TRIVIAL(info) << "Session file " << _path << " does not exist.";
    return false;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Environment::loadSessionInfo(std::istream& _input)
{
    std::stringstream json;
    json << _input.rdbuf();
    if (m_sessionInfo.Parse<0>(json.str().c_str()).HasParseError())
    {
        BOOST_LOG_TRIVIAL(error) << "JSON parsing error when loading session info from input stream";
        return false;
    }

    return true;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Environment::saveSessionInfo(const boost::filesystem::path& _path)
{
    std::ofstream ofs;
    ofs.open(_path.string(), std::ios_base::out | std::ios_base::trunc);
    if (saveSessionInfo(ofs))
    {
        BOOST_LOG_TRIVIAL(info) << "Saved session info to " << _path;
        return true;
    }

    BOOST_LOG_TRIVIAL(error) << "Error saving session info to " << _path;
    return false;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Environment::saveSessionInfo(std::ostream& _output)
{
    rapidjson::GenericWriteStream jsonGfs(_output);
    rapidjson::PrettyWriter<rapidjson::GenericWriteStream> writer(jsonGfs);
    m_sessionInfo.Accept(writer);
    return true;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string
Environment::operator[](const std::string& _key) const
{
    if (!m_configuration[_key.c_str()].IsNull())
    {
        return m_configuration[_key.c_str()].GetString();
    }
    else
    if (!m_sessionInfo[_key.c_str()].IsNull())
    {
        return m_sessionInfo[_key.c_str()].GetString();
    }
    
    return std::string("");
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
