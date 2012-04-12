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
#include "ContestGenerator.hpp"
#include "SolutionGenerator.hpp"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <sstream>

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
int
main(int _argc, const char* _argv[])
{
    GCJFramework::ContestGenerator contestGenerator;
    GCJFramework::SolutionGenerator solutionGenerator;

    bool validate;
    std::string contest, solution;
    std::string configPath;
    boost::program_options::variables_map variables;

    boost::program_options::options_description description(
        "Google Code Jam Solution Framework\n"
        "\n"
        "Copyright (C) 2012 Matthew Alan Gray\n"
        "\n"
        "  This software is provided 'as-is', without any express or implied\n"
        "  warranty.  In no event will the authors be held liable for any damages\n"
        "  arising from the use of this software.\n"
        "\n"
        "  Permission is granted to anyone to use this software for any purpose,\n"
        "  including commercial applications, and to alter it and redistribute it\n"
        "  freely, subject to the following restrictions:\n"
        "\n"
        "  1. The origin of this software must not be misrepresented; you must not\n"
        "     claim that you wrote the original software. If you use this software\n"
        "     in a product, an acknowledgment in the product documentation would be\n"
        "     appreciated but is not required.\n"
        "  2. Altered source versions must be plainly marked as such, and must not be\n"
        "     misrepresented as being the original software.\n"
        "  3. This notice may not be removed or altered from any source distribution.\n"
        "\n"
        "  @author Matthew Alan Gray <mgray@hatboystudios.com>\n"
        "\n"
        "Allowed options:"
    );

    description.add_options()
        (
            "help,h", 
            "Produce this help message"
        )
        (
            "contestId,ci",
            boost::program_options::value<std::string>(&contest),
            "Contest Id"
        )
        (
            "solution,s",
            boost::program_options::value<std::string>(&solution),
            "Solution name"
        )
        (
            "config,c", 
            boost::program_options::value<std::string>(&configPath)
                ->default_value("config.json"), 
            "Configuration JSON file"
        )
    ;

    boost::program_options::store(
        boost::program_options::parse_command_line(
            _argc, 
            (char**)_argv, 
            description
        ), 
        variables
    );
    
    boost::program_options::notify(variables);

    if (variables.size() == 1 || variables.count("help") == 1)
    {
        std::stringstream stream;
        stream << std::endl << description << std::endl;
        std::cout << stream.str();
        return 0;
    }

    boost::filesystem::path path = boost::filesystem::system_complete(
        boost::filesystem::path(configPath)
    ).normalize();

    return 0;
}

//-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
