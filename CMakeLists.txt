cmake_minimum_required(VERSION 3.28)
project(BlockBlast)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(src/include)

file(GLOB SOURCES "src/*.cpp")

file(GLOB_RECURSE FONT_FILES CONFIGURE_DEPENDS "assets/fonts/*/*.ttf")

file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS "assets/shaders/*.frag")

add_custom_target(copy_fonts ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FONT_FILES} ${CMAKE_BINARY_DIR}/fonts
    DEPENDS ${FONT_FILES}
)

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHADER_FILES} ${CMAKE_BINARY_DIR}/shaders
    DEPENDS ${SHADER_FILES}
)

add_executable(main ${SOURCES})

add_dependencies(main copy_fonts)
add_dependencies(main copy_shaders)

target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE SFML::Graphics)
