#pragma once

#include <fock/commands/command.hpp>

namespace fock
{
    class InfoCommand : public Command
    {
    public:

        InfoCommand() noexcept;

        virtual ~InfoCommand() noexcept = default;

    protected:

        void OnExecute(const std::vector<std::string> & command_params_array) override;

    };
}