#pragma once

// FOCK includes
#include <fock/commands/command.hpp>
#include <fock/builders/msvc_builder.hpp>
#include <fock/projects/cpp_project.hpp>

namespace fock
{
    class BuildCommand : public Command
    {
    public:

        BuildCommand() noexcept;

        virtual ~BuildCommand() noexcept = default;

    protected:

        void OnExecute(const std::vector<std::string> & command_params_array) override;

    };
}