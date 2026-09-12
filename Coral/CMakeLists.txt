cmake_minimum_required(VERSION 3.15)
project(Coral LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(
    $<$<PLATFORM_ID:Windows>:CORAL_WINDOWS>
    $<$<PLATFORM_ID:Linux>:CORAL_LINUX>
    $<$<PLATFORM_ID:Darwin>:CORAL_MACOSX>
)

file(GLOB_RECURSE SOURCE_DIR "Source/**.cpp")
add_library(Coral STATIC ${SOURCE_DIR})

target_precompile_headers(Coral PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/CoralPCH.hpp")

target_include_directories(Coral PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Source" 
    "${CMAKE_CURRENT_SOURCE_DIR}/NetCore"
)
