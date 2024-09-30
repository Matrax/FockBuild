#include <fock/commands/build_command.hpp>

fock::BuildCommand::BuildCommand() noexcept :
    Command("info", 5, 5)
{}

void fock::BuildCommand::OnExecute(const std::vector<std::string> & command_params_array)
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
    std::cout << "[FOCKBUILD - INFO] : Building program..." << std::endl;
    if(language.compare("cpp") == 0 && compiler.compare("msvc") == 0)
    {
        try {
            // Instantiate a C++ fock project, a MSVC builder and build
            const fock::CppProject cpp_project(file);
            const fock::MSVCBuilder msvc_builder;
            msvc_builder.Build(cpp_project);
        } catch(const std::exception & exception) {
            throw std::runtime_error(exception.what());
        }
    }
    std::cout << "[FOCKBUILD - INFO] : Program builded !" << std::endl;
}