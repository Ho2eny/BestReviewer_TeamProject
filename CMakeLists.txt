cmake_minimum_required(VERSION 3.8)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll" ".dll.a" ".a" ".lib")
set(CMAKE_FIND_LIBRARY_PREFIXES "cyg" "lib")

find_package(CURL REQUIRED)
if(NOT(CURL_FOUND))
    message(FATAL_ERROR "Could not find CURL")
endif()

find_package(Jsoncpp REQUIRED)
if(NOT(Jsoncpp_FOUND))
    message(FATAL_ERROR "Could not find LibJsoncpp")
endif()

set(PROJECT ChatClient)

project(${PROJECT})

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
add_subdirectory(test)