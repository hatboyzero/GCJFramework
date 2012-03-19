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
#include "ContestManager.hpp"
#include "Contest.hpp"

#include <boost/log/trivial.hpp>
#include <boost/thread/locks.hpp>

#include <sstream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ContestManager::ContestManager()
:   m_path()
,   m_contestsMutex()
,   m_contests()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ContestManager::~ContestManager()
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
ContestManager::setLocation(const boost::filesystem::path& _path)
{
    std::stringstream stream;

    if (boost::filesystem::exists(_path))
    {
        m_path = _path;
        stream << "Search path set to " << m_path << std::endl;
        BOOST_LOG_TRIVIAL(info) << stream.str();
        std::cout << stream.str();
        return true;
    }

    stream << "Search path " << _path << " does not exist!" << std::endl;
    BOOST_LOG_TRIVIAL(error) << stream.str();
    return false;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
ContestManager::loadContest(const std::string& _contestId)
{
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    struct Deleter
    {
        void
        operator()(I_Contest* _pContest)
        {
            Contest* pContest =
                dynamic_cast<Contest*>(_pContest);

            assert (pContest != NULL);

            delete pContest;
        }
    };  // struct Deleter
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

    std::stringstream stream;

    boost::filesystem::path contestPath = boost::filesystem::system_complete(
        m_path.string() + "/Contest-" + _contestId
    ).normalize();

    if (boost::filesystem::exists(contestPath) && boost::filesystem::is_directory(contestPath))
    {
        boost::lock_guard<boost::mutex> guard(m_contestsMutex);

        Contests_type::iterator iter = m_contests.find(_contestId);
        if (iter == m_contests.end())
        {
            stream.clear();
            stream << "Loading Contest-" << _contestId << "..." << std::endl;
            BOOST_LOG_TRIVIAL(info) << stream.str();
            std::cout << stream.str();

            pContest_type pContest(new Contest(contestPath), Deleter());
            
            if (pContest->loadSolutions())
            {
                m_contests[_contestId] = pContest;

                stream.clear();
                stream << "Loaded Contest-" << _contestId << "." << std::endl;
                BOOST_LOG_TRIVIAL(info) << stream.str();
                std::cout << stream.str();
                return true;
            }
        }
    }

    stream.clear();
    stream << "Failed to load Contest-" << _contestId << "!" << std::endl;
    BOOST_LOG_TRIVIAL(error) << stream.str();
    std::cout << stream.str();
    return false;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
ContestManager::pContest_type
ContestManager::getContest(const std::string& _contestId) const
{
    boost::lock_guard<boost::mutex> guard(m_contestsMutex);

    Contests_type::const_iterator iter = m_contests.find(_contestId);
    if (iter != m_contests.end())
    {
        return iter->second;
    }

    std::stringstream stream;
    stream << "Attempted to retrieve Contest-" << _contestId << ", but it does not exist..." << std::endl;
    BOOST_LOG_TRIVIAL(warning) << stream.str();
    std::cout << stream.str();
    return pContest_type();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
ContestManager::getContests(I_ContestVisitor& _visitor) const
{
    if (!m_contests.empty())
    {
        boost::lock_guard<boost::mutex> guard(m_contestsMutex);
        if (!m_contests.empty())
        {
            _visitor.begin();

            Contests_type::const_iterator iter = m_contests.begin();
            while (iter != m_contests.end())
            {
                _visitor.visit(iter->second);
                iter++;
            }

            _visitor.end();
        }
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
