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
#ifndef GCJFRAMEWORK_MODULE_INFO_HPP_INCLUDED
#define GCJFRAMEWORK_MODULE_INFO_HPP_INCLUDED

#include "../I_ModuleInfo.hpp"

#include <string>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
namespace GCJFramework {
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

class ModuleInfo
:   public I_ModuleInfo
{
    /// @name Types
    /// @{
public:
    /// @}

    /// @name I_ModuleInfo implementation
public:
    virtual void setName(const std::string _name);
    virtual std::string getName() const;

    virtual void setHandle(const ModuleHandle_type _handle);
    virtual ModuleHandle_type getHandle() const;

    virtual unsigned incrementReferences();
    virtual unsigned decrementReferences();
    /// @}

    /// @name 'Structors
    /// @{
public:
             ModuleInfo();
    virtual ~ModuleInfo();
    /// @}

    /// @name Member variables
    /// @{

    // Module name
    std::string         m_name;

    // Module handle
    ModuleHandle_type  m_hModule;

    // Module reference count
    unsigned            m_references;
    /// @}

};  // interface ModuleInfo

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
}	// namespace GCJFramework
//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~

#endif // GCJFRAMEWORK_MODULE_INFO_HPP_INCLUDED
