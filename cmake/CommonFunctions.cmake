# Common functions for Utility project

# Function to set common target properties
function(set_utility_target_properties TARGET_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

    # Add platform-specific compile definitions
    if(WIN32)
        target_compile_definitions(${TARGET_NAME} PRIVATE OS_WINDOWS)
    elseif(APPLE)
        target_compile_definitions(${TARGET_NAME} PRIVATE OS_MACOS)
    elseif(UNIX)
        target_compile_definitions(${TARGET_NAME} PRIVATE OS_LINUX)
    endif()
endfunction()
