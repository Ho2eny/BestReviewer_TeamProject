set(PROJECT ChatClientTest)

set(SOURCES
    parameter_test.cc    
    command_test.cc
    json_serializer_test.cc
    http_client_test.cc
)

add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT}
    PUBLIC
        gtest
        gtest_main
        curl
        jsoncpp
        ChatClient
)

add_test(
    NAME ${PROJECT}
    COMMAND ${PROJECT}
)
