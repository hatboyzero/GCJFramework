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
#ifndef GCJFRAMEWORK_I_ENVIRONMENT_HPP_INCLUDED
#define GCJFRAMEWORK_I_ENVIRONMENT_HPP_INCLUDED

#include "Configuration.hpp"

#include <boost/filesystem/path.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class GCJUTILITY_DLL_LINK I_Environment
:   public boost::noncopyable
{
    /// @name Types
    /// @{
public:
    typedef boost::shared_ptr<I_Environment>    pEnvironment_type;
    /// @}

    /// @name Environment implementation
    /// @{
public:
    /// Loads the environment configuration from a file path.
    /// @param[in] _path Configuration file path.
    /// @returns True if successful, False otherwise.
    virtual bool loadConfiguration(const boost::filesystem::path& _path) = 0;

    /// Loads the environment configuratoin from an input stream.
    /// @param[in] _input Configuration input stream.
    /// @returns True if successful, False otherwise.
    virtual bool loadConfiguration(std::istream& _input) = 0;

    /// Loads the session info from a file path.
    /// @param[in] _path Session info file path.
    /// @returns True if successful, False otherwise.
    virtual bool loadSessionInfo(const boost::filesystem::path& _path) = 0;

    /// Loads the session info from an input stream.
    /// @param[in] _input Session info input stream.
    /// @returns True if successful, False otherwise.
    virtual bool loadSessionInfo(std::istream& _input) = 0;

    /// Saves the session info to a file path.
    /// @param[in] _path Session info file path.
    /// @returns True if successful, False otherwise.
    virtual bool saveSessionInfo(const boost::filesystem::path& _path) = 0;

    /// Saves the session info to an output stream.
    /// @param[in] _output Session info output stream.
    /// @returns True if successful, False otherwise.
    virtual bool saveSessionInfo(std::ostream& _output) = 0;

    /// Gets an environment variable (configuration and session)
    virtual const std::string operator[](const std::string& _key) const = 0;
    /// @}

    /// @name Static Methods
    /// @{
public:
    static pEnvironment_type create();
    /// @}

    /// @name 'Structors
    /// @{
protected:
             I_Environment();
    virtual ~I_Environment();
    /// @}

};  // interface I_Environment

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_I_ENVIRONMENT_HPP_INCLUDED
