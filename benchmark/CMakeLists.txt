# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set a default C++ compile flag
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" CACHE STRING "Set C++ Compiler Flags" FORCE)
SET( CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -DNVALGRIND" CACHE STRING "" FORCE )

# Set the project name
project (benchmark)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    ../src/hello.cpp
    benchmark1
)


find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/../include/
)

# link against the boost libraries
target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        Threads::Threads
        benchmark::benchmark
)
