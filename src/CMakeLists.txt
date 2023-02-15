cmake_minimum_required(VERSION 3.8)

set(PROJECT ChatClient)

add_compile_options(-fprofile-arcs -ftest-coverage)

set(SOURCES
    http/http_plugin.h
    http/thirdparty/curl/curl_client.cc 
    http/thirdparty/curl/curl_client.h
    http/repository/user_http_repository.cc
    http/repository/user_http_repository.h
    http/converter/user_dto_converter.h
    http/converter/user_dto_converter.cc
    http/dto/request.cc http/dto/request.h
    http/dto/response.h
    utils.h
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
)


add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT}
    PUBLIC
        curl
        jsoncpp
        ChatClient
)
