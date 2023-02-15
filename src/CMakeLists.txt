cmake_minimum_required(VERSION 3.8)

set(PROJECT ChatClient)

add_compile_options(-fprofile-arcs -ftest-coverage)

set(SOURCES
    hardtoname.cc hardtoname.h
    http_client.cc http_client.h
    http_plugin.h
    plugin/curl_client.cc plugin/curl_client.h
    plugin/curl/repository/user_http_repository.cc
    plugin/curl/repository/user_http_repository.h
    plugin/curl/converter/user_dto_converter.h
    plugin/curl/converter/user_dto_converter.cc
    request.cc request.h
    response.h
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
