set(PROJECT ChatClientTest)

set(SOURCES
    cache_test.cc
    functionality.cc
    command_test.cc
    color_test.cc  
    parameter_test.cc
    json_serializer_test.cc
    http_plugin_test.cc
    signup_request_test.cc
    repository/chat_repository_test.cc
    repository/room_repository_test.cc
    repository/user_repository_test.cc    
)

add_executable(${PROJECT} ${SOURCES})

find_library(gmock_path NAMES libgmock.a)
add_library(gmock STATIC IMPORTED)
set_target_properties(gmock PROPERTIES IMPORTED_LOCATION ${gmock_path})

target_link_libraries(${PROJECT}
    PUBLIC
        gtest
        gtest_main
        gmock
        curl
        jsoncpp
        ChatClient
)

add_test(
    NAME ${PROJECT}
    COMMAND ${PROJECT}
)
