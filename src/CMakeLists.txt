cmake_minimum_required(VERSION 3.8)

set(PROJECT ChatClient)

add_compile_options(-fprofile-arcs -ftest-coverage)

set(SOURCES
    http/http_plugin.h
    http/thirdparty/curl/curl_client.cc 
    http/thirdparty/curl/curl_client.h
    http/repository/chat_http_repository.cc
    http/repository/chat_http_repository.h
    http/repository/user_http_repository.cc
    http/repository/user_http_repository.h
    http/repository/room_http_repository.cc
    http/repository/room_http_repository.h
    http/converter/chat_dto_converter.h
    http/converter/chat_dto_converter.cc
    http/converter/user_dto_converter.h
    http/converter/user_dto_converter.cc
    http/converter/room_dto_converter.h
    http/converter/room_dto_converter.cc
    http/dto/request.cc http/dto/request.h
    http/dto/response.h
    utils.h
    utils.cc
    command/cache.h command/cache.cc
    command/invoker.h command/invoker.cc
    command/command.h command/command.cc
    command/parameter_validator.h command/parameter_validator.cc
    command/factory/command_creator.h
    command/factory/command_creator.cc
    command/factory/receiver_creator.h
    command/factory/receiver_creator.cc
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
