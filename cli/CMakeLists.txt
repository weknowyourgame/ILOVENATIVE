# CLI CMakeLists.txt
# Simple CMake configuration for ILOVENATIVE CLI application

cmake_minimum_required(VERSION 3.16)

# Project name and version
project(ILOVENATIVE_CLI VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable all warnings for better code quality
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
set(CLI_SOURCES
    main.cpp
    command_handler.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${CLI_SOURCES})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Include current directory for headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add compile definitions for better user experience
target_compile_definitions(${PROJECT_NAME} PRIVATE
    PROJECT_NAME="${PROJECT_NAME}"
    PROJECT_VERSION="${PROJECT_VERSION}"
)

# Find and link required packages (none needed for basic CLI)
# The application only uses standard C++ library

# Installation (optional)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Print configuration summary
message(STATUS "=== ILOVENATIVE CLI Configuration ===")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output directory: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "=====================================")
