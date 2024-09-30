#include <fock/projects/project.hpp>

fock::Project::Project(const std::string_view & filepath) :
    m_name(""),
    m_description("")
{
    try {
        // Open file
        std::ifstream file(filepath.data());
        if(file.is_open() == false)
            throw std::runtime_error("Can't open the JSON project file !");

        // Parse JSON
        m_json_data = nlohmann::json::parse(file);

        // Close the file
        if(file.is_open() == true)
            file.close();

        // Read configurations
        m_build_directory = ReadConfiguration<std::string>("fock-project", "build-directory");
        m_name = ReadConfiguration<std::string>("fock-project", "name");
        m_description = ReadConfiguration<std::string>("fock-project", "description");

        // Read array configurations
        CopyJsonDataToArray<std::string>("fock-project", "authors", m_authors);
        CopyJsonDataToArray<int>("fock-project", "version", m_version);
    } catch(const std::exception& exception) {
        throw std::runtime_error(exception.what());
    }
}

fock::Project::~Project()
{
    if(m_json_data.is_null() == false)
        m_json_data.clear();
}

std::string fock::Project::GetName() const noexcept
{
    return m_name;
}

std::string fock::Project::GetDescription() const noexcept
{
    return m_description;
}

std::string fock::Project::GetBuildDirectory() const noexcept
{
    return m_build_directory;
}

std::vector<std::string> fock::Project::GetAuthors() const noexcept
{
    return m_authors;
}

std::vector<int> fock::Project::GetVersion() const noexcept
{
    return m_version;
}