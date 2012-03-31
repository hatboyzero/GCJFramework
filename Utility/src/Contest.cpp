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
#include "Contest.hpp"

#include <GCJFramework/Core/I_Module.hpp>
#include <GCJFramework/Core/I_ModuleManager.hpp>
#include <GCJFramework/Core/I_ModuleService.hpp>
#include <GCJFramework/Core/I_Solution.hpp>

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/thread/locks.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Contest::Contest(const boost::filesystem::path& _path)
:   m_name(_path.leaf().string())
,   m_path(_path)
,   m_solutionsMutex()
,   m_solutions()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Contest::~Contest()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string&
Contest::getName() const
{
    return m_name;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Contest::loadSolutions()
{
    clearSolutions();

    std::stringstream stream;
    boost::filesystem::directory_iterator iter(m_path);
    while (iter != boost::filesystem::directory_iterator())
    {
        if (boost::filesystem::is_directory(iter->path()))
        {
            stream.str("");
            std::string solutionName = iter->path().leaf().string();
            stream << "Loading solution " << solutionName << "...";
            BOOST_LOG_TRIVIAL(info) << stream.str();

            boost::filesystem::path modulePath = boost::filesystem::system_complete(
                iter->path().string() + "/bin"
            ).normalize();

            I_ModuleManager::getSingleton().addPath(modulePath);

            I_ModuleService::pModule_type pModule = 
                I_ModuleManager::getSingleton()
                    .getService()
                        ->load(solutionName);

            if (pModule != NULL)
            {
                boost::lock_guard<boost::mutex> guard(m_solutionsMutex);

                pModule->setPath(iter->path());
                m_solutions[solutionName] = SolutionContext();
                m_solutions[solutionName].m_pSolution = pModule->getSolution();
                m_solutions[solutionName].m_datasetPath = iter->path().string() + "/datasets";
            }
            else
            {
                stream.str("");
                stream << "Error loading solution " << solutionName << "!";
                BOOST_LOG_TRIVIAL(warning) << stream.str();
            }
        }

        iter++;
    }

    return true;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Contest::pSolution_type
Contest::getSolution(const std::string& _name)
{
    boost::lock_guard<boost::mutex> guard(m_solutionsMutex);

    Solutions_type::iterator iter = m_solutions.find(_name);
    if (iter != m_solutions.end())
    {
        return iter->second.m_pSolution;
    }

    std::stringstream stream;
    stream << "Solution " << _name << " does not exist!";
    BOOST_LOG_TRIVIAL(warning) << stream.str();
    return pSolution_type();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
Contest::getSolutions(I_SolutionVisitor& _visitor) const
{
    boost::lock_guard<boost::mutex> guard(m_solutionsMutex);

    _visitor.begin();

    Solutions_type::const_iterator iter = m_solutions.begin();
    while (iter != m_solutions.end())
    {
        _visitor.visit(*iter->second.m_pSolution);
        iter++;
    }

    _visitor.end();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
Contest::clearSolutions()
{
    boost::lock_guard<boost::mutex> guard(m_solutionsMutex);

    m_solutions.clear();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
