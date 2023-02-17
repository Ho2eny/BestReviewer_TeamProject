
# Team Project_FIFO

## Members
- 김동혁
- 김철희
- 문선아
- 임채중
- 허인

## 구현 기능
1. 계정 생성
2. Login
3. Loginout
4. 모든 채팅방 보기
5. 채팅방 생성
6. 채팅방 참여(join)

## 실행 및 결과
- 실행 방법
```
$ src/chat_client.exe 
======================================
========== FIFO Chat Client ==========
======================================

MENU
> q. Quit Application
> quit. Quit Application
> 50. Sign up for the program
> 51. Log in to the program
> 52. Log  out of the program
> 60. List all rooms
> 61. Create a room
> 62. Join a room

> Waiting for a command... : 50
> Enter ID : fifo_test
> Enter Password: password123
Signed up to FIFO Chat with fifo_test
```
- 결과
TODO: 캡쳐 붙이기..!

## 테스트 및 결과
```
$ test/ChatClientTest.exe 
Running main() from /WorkSpace/googletest-main/googletest/src/gtest_main.cc
[==========] Running 64 tests from 9 test suites.
[----------] Global test environment set-up.     
[----------] 27 tests from RepositoryTestFixture 
[ RUN      ] RepositoryTestFixture.loginSuccess  

// skipping...

[----------] Global test environment tear-down
[==========] 64 tests from 9 test suites ran. (299 ms total)
[  PASSED  ] 64 tests.
```

## Coverage
https://pages.github.ecodesamsung.com/Best-Reviewer-23-2/TeamProject_FIFO
