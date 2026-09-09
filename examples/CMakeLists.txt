# Utility examples

option(BUILD_EXAMPLES "Build the runnable examples" OFF)

if(BUILD_EXAMPLES)
    add_subdirectory(cache)
    add_subdirectory(graphic_colors)
    add_subdirectory(math_matrices)
    add_subdirectory(sound_mp3)
    add_subdirectory(math_vectors)
endif()
