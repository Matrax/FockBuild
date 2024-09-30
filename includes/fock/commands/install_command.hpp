#pragma once

// FOCK includes
#include <fock/commands/command.hpp>
#include <fock/builders/msvc_builder.hpp>
#include <fock/projects/cpp_project.hpp>

namespace fock
{
    class InstallCommand : public Command
    {
    public:

        InstallCommand() noexcept;

        virtual ~InstallCommand() noexcept = default;

    protected:

        void OnExecute(const std::vector<std::string> & command_params_array) override;

    };
}