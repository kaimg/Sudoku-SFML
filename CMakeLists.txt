cmake_minimum_required(VERSION 3.10)
project(Sudoku VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable warnings and debug symbols in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MSVC)
        add_compile_options(/W4 /WX)
    else()
        add_compile_options(-Wall -Wextra -Wpedantic -g)
    endif()
endif()

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Define source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        sfml-graphics 
        sfml-window 
        sfml-system
        sfml-audio
)

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Install resources
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources
    DESTINATION share/${PROJECT_NAME}
)

# Copy resources to build directory for development
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${CMAKE_CURRENT_BINARY_DIR}/resources
) 