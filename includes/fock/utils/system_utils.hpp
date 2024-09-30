#pragma once

#include <Windows.h>

// STD includes
#include <string>
#include <vector>
#include <string_view>
#include <iostream>
#include <filesystem>

namespace fock
{
    /*
    * Get all the arguments of the program.
    * @param argc The number of arguments
    * @param argv[] Array of arguments
    */
    const std::vector<std::string> GetProgramArgs(int argc, char * argv[]);

    void CallSystemCommand(const std::string & command);

    std::string GetFileNameFromPath(const std::string & path) noexcept;
}
