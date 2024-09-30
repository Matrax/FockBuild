#pragma once

// STD includes
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <string_view>

// JSON includes
#include <nlohmann/json.hpp>

namespace fock
{
    class Project
    {
    private:

        std::string m_name;
        std::string m_description;
        std::string m_build_directory;
        std::vector<int> m_version;
        std::vector<std::string> m_authors;
        nlohmann::json m_json_data;

    public:

        // Constructor
        Project(const std::string_view & filepath);

        // Default destructor
		virtual ~Project() noexcept;

        /*
        This method read a configuration of a type <T> from the JSON file.
        @param category The category of the configuration.
        @param configuration The name of the configuration to read from the JSON file.
        */
        template<typename T> 
        inline T ReadConfiguration(const std::string_view & category, const std::string_view & configuration) const
        {
            if(m_json_data.contains(category) == false)
                throw std::runtime_error("Can't retrieve the cpp-build configuration !");

            if( m_json_data[category].contains(configuration) == false)
            {
                std::cerr << "At " << category << ":" << configuration << std::endl;
                throw std::runtime_error("Can't retrieve the configuration !");
            }

            return m_json_data[category][configuration];
        }

        /*
        This method fill an array of a type <T> of all the values from a configuration in a JSON file.
        @param category The category of the configuration.
        @param configuration The name of the configuration in the JSON file.
        @param destination The array to fill.
        */
        template<typename T> 
        inline void CopyJsonDataToArray(const std::string_view & category, const std::string_view & configuration, std::vector<T> & destination) const
        {
            if(m_json_data.contains(category) == false)
                throw std::runtime_error("Can't retrieve the cpp-build configuration !");

            if( m_json_data[category].contains(configuration) == false)
                throw std::runtime_error("Can't retrieve the configuration !");

            const std::vector<T> array = m_json_data[category][configuration];

            // Copy into destination
            for(const T & str : array)
            {
                destination.push_back(str);
            }
        }

        std::string GetName() const noexcept;

        std::string GetDescription() const noexcept;

        std::string GetBuildDirectory() const noexcept;

        std::vector<std::string> GetAuthors() const noexcept;

        std::vector<int> GetVersion() const noexcept;


    };
}