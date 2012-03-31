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
#ifndef GCJFRAMEWORK_CONTEST_HPP_INCLUDED
#define GCJFRAMEWORK_CONTEST_HPP_INCLUDED

#include <GCJFramework/Core/I_Contest.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/thread/mutex.hpp>

#include <map>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class Contest
:   public I_Contest
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_Contest implementation
    /// @{
public:
    virtual const std::string& getName() const;
    virtual bool loadSolutions();
    virtual pSolution_type getSolution(const std::string& _name);
    virtual void getSolutions(I_SolutionVisitor& _visitor) const;
    /// @}

    /// @name Contest implementation
    /// @{
public:
    void clearSolutions();
    /// @}

    /// @name Inner Structures
    /// @{
public:
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    struct SolutionContext
    {
        pSolution_type          m_pSolution;
        boost::filesystem::path m_datasetPath;
    };  // struct SolutionContext
    //-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
    /// @}

    /// @name 'Structors
    /// @{
public:
             Contest(const boost::filesystem::path& _path);
    virtual ~Contest();
    /// @}

    /// @name Member Variables
    /// @{
private:
    const std::string           m_name;
    boost::filesystem::path     m_path;

    mutable boost::mutex        m_solutionsMutex;
    typedef std::map<std::string, SolutionContext>   Solutions_type;
    Solutions_type              m_solutions;
    /// @}

};  // class Contest

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}   // namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_CONTEST_HPP_INCLUDED
