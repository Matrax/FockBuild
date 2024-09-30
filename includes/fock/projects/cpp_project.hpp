#pragma once

// STD includes
#include <string>
#include <vector>
#include <string_view>

// FOCK includes
#include <fock/projects/project.hpp>
#include <fock/languages/cpp_build_type.hpp>

namespace fock
{
    class CppProject : public Project
    {
    private:
        
        std::vector<std::string> m_sources;
        std::vector<std::string> m_modules;
        std::vector<std::string> m_include_directories;
        std::vector<std::string> m_libraries;
        std::vector<std::string> m_library_directories;
        fock::CppBuildType m_build_type;

    public:

        // Constructor
        CppProject(const std::string_view & filepath);
		
        // Default destructor
		virtual ~CppProject() noexcept = default;

        std::vector<std::string> GetSources() const noexcept;

        std::vector<std::string> GetModules() const noexcept;

        std::vector<std::string> GetIncludeDirectories() const noexcept;

        std::vector<std::string> GetLibraries() const noexcept;

        std::vector<std::string> GetLibraryDirectories() const noexcept;

        fock::CppBuildType GetBuildType() const noexcept;

    };
}