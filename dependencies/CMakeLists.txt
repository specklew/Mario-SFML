include(FetchContent)

#SFML
set(SFML_VERSION "2.5.1")

FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG        "${SFML_VERSION}"
)

message(STATUS "Declaring sfml to fetch...")

set(SOURCE_FILES
        stb/stb_image.h
        animatedgifs/include/AnimatedGif.h
        animatedgifs/src/AnimatedGif.cpp)
add_library(stb ${SOURCE_FILES})
target_include_directories(stb PUBLIC stb animatedgifs/include)

add_subdirectory(sfml)