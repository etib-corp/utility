cmake_minimum_required(VERSION 3.10)

include(FetchContent)

project(utility
    VERSION 1.0.0
    DESCRIPTION "Utility"
    HOMEPAGE_URL "https://etib-corp.github.io/utility"
    LANGUAGES CXX
)

# Include common functions
include(cmake/CommonFunctions.cmake)

# Platform-specific configuration
if(WIN32)
    include(cmake/ConfigWindows.cmake)
elseif(APPLE)
    include(cmake/ConfigMacOS.cmake)
elseif(UNIX)
    include(cmake/ConfigLinux.cmake)
endif()

# Set global C++ standard and properties
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Set the files directories
set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/headers")
set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sources")

# Fetch GLM library
set(GLM_BUILD_TESTS OFF)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(glm)

# Add the headers directories
include_directories(
    ${HEADERS_DIR}
)

# Add the source files
file(GLOB_RECURSE SOURCES
    "${SOURCES_DIR}/*.cpp"
)

# Create the main library
add_library(${PROJECT_NAME} ${SOURCES})

# Link dependencies
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    glm::glm 
)

# Set common target properties
set_utility_target_properties(${PROJECT_NAME})

# Configure public interface
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${HEADERS_DIR}>
        $<INSTALL_INTERFACE:include>
)

# Set library output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Optional components
option(BUILD_TESTING "Build the tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_EXAMPLES "Build the examples" OFF)

if(BUILD_TESTING)
    message(STATUS "Building tests...")
    add_subdirectory(tests)
else()
    message(STATUS "Skipping tests...")
endif()

if(BUILD_DOCS)
    message(STATUS "Building docs...")
    add_subdirectory(docs)
else()
    message(STATUS "Skipping docs...")
endif()

if(BUILD_EXAMPLES)
    message(STATUS "Building examples...")
    add_subdirectory(examples)
else()
    message(STATUS "Skipping examples...")
endif()
