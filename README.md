
# Team Project (C++)

## 23-2차 팀프로젝트 시간표
![팀프로젝트시간표_23-1 2](https://media.github.ecodesamsung.com/user/3415/files/21d09bb0-6cff-4e09-90b9-720b12aec410)



## C++ 프로젝트 basic template
 - 기본적인 http request 기능
 - 기본적인 json parsing, writing 기능
 - 테스트 케이스

## Build Environment

#### Windows 10 with Cygwin

## How to build
```
CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP
$ mkdir build

CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP
$ cd build/

CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP/build
$ cmake ..
  :
-- Configuring done
-- Generating done
-- Build files have been written to: /cygdrive/d/TeamProj/cpp/TeamProj_CPP/build

CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP/build
$ make
Scanning dependencies of target ChatClient
[ 16%] Building CXX object src/CMakeFiles/ChatClient.dir/hardtoname.cc.o
[ 33%] Linking CXX static library libChatClient.a
  :
[100%] Linking CXX executable ChatClientTest.exe
[100%] Built target ChatClientTest
```

## How to run & test   
1. Run the execution program in **Cygwin terminal**
    ```
    CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP/build
    $ ./src/chat_client.exe
    11.welcome_simpleJson, 12.parse json, 13.assemble json
    21.welcome_arrayJson, 22.parse json, 33.assemble json
    Enter command(q for quit) : 11
    OK to curl : 200, {"message":"Welcome to Best Reviewer"}

    11.welcome_simpleJson, 12.parse json, 13.assemble json
    21.welcome_arrayJson, 22.parse json, 33.assemble json
    Enter command(q for quit) : 12
    Welcome to Best Reviewer
    11.welcome_simpleJson, 12.parse json, 13.assemble json
    21.welcome_arrayJson, 22.parse json, 33.assemble json
    Enter command(q for quit) : 13
    Easy to compose JSON string
    {
            "message" : "Easy to compose JSON string"
    }
    11.welcome_simpleJson, 12.parse json, 13.assemble json
    21.welcome_arrayJson, 22.parse json, 33.assemble json
    Enter command(q for quit) : 21
    [{"message":"Welcome to Best Reviewer 0"},{"message":"Welcome to Best Reviewer 1"},{"message":"Welcome to Best Reviewer 2"}]
    11.welcome_simpleJson, 12.parse json, 13.assemble json
    21.welcome_arrayJson, 22.parse json, 33.assemble json
    Enter command(q for quit) :
    ```

2. Run the google test in **Cygwin terminal**
    ```
    CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP/build
    $ ./test/ChatClientTest.exe
    Running main() from /cygdrive/d/TeamProj/googletest-master/googletest-master/googletest/src/gtest_main.cc
    [==========] Running 6 tests from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 6 tests from HttpRequestTest
    [ RUN      ] HttpRequestTest.getSimpleJsonbyHttpRequest
    [       OK ] HttpRequestTest.getSimpleJsonbyHttpRequest (0 ms)
    [ RUN      ] HttpRequestTest.parseSimpleJson
    [       OK ] HttpRequestTest.parseSimpleJson (0 ms)
    [ RUN      ] HttpRequestTest.composeSimpleJson
    [       OK ] HttpRequestTest.composeSimpleJson (0 ms)
    [ RUN      ] HttpRequestTest.getArrayJsonbyHttpRequest
    [       OK ] HttpRequestTest.getArrayJsonbyHttpRequest (11 ms)
    [ RUN      ] HttpRequestTest.parseArrayJson
    {
            "message" : "Welcome to Best Reviewer 0"
    }
    detailed message with forLoop: Welcome to Best Reviewer 0
    {
            "message" : "Welcome to Best Reviewer 1"
    }
    detailed message with forLoop: Welcome to Best Reviewer 1
    {
            "message" : "Welcome to Best Reviewer 2"
    }
    detailed message with forLoop: Welcome to Best Reviewer 2
    0: {
            "message" : "Welcome to Best Reviewer 0"
    }
    detailed message with ItrLoop: Welcome to Best Reviewer 0
    1: {
            "message" : "Welcome to Best Reviewer 1"
    }
    detailed message with ItrLoop: Welcome to Best Reviewer 1
    2: {
            "message" : "Welcome to Best Reviewer 2"
    }
    detailed message with ItrLoop: Welcome to Best Reviewer 2
    [       OK ] HttpRequestTest.parseArrayJson (0 ms)
    [ RUN      ] HttpRequestTest.composeArrayJson
    [       OK ] HttpRequestTest.composeArrayJson (0 ms)
    [----------] 6 tests from HttpRequestTest (11 ms total)

    [----------] Global test environment tear-down
    [==========] 6 tests from 1 test suite ran. (11 ms total)
    [  PASSED  ] 6 tests.
    ```

## How to measure coverage using gcovr
1. Check gcno and gcda files **after build and test**

    ```
    CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP
    $ find . -name *gcda -print
    ./build/src/CMakeFiles/ChatClient.dir/hardtoname.cc.gcda
    ./build/src/CMakeFiles/chat_client.dir/main.cc.gcda

    CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP
    $ find . -name *gcno -print
    ./build/src/CMakeFiles/ChatClient.dir/hardtoname.cc.gcno
    ./build/src/CMakeFiles/chat_client.dir/main.cc.gcno
    ```
2. Run gcovr in the project **root directory**
    ```
    CORP+andy.shlee@andy-shlee01 /cygdrive/d/TeamProj/cpp/TeamProj_CPP
    $ gcovr
    ------------------------------------------------------------------------------
                            GCC Code Coverage Report
    Directory: .
    ------------------------------------------------------------------------------
    File                                       Lines    Exec  Cover   Missing
    ------------------------------------------------------------------------------
    src/hardtoname.cc                             35      34    97%    [* 38]
    src/main.cc                                   53      52    98%   67
    ------------------------------------------------------------------------------
    TOTAL                                         88      86    97%
    ------------------------------------------------------------------------------
    ```
