//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
// Google Code Jam Solution Framework
//
// Copyright (C) 2012 Matthew Alan Gray
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//  @author Matthew Alan Gray <mgray@hatboystudios.com>
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#ifndef GCJFRAMEWORK_ENVIRONMENT_HPP_INCLUDED
#define GCJFRAMEWORK_ENVIRONMENT_HPP_INCLUDED

#include <rapidjson/document.h>

#include <boost/filesystem.hpp>

#include <iostream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class Environment
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name Environment implementation
    /// @{
public:
    /// Loads the environment configuration from a file path.
    /// @param[in] _path Configuration file path.
    /// @returns True if successful, False otherwise.
    bool loadConfiguration(const boost::filesystem::path& _path);

    /// Loads the environment configuratoin from an input stream.
    /// @param[in] _input Configuration input stream.
    /// @returns True if successful, False otherwise.
    bool loadConfiguration(std::istream& _input);

    /// Loads the session info from a file path.
    /// @param[in] _path Session info file path.
    /// @returns True if successful, False otherwise.
    bool loadSessionInfo(const boost::filesystem::path& _path);

    /// Loads the session info from an input stream.
    /// @param[in] _input Session info input stream.
    /// @returns True if successful, False otherwise.
    bool loadSessionInfo(std::istream& _input);

    /// Saves the session info to a file path.
    /// @param[in] _path Session info file path.
    /// @returns True if successful, False otherwise.
    bool saveSessionInfo(const boost::filesystem::path& _path);

    /// Saves the session info to an output stream.
    /// @param[in] _output Session info output stream.
    /// @returns True if successful, False otherwise.
    bool saveSessionInfo(std::ostream& _output);
    /// @}

    /// @name 'Structors
    /// @{
public:
     Environment();
    ~Environment();
    /// @}

    /// @name Member Variables
    /// @{
private:
    rapidjson::Document     m_configuration;
    rapidjson::Document     m_sessionInfo;
    /// @}

};  // class Environment

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_ENVIRONMENT_HPP_INCLUDED
