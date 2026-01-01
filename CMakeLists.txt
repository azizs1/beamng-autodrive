cmake_minimum_required(VERSION 3.20)
project(beamng-autodrive LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wno-deprecated-anon-enum-enum-conversion)

# Let CMake find packages installed by vcpkg
# make sure that `./vcpkg integrate install` is already done in ~/vcpkg
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

# equivalent to -pthread
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
