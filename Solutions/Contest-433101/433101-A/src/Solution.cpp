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
#include "Solution.hpp"

#include <GCJFramework/Core/I_Module.hpp>
#include <GCJFramework/Core/I_ModuleManager.hpp>
#include <GCJFramework/Core/I_ModuleService.hpp>

#include <boost/cstdint.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/log/trivial.hpp>

#include <sstream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Solution::Solution(I_Module* _pModule)
:   m_pModule(_pModule)
,   m_pIs(NULL)
,   m_pOs(NULL)
{
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
Solution::~Solution()
{
    reset();

    I_ModuleManager::getSingleton().getService()->unload(m_pModule);
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
const std::string&
Solution::getName() const
{
    return m_pModule->getName();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Solution::validate() const
{
    std::stringstream outputStream;

    bool success = execute(getInput("validation"), outputStream);

    if (success)
    {
        std::stringstream inputStream;
        inputStream << getValidationInput().rdbuf();
        reset();

        success &= outputStream.str().compare(inputStream.str()) == 0;

        if (!success)
        {
            std::stringstream stream;
            stream << "Validation Failed!!!" << std::endl;
            stream << "Expected:" << std::endl;
            stream << inputStream.str() << std::endl;
            stream << "Instead, got: " << std::endl;
            stream << outputStream.str();
            BOOST_LOG_TRIVIAL(error) << stream.str();
            return false;
        }
        else
        {
            std::stringstream stream;
            stream << "Solution " << getName() << " successfully validated!";
            BOOST_LOG_TRIVIAL(info) << stream.str();
            return true;
        }
    }

    return true;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
bool
Solution::execute(const std::string& _type) const
{
    return execute(getInput(_type), getOutput(_type));
    reset();
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
void
Solution::reset() const
{
    if (m_pIs != NULL)
    {
        delete m_pIs;
        m_pIs = NULL;
    }

    if (m_pOs != NULL)
    {
        delete m_pOs;
        m_pOs = NULL;
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
std::istream&
Solution::getInput(const std::string& _type) const
{
    boost::filesystem::path inputPath = boost::filesystem::system_complete(
        m_pModule->getPath().string() + "/datasets/" + getName() + "-" + _type + ".in"
    ).normalize();

    if (boost::filesystem::exists(inputPath))
    {
        if (m_pIs != NULL)
        {
            delete m_pIs;
        }

        try
        {
            m_pIs = new std::ifstream(inputPath.string());
            return *m_pIs;
        }
        catch (std::exception& _e)
        {
            std::stringstream stream;
            stream << "Input stream could not be created! --" << _e.what();
            BOOST_LOG_TRIVIAL(error) << stream.str();
            throw std::exception(stream.str().c_str());
        }
    }

    std::stringstream stream;
    stream << "Input stream does not exist!";
    BOOST_LOG_TRIVIAL(error) << stream.str();
	throw std::exception(stream.str().c_str());
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
std::istream&
Solution::getValidationInput() const
{
    boost::filesystem::path inputPath = boost::filesystem::system_complete(
        m_pModule->getPath().string() + "/datasets/" + getName() + "-validation.out"
    ).normalize();

    if (boost::filesystem::exists(inputPath))
    {
        if (m_pIs != NULL)
        {
            delete m_pIs;
            m_pIs = NULL;
        }

        m_pIs = new std::ifstream(inputPath.string());
        return *m_pIs;
    }

    std::stringstream stream;
    stream << "Validation input stream does not exist!";
    BOOST_LOG_TRIVIAL(error) << stream.str();
    throw std::exception(stream.str().c_str());
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
std::ostream&
Solution::getOutput(const std::string& _type) const
{
    boost::filesystem::path outputPath = boost::filesystem::system_complete(
        m_pModule->getPath().string() + "/datasets/" + getName() + "-" + _type + ".out"
    ).normalize();

    if (m_pOs != NULL)
    {
        delete m_pOs;
        m_pOs = NULL;
    }

    try
    {
        m_pOs = new std::ofstream(outputPath.string());
        return *m_pOs;
    }
    catch (std::exception& _e)
    {
        std::stringstream stream;
        stream << "Output stream could not be created! --" << _e.what();
        BOOST_LOG_TRIVIAL(error) << stream.str();
        throw std::exception(stream.str().c_str());
    }
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
