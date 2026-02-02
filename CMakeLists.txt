cmake_minimum_required(VERSION 3.15)
project(Advent-of-Code-2025 VERSION 1.0.0 LANGUAGES C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ensure debug symbols and no optimization for Debug builds
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

# Compiler warnings
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.c")
list(FILTER SOURCES EXCLUDE REGEX ".*main\\.c$")

# Debug: Print what files were found
message(STATUS "Found source files: ${SOURCES}")

# Create library first
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME}_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_compile_definitions(${PROJECT_NAME}_lib PUBLIC _POSIX_C_SOURCE=200809L)

# Create executable
add_executable(${PROJECT_NAME} src/main.c)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
target_compile_definitions(${PROJECT_NAME} PRIVATE _POSIX_C_SOURCE=200809L PROJECT_ROOT="${PROJECT_SOURCE_DIR}")

# Installation rules (optional)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
