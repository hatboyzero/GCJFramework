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
#include "ContestGenerator.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/log/trivial.hpp>

#include <sstream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ContestGenerator::ContestGenerator(const boost::filesystem::path& _configPath)
:   m_configPath(_configPath)
,   m_pEnvironment(I_Environment::create())
,   m_pContestManager(I_ContestManager::create())
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ContestGenerator::~ContestGenerator()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
ContestGenerator::generate(const std::string& _contestId)
{
    if (!boost::filesystem::exists(m_configPath))
    {
        std::stringstream stream;
        stream << "Configuration path \"" << m_configPath << "\" does not exist.";
        BOOST_LOG_TRIVIAL(error) << stream.str();
        return;
    }

    if (!m_pEnvironment->loadConfiguration(m_configPath))
    {
        return;
    }

    std::string locationPathStr = (*m_pEnvironment)["location"];
    if (locationPathStr.empty())
    {
        std::stringstream stream;
        stream << "Solution path not defined -- verify \"location\" is defined in config.json";
        BOOST_LOG_TRIVIAL(error) << stream.str();
        return;
    }

    boost::filesystem::path locationPath = boost::filesystem::system_complete(
        locationPathStr
    ).normalize();

    if (!m_pContestManager->setLocation(locationPath))
    {
        return;
    }

    if (!m_pContestManager->loadContest(_contestId))
    {
        //m_pContestManager->generateContest(_contestId);
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
