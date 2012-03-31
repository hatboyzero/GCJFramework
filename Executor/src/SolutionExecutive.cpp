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
#include "SolutionExecutive.hpp"

#include <GCJFramework/Core/I_ModuleManager.hpp>
#include <GCJFramework/Core/I_ModuleService.hpp>
#include <GCJFramework/Core/I_Module.hpp>
#include <GCJFramework/Core/I_Contest.hpp>
#include <GCJFramework/Core/I_Solution.hpp>

#include <boost/log/trivial.hpp>

#include <sstream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
SolutionExecutive::SolutionExecutive(const boost::filesystem::path& _configPath)
:   m_configPath(_configPath)
,   m_pEnvironment(I_Environment::create())
,   m_pContestManager(I_ContestManager::create())
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
SolutionExecutive::~SolutionExecutive()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
SolutionExecutive::run()
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

    std::string contestId = (*m_pEnvironment)["contest"];
    if (contestId.empty())
    {
        std::stringstream stream;
        stream << "Contest not defined -- verify \"contest\" is defined in config.json";
        BOOST_LOG_TRIVIAL(error) << stream.str();
        return;
    }

    if (!m_pContestManager->loadContest(contestId))
    {
        return;
    }

    I_ContestManager::pContest_type pContest = 
        m_pContestManager->getContest(contestId);

    if (pContest.get() == NULL)
    {
        return;
    }

    validate(pContest);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
SolutionExecutive::validate(pContest_type _pContest)
{
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    class SolutionVisitor
    :   public I_Contest::I_SolutionVisitor
    {
    public:
        virtual void begin() {}

        virtual void visit(const I_Solution& _solution)
        {
            try
            {
                _solution.validate();
            }
            catch (std::exception& _e)
            {
                std::stringstream stream;
                stream << "Caught exception during validation of " << _solution.getName();
                stream << " -- " << _e.what();
                BOOST_LOG_TRIVIAL(error) << stream.str();
            }
        }

        virtual void end() {}

        SolutionVisitor()
        {
        }

    private:

    };  // class SolutionVisitor
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

   SolutionVisitor visitor;
   _pContest->getSolutions(visitor);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
