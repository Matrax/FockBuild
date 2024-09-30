#include <fock/utils/system_utils.hpp>

const std::vector<std::string> fock::GetProgramArgs(int argc, char * argv[]) 
{
    // Check args
    if(argc <= 0 || argv == nullptr)
        throw std::runtime_error("Can't retrieve the program arguments");
    
    // Fill arguments list
    std::vector<std::string> arguments;
    for(size_t i = 0; i < argc; i++)
        arguments.push_back(argv[i]);

    return arguments;
}

void fock::CallSystemCommand(const std::string & command)
{
    // System call
    int result = std::system(command.data());
    
    // Check system call
    if(result != 0)
        throw std::runtime_error("Error on calling the command");
}

std::string fock::GetFileNameFromPath(const std::string & path) noexcept
{
    std::filesystem::path file_path = std::filesystem::path(path);

    if(file_path.empty() == false)
    {
        file_path = file_path.filename();

        if(file_path.extension().empty() == false)
        {
            file_path = file_path.replace_extension("");
        }
    }

    return file_path.string();
}