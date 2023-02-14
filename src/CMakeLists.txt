cmake_minimum_required(VERSION 3.8)

set(PROJECT ChatClient)

add_compile_options(-fprofile-arcs -ftest-coverage)

set(SOURCES
    hardtoname.cc hardtoname.h
    command/login.cc
    command/signup.cc
    util/util.cc
)

add_library(${PROJECT} STATIC ${SOURCES})
target_link_libraries(${PROJECT}
    PUBLIC
        curl
        jsoncpp
        gcov
)

set(PROJECT chat_client)
set(SOURCES
    main.cc
    command/login.cc
    command/signup.cc
)


add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT}
    PUBLIC
        curl
        jsoncpp
        ChatClient
)