// Win32 includes
#undef UNICODE
#include <Windows.h>

// STD includes
#include <iostream>
#include <string>
#include <exception>
#include <vector>

// FOCK includes
#include <fock/projects/cpp_project.hpp>
#include <fock/builders/msvc_builder.hpp>
#include <fock/utils/system_utils.hpp>
#include <fock/commands/info_command.hpp>
#include <fock/commands/build_command.hpp>
#include <fock/commands/print_cmd_command.hpp>

/*
* Main entry of the program.
*/
int main(int argc, char * argv[])
{
    try {
        // Get all program args into an std::string vector
        const std::vector<std::string> command_params_array = fock::GetProgramArgs(argc, argv);

        // If no command, use the info command
        if(command_params_array.size() == 1) 
            fock::InfoCommand().Execute(command_params_array);

        // If there is a command, call the correct command
        if(command_params_array.size() > 1)
        {
            if(command_params_array.at(1).compare("build") == 0) 
                fock::BuildCommand().Execute(command_params_array);
            else if(command_params_array.at(1).compare("print-cmd") == 0) 
                fock::PrintCmdCommand().Execute(command_params_array);
            else
                throw std::runtime_error("This command doesn't exist !");

        }
    } catch(const std::exception & exception) {
		// Print the error to the std::cerr if possible
		if(std::cerr)
			std::cerr << "[FOCKBUILD - ERROR] : " << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}