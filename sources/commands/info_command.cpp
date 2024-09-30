#include <fock/commands/info_command.hpp>

fock::InfoCommand::InfoCommand() noexcept :
    Command("info", 1, 1)
{}

void fock::InfoCommand::OnExecute(const std::vector<std::string> & command_params_array)
{
    if(!std::cout)
        throw std::runtime_error("Can't print to the terminal !");

    // Print description
    std::cout << "FockBuild is a build system that allow the developers to manage and build differents kind of projects written with a programming language like C/C++, Java." << std::endl;
    std::cout << std::endl;

    // Print usage
    std::cout << "Usage: " << std::endl;
    std::cout << "\t- fockbuild [options]" << std::endl;
    std::cout << std::endl;

    // Print options
    std::cout << "Options: " << std::endl;
    std::cout << "\t- build [file] [language] [compiler] : Build a project with a JSON file, the language and the compiler." << std::endl;
    std::cout << "\t- print-cmd [file] [language] [compiler] : Print the commands that will build the project." << std::endl;
    std::cout << std::endl;

    // Print supported languages and compilerse associated with
    std::cout << "Supported languages and compilers: " << std::endl;
    std::cout << "\t- cpp [msvc]" << std::endl;
}