set(PROJECT ChatClientTest)

set(SOURCES
    functionality.cc
    color_test.cc  
    parameter_test.cc
    json_serializer_test.cc
    http_plugin_test.cc
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
