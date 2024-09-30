#pragma once

namespace fock
{
    /*
    This enumeration represent all the available build types for a C++ program.
    You can build :
      - An executable
      - A header-only library
      - A static library
      - A dynamic library
    */
    enum class CppBuildType
    {
        EXECUTABLE,
        HEADER_ONLY,
        STATIC_LIBRARY,
        DYNAMIC_LIBRARY
    };
}
