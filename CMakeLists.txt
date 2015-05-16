cmake_minimum_required(VERSION 2.6)

project("Chronos")
enable_testing()

find_package(CURL)
find_package(Threads)
find_package(OpenSSL)
find_package(Boost COMPONENTS date_time filesystem random regex system thread)

include_directories("src")
include_directories("include")
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})

add_definitions("-std=c++11")

# Chronos components
add_subdirectory(src)

# Web components
add_subdirectory(web)

add_dependencies(chronos-server-lib chronos-web)

add_executable(chronos src/main/chronos.cpp)
add_dependencies(chronos-server-lib chronos-web)
target_link_libraries(
    chronos
    chronos-server-lib
    atlas-web
    )

