# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (agent)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/hello.cpp
)


find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)

add_subdirectory(benchmark)

# Add an executable
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include/
)

# link against the boost libraries
target_link_libraries( ${PROJECT_NAME}
    PRIVATE
    	zmq
        Threads::Threads
        benchmark::benchmark
)
