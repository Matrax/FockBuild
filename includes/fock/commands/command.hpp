#pragma once

// STD includes
#include <string>
#include <string_view>
#include <vector>
#include <exception>
#include <iostream>

namespace fock
{
    class Command
    {
    private:
        
        std::string m_name;
        unsigned short m_max_params;
        unsigned short m_min_params;
        
    public:

        Command() = delete;

        Command(const std::string_view & name, unsigned short m_min_params, unsigned short m_max_params);

        virtual ~Command() noexcept = default;

        void Execute(const std::vector<std::string> & command_params_array);

    protected:

        virtual void OnExecute(const std::vector<std::string> & command_params_array) = 0;

    };
}