#include <fock/projects/cpp_project.hpp>

fock::CppProject::CppProject(const std::string_view & filepath) :
    fock::Project(filepath),
    m_build_type(CppBuildType::EXECUTABLE)
{
    try {
        // Read array configurations
        CopyJsonDataToArray<std::string>("cpp", "sources", m_sources);
        CopyJsonDataToArray<std::string>("cpp", "modules", m_modules);
        CopyJsonDataToArray<std::string>("cpp", "libraries", m_libraries);
        CopyJsonDataToArray<std::string>("cpp", "include-directories", m_include_directories);
        CopyJsonDataToArray<std::string>("cpp", "library-directories", m_library_directories);
        
        // Parse build-type
        const std::string build_type_str = ReadConfiguration<std::string>("cpp", "build-type"); 
        if(build_type_str.compare("EXECUTABLE") == 0) 
            m_build_type = CppBuildType::EXECUTABLE;
        else if(build_type_str.compare("STATIC-LIBRARY") == 0) 
            m_build_type = CppBuildType::STATIC_LIBRARY;
        else if(build_type_str.compare("DYNAMIC-LIBRARY") == 0) 
            m_build_type = CppBuildType::DYNAMIC_LIBRARY;
        else if(build_type_str.compare("HEADER-ONLY") == 0) 
            m_build_type = CppBuildType::HEADER_ONLY;
        else 
            throw std::runtime_error("No correct build type defined in the JSON file !");
    } catch(const std::exception& exception) {
        throw std::runtime_error(exception.what());
    }
}

std::vector<std::string> fock::CppProject::GetSources() const noexcept
{
    return m_sources;
}

std::vector<std::string> fock::CppProject::GetModules() const noexcept
{
    return m_modules;
}

std::vector<std::string> fock::CppProject::GetIncludeDirectories() const noexcept
{
    return m_include_directories;
}

std::vector<std::string> fock::CppProject::GetLibraries() const noexcept
{
    return m_libraries;
}

std::vector<std::string> fock::CppProject::GetLibraryDirectories() const noexcept
{
    return m_library_directories;
}

fock::CppBuildType fock::CppProject::GetBuildType() const noexcept
{
    return m_build_type;
}
