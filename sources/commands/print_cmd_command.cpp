#include <fock/commands/print_cmd_command.hpp>

fock::PrintCmdCommand::PrintCmdCommand() noexcept :
    Command("info", 5, 5)
{}

void fock::PrintCmdCommand::OnExecute(const std::vector<std::string> & command_params_array)
{
    // Parse arguments
    const std::string file = command_params_array.at(2);
    const std::string language = command_params_array.at(3);
    const std::string compiler = command_params_array.at(4);

    // Check arguments
    if(file.empty() == true)
        throw std::runtime_error("No file provided");
    if(language.empty() == true)
        throw std::runtime_error("No programming language provided");
    if(compiler.empty() == true)
        throw std::runtime_error("No compiler provided");

    // Check language
    const std::vector<std::string> available_languages = {"cpp"};
    bool language_valid = false;
    for(const std::string & available_language : available_languages)
    {
        if(available_language.compare(language) == 0) 
            language_valid = true;
    }
    if(language_valid == false)
        throw std::runtime_error("Invalid language !");

    // Check compiler
    const std::vector<std::string> available_compilers = {"msvc"};
    bool compiler_valid = false;
    for(const std::string & available_compiler : available_compilers)
    {
        if(available_compiler.compare(compiler) == 0) 
            compiler_valid = true;
    }
    if(compiler_valid == false)
        throw std::runtime_error("Invalid compiler !");

    // If C++ and MSVC
    std::cout << "[FOCKBUILD - INFO] : Retrieving the command..." << std::endl;
    if(language.compare("cpp") == 0 && compiler.compare("msvc") == 0)
    {
        try {
            // Instantiate a C++ fock project, a MSVC builder and then build
            const fock::CppProject cpp_project(file);
            const fock::MSVCBuilder msvc_builder;
            bool can_link = false;

            // If we have modules
            if(cpp_project.GetModules().size() > 0)
            {
                const std::vector<std::string> additional_compiler_params = msvc_builder.GetCompilerParams(cpp_project);
                std::cout << std::endl;
                std::cout << "Modules compilation:" << std::endl << std::endl;
                std::cout << msvc_builder.GetCommandToCompileModules(cpp_project, additional_compiler_params) << std::endl;
                can_link = true;
            }

            // If we have sources
            if(cpp_project.GetSources().size() > 0)
            {
                const std::vector<std::string> additional_compiler_params = msvc_builder.GetCompilerParams(cpp_project);
                std::cout << std::endl;
                std::cout << "Sources compilation:" << std::endl << std::endl;
                std::cout << msvc_builder.GetCommandToCompileSources(cpp_project, additional_compiler_params) << std::endl;
                can_link = true;
            }

            // If we have sources or modules to link
            if(can_link == true)
            {
                const std::vector<std::string> additional_linker_params = msvc_builder.GetCompilerParams(cpp_project);
                std::cout << std::endl;
                std::cout << "Create executable:" << std::endl << std::endl;
                std::cout << msvc_builder.GetCommandToCreateExecutable(cpp_project, additional_linker_params) << std::endl;
            }

        } catch(const std::exception & exception) {
            throw std::runtime_error(exception.what());
        }
    }
    std::cout << "[FOCKBUILD - INFO] : Command here !" << std::endl;
}