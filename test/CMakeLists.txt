set(PROJECT ChatClientTest)

set(SOURCES
    command_test.cc
    json_serializer_test.cc
    hardtonametest.cc 
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
