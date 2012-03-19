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
:   m_path(_path)
,   m_solutionsMutex()
,   m_solutions()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Contest::~Contest()
{
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
            stream.clear();
            std::string solutionName = iter->path().leaf().string();
            stream << "Loading solution " << solutionName << "..." << std::endl;
            BOOST_LOG_TRIVIAL(info) << stream.str();
            std::cout << stream.str();

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

                m_solutions[solutionName] = pModule->getSolution();
            }
            else
            {
                stream.clear();
                stream << "Error loading solution " << solutionName << "!" << std::endl;
                BOOST_LOG_TRIVIAL(warning) << stream.str();
                std::cout << stream.str();
            }
        }

        iter++;
    }

    return true;
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
