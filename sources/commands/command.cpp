#include <fock/commands/command.hpp>

fock::Command::Command(const std::string_view & name, unsigned short min_params, unsigned short max_params) :
    m_name(name),
    m_min_params(min_params),
    m_max_params(max_params)
{
    if(m_name.empty() == true)
        throw std::runtime_error("Can't create a command with no name");
}

void fock::Command::Execute(const std::vector<std::string> & params)
{
    if(params.size() < m_min_params)
        throw std::runtime_error("Not enough parameters ! Do fockbuild.exe to get all the parameters for this command");

    if(params.size() > m_max_params)
        throw std::runtime_error("Too much parameters ! Do fockbuild.exe to get all the parameters for this command");

    try {
        OnExecute(params);
    } catch(const std::exception & exception) {
        std::cerr << "[FOCKBUILD - ERROR] : " << exception.what() << std::endl;
    }
}