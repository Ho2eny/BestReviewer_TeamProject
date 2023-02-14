set(PROJECT ChatClientTest)

set(SOURCES
    hardtonametest.cc
    api_test.cc
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