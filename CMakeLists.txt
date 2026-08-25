cmake_minimum_required(VERSION 3.10)

project(utility
    VERSION 1.0.0
    DESCRIPTION "A comprehensive C++ utilities library tailored for the development of modern desktop and extended reality (XR) applications."
    HOMEPAGE_URL "https://etib-corp.github.io/utility"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 01. Policy & standard setup

# 02. Options & configuration
option(BUILD_DOCS "Build Doxygen documentation" OFF)
option(BUILD_DOCS_ONLY "Configure only the documentation target" OFF)

if(BUILD_DOCS_ONLY)
    set(BUILD_DOCS ON)
    set(BUILD_TESTING OFF)
endif()

# 03. Global properties
include(FetchContent)


if(NOT BUILD_DOCS_ONLY)
    # Fetch external dependencies
    FetchContent_Declare(
        tinyobjloader
        GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git
        GIT_TAG release
    )
    # tinyobjloader may call add_sanitizers() even when the helper module is unavailable.
    if(NOT COMMAND add_sanitizers)
        function(add_sanitizers)
        endfunction()
    endif()
    FetchContent_MakeAvailable(tinyobjloader)

    set(GLM_BUILD_TESTS OFF)

    add_compile_definitions(GLM_FORCE_RADIANS)
    add_compile_definitions(GLM_FORCE_DEPTH_ZERO_TO_ONE)

    FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(glm)

    set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

    # Ensure FreeType is configured without HarfBuzz.
    set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "Disable HarfBuzz in FreeType" FORCE)
    set(FT_REQUIRE_HARFBUZZ OFF CACHE BOOL "Do not require HarfBuzz in FreeType" FORCE)

    FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
        GIT_TAG VER-2-14-3
    )
    FetchContent_MakeAvailable(freetype)

    FetchContent_Declare(stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(stb)

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.2.0
    )
    set(FMT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(FMT_INSTALL OFF CACHE BOOL "" FORCE)
    set(FMT_OS_X_VERSION 10.15 CACHE STRING "" FORCE)
    FetchContent_MakeAvailable(fmt)

    # Disable building examples, tests, and utilities for OpenAL Soft
    set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
    set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
    set(ALSOFT_INSTALL OFF CACHE BOOL "" FORCE)

    # Force OpenAL to NOT use its bundled fmt and instead use the project-wide fmt
    set(ALSOFT_USE_BUNDLED_FMT OFF CACHE BOOL "" FORCE)
    set(ALSOFT_CONFIG_FMT "fmt" CACHE STRING "" FORCE)

    FetchContent_Declare(openal
        GIT_REPOSITORY https://github.com/kcat/openal-soft.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(openal)

    FetchContent_Declare(
        dr_libs
        GIT_REPOSITORY https://github.com/mackron/dr_libs.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(dr_libs)

    # Set the files directories
    set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/headers")
    set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources")

    # Add the headers directories
    include_directories(
        ${HEADERS_DIR}
    )

    # Add the source files
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${SOURCES_DIR}/*.cpp"
    )

    # 04. Library definition
    add_library(${PROJECT_NAME} ${SOURCES})

    # 06. Compile definitions
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
            GLM_ENABLE_EXPERIMENTAL
    )

    # 07. Link dependencies
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            tinyobjloader
            glm
            freetype
            fmt::fmt
            OpenAL::OpenAL
    )

    if(WIN32)
        target_link_libraries(${PROJECT_NAME}
            PUBLIC
                Dbghelp
        )
    endif()

    # 05. Include directories
    target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${HEADERS_DIR}>
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${stb_SOURCE_DIR}>
            $<BUILD_INTERFACE:${dr_libs_SOURCE_DIR}>
    )

    # 10. Install & export rules
    # Allow downstream projects to consume the library via find_package().

    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    set(UTILITY_INSTALL_CMAKEDIR
        "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(DIRECTORY ${HEADERS_DIR}/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.hpp"
    )

    install(EXPORT ${PROJECT_NAME}Targets
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${UTILITY_INSTALL_CMAKEDIR}
    )

    configure_package_config_file(
        cmake/${PROJECT_NAME}Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION ${UTILITY_INSTALL_CMAKEDIR}
    )

    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${UTILITY_INSTALL_CMAKEDIR}
    )
endif()

# 08. Documentations

if(BUILD_DOCS)
    message(STATUS "Building documentation...")
    include(cmake/Docs.cmake)
    add_project_docs()
else()
    message(STATUS "Skipping documentation...")
endif()

# 09. Tests

if(BUILD_TESTING)
    message(STATUS "Building tests...")
    add_subdirectory(tests)
else()
    message(STATUS "Skipping tests...")
endif()