#include <fock/builders/msvc_builder.hpp>

std::string fock::MSVCBuilder::GetCommandToCompileSources(const fock::CppProject & project, const std::vector<std::string> & additional_compiler_params) const
{
    // Command params
    std::string params("");
    std::string includes("");
    std::string sources("");

    // Add additional compiler params
    if(additional_compiler_params.size() > 0)
    {
        for(const std::string & param : additional_compiler_params)
        {
            params += param;
            params += " ";
        }
    }

    // Add include directories
    if(project.GetIncludeDirectories().size() > 0)
    {
        for(const std::string & dir : project.GetIncludeDirectories())
        {
            includes += "/I\"";
            includes += dir;
            includes += "\" ";
        }
    }

    // Add source files
    if(project.GetSources().size() > 0)
    {
        for(const std::string & file : project.GetSources())
        {
            sources += file;
            sources += " ";
        }
    } else {
        throw std::runtime_error("No sources to compile !");
    }

    // Return the command from format string
    return std::format("cl /c /TP /ifcSearchDir {0}/ /Fo:{0}/ {1} {2} {3}", project.GetBuildDirectory(), params, includes, sources);
}

std::string fock::MSVCBuilder::GetCommandToCompileModules(const fock::CppProject & project, const std::vector<std::string> & additional_compiler_params) const
{
    // Command params
    std::string params("");
    std::string includes("");
    std::string modules("");

    // Add additional compiler params
    if(additional_compiler_params.size() > 0)
    {
        for(const std::string & param : additional_compiler_params)
        {
            params += param;
            params += " ";
        }
    }

    // Add include directories
    if(project.GetIncludeDirectories().size() > 0)
    {
        for(const std::string & dir : project.GetIncludeDirectories())
        {
            includes += "/I\"";
            includes += dir;
            includes += "\" ";
        }
    }

    // Add modules files
    if(project.GetModules().size() > 0)
    {
        for(const std::string & file : project.GetModules())
        {
            modules += file;
            modules += " ";
        }
    } else {
        throw std::runtime_error("No modules to compile !");
    }

    // Get command string from format string
    return std::format("cl /c /TP /ifcSearchDir {0}/ /ifcOutput {0}/ /Fo:{0}/ {1} {2} {3}", project.GetBuildDirectory(), params, includes, modules);
}

std::string fock::MSVCBuilder::GetCommandToCreateExecutable(const fock::CppProject & project, const std::vector<std::string> & additional_linker_params) const
{
    // Params
    std::string params("");
    std::string module_objects("");
    std::string source_objects("");
    std::string library_directories("");
    std::string libraries("");

    // Add additional linker params
    if(additional_linker_params.size() > 0)
    {
        for(const std::string & param : additional_linker_params)
        {
            params += param;
            params += " ";
        }
    }

    // Add source objects files
    if(project.GetSources().size() > 0)
    {
        for(const std::string & path : project.GetSources())
        {
            // Get source name
            std::string source_name = fock::GetFileNameFromPath(path);
            source_objects += project.GetBuildDirectory();
            source_objects += "/";
            source_objects += source_name;
            source_objects += ".obj";
            source_objects += " ";
        }
    }

    // Add module objects files
    if(project.GetModules().size() > 0)
    {
        for(const std::string & path : project.GetModules())
        {
            // Get module name
            std::string module_name = fock::GetFileNameFromPath(path);
            module_objects += project.GetBuildDirectory();
            module_objects += "/";
            module_objects += module_name;
            module_objects += ".obj";
            module_objects += " ";
        }
    }

    // Add static library directories
    if(project.GetLibraryDirectories().size() > 0)
    {
        for(const std::string & lib : project.GetLibraryDirectories())
        {
            library_directories += "/LIBPATH:";
            library_directories += "\"";
            library_directories += lib;
            library_directories += "\" ";
        }
    }

    // Add static libraries
    if(project.GetLibraries().size() > 0)
    {
        for(const std::string & lib : project.GetLibraries())
        {
            libraries += lib;
            libraries += " ";
        }
    }

    // Get command string from format string
    return std::format("link /OUT:{0}/{1}.exe {2} {3} {4} {5} {6}", project.GetBuildDirectory(), project.GetName(), 
                        params, library_directories, libraries, module_objects, source_objects);
}

void fock::MSVCBuilder::CompileSources(const fock::CppProject & project, const std::vector<std::string> & additional_compiler_params) const
{
    // Get the command to compile sources
    std::string command = GetCommandToCompileSources(project, additional_compiler_params);

    // System call
    try {
        fock::CallSystemCommand(command);
    } catch (const std::exception & exception) {
        throw std::runtime_error(exception.what());
    }
}

void fock::MSVCBuilder::CompileModules(const fock::CppProject & project, const std::vector<std::string> & additional_compiler_params) const
{
    // Get the command to compile sources
    const std::string command = GetCommandToCompileModules(project, additional_compiler_params);

    // System call
    try {
        fock::CallSystemCommand(command);
    } catch (const std::exception & exception) {
        throw std::runtime_error(exception.what());
    }
}

void fock::MSVCBuilder::CreateExecutable(const fock::CppProject & project, const std::vector<std::string> & additional_linker_params) const
{
    // Get the command to compile sources
    const std::string command = GetCommandToCreateExecutable(project, additional_linker_params);

    // System call
    try {
        fock::CallSystemCommand(command);
    } catch (const std::exception & exception) {
        throw std::runtime_error(exception.what());
    }
}

std::vector<std::string> fock::MSVCBuilder::GetCompilerParams(const fock::CppProject & project) const
{
    std::vector<std::string> additional_compiler_params;
    project.CopyJsonDataToArray<std::string>("msvc", "compiler-parameters", additional_compiler_params);
    return additional_compiler_params;
}

std::vector<std::string> fock::MSVCBuilder::GetLinkerParams(const fock::CppProject & project) const
{
    std::vector<std::string> additional_linker_params;
    project.CopyJsonDataToArray<std::string>("msvc", "linker-parameters", additional_linker_params);
    return additional_linker_params;
}

void fock::MSVCBuilder::Build(const fock::CppProject & project) const
{
    // Get MSVC configurations from the cpp build file and get additionals params
    std::vector<std::string> additional_compiler_params;
    std::vector<std::string> additional_linker_params;
    project.CopyJsonDataToArray<std::string>("msvc", "compiler-parameters", additional_compiler_params);
    project.CopyJsonDataToArray<std::string>("msvc", "linker-parameters", additional_linker_params);

    // Build the project (Compile and link if it is possible)
    bool can_link = false;
    switch (project.GetBuildType())
    {
    case fock::CppBuildType::EXECUTABLE:

        // If modules files present
        if(project.GetModules().size() > 0)
        {
            // Compile modules
            CompileModules(project, additional_compiler_params);
            can_link = true;
        }

        // If sources files present
        if(project.GetSources().size() > 0)
        {
            // Compile sources, and then create the executable
            CompileSources(project, additional_compiler_params);
            can_link = true;
        }

        // If we can link
        if(can_link == true)
        {
            // Create the executable
            CreateExecutable(project, additional_linker_params);
        } else {
            throw std::runtime_error("Can't link because no sources or modules was compiled !");
        }

        break;
    case fock::CppBuildType::STATIC_LIBRARY:
        break;
    }
}