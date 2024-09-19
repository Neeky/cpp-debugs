cmake_minimum_required(VERSION 3.10)
project(cpp-debugs)
find_package(fmt CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

add_executable(cpp-multi-threads src/cpp-multi-threads.cpp)
add_executable(cpp-symbols src/cpp-symbols.cpp)
add_executable(cpp-off-cpus src/cpp-off-cpus.cpp)

target_link_libraries(cpp-multi-threads PRIVATE fmt::fmt)
target_link_libraries(cpp-multi-threads PRIVATE cxxopts::cxxopts)
target_link_libraries(cpp-symbols PRIVATE cxxopts::cxxopts)
target_link_libraries(cpp-off-cpus PRIVATE cxxopts::cxxopts)
