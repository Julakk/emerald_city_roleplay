cmake_minimum_required(VERSION 3.15)
project(ecrp_client_plugin LANGUAGES CXX)

# SA-MP client (samp.exe) itu 32-bit, jadi DLL plugin WAJIB 32-bit juga.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ecrp SHARED
    src/main.cpp
    src/hook.cpp
)

target_include_directories(ecrp PRIVATE include)

# Link library D3D9 buat hook rendering.
target_link_libraries(ecrp PRIVATE d3d9)

set_target_properties(ecrp PROPERTIES
    OUTPUT_NAME "ecrp_client"
    PREFIX ""
)
