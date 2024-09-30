#include <fock/commands/install_command.hpp>

fock::InstallCommand::InstallCommand() noexcept :
    Command("info", 5, 5)
{}

void fock::InstallCommand::OnExecute(const std::vector<std::string> & command_params_array)
{

}