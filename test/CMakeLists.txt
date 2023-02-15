set(PROJECT ChatClientTest)

set(SOURCES
    color_test.cc  
    parameter_test.cc    
    command_test.cc
    json_serializer_test.cc
    http_plugin_test.cc
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
