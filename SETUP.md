
## Build Environment

#### Windows 10 with Cygwin
1. Run Cygwin installer (https://cygwin.com/setup-x86_64.exe)
    * cygwin이 이미 설치되어 있는 경우, setup-x86_64.exe 실행 후 필요한 packages 추가 설치
    * cygwin을 다시 설치하는 경우, 이전 cygwin 폴더 (default path: C:\cygwin64) 삭제 후 setup-x86_64.exe 실행
   
2. Install required packages : **gcc-g++, gcc-core, cmake, make, libcurl-devel, libjsoncpp-devel, gcovr, python36**   

    ![cygwin_select_pkg](https://media.github.ecodesamsung.com/user/3415/files/9ff54879-8682-4c04-ab84-82a87bfe09fd)
   
3. Change Python version on Cygwin    
    * Select python3.6
        ```
        $ /usr/sbin/update-alternatives --config python

        There are 2 programs which provide 'python'.

        Selection    Command
        -----------------------------------------------
        1           /usr/bin/python3.6
        *+ 2           /usr/bin/python3.9

        Enter to keep the current selection[+], or type selection number: 1
        ``` 

        ```
        $ /usr/sbin/update-alternatives --config python3

        There are 2 programs which provide 'python3'.

        Selection    Command
        -----------------------------------------------
        1           /usr/bin/python3.6
        *+ 2           /usr/bin/python3.9

        Enter to keep the current selection[+], or type selection number: 1
        ``` 
    * Check python version
        ```
        $ python -V
        Python 3.6.15

        $ python3 -V
        Python 3.6.15
        
        $ ls -al /etc/alternatives/python*
        lrwxrwxrwx 1 CORP+andy.shlee CORP+Domain Users 18 Jun 22 16:07 /etc/alternatives/python -> /usr/bin/python3.6
        lrwxrwxrwx 1 CORP+andy.shlee CORP+Domain Users 18 Jun 22 16:11 /etc/alternatives/python3 -> /usr/bin/python3.6
        ```

4. Install GoogleTest on Cygwin (https://github.com/google/googletest/releases)
    ```
    CORP+andy.shlee@andy-shlee01 /cygdrive/d/test/googletest-master
    $ mkdir build

    CORP+andy.shlee@andy-shlee01 /cygdrive/d/test/googletest-master
    $ cd build

    CORP+andy.shlee@andy-shlee01 /cygdrive/d/test/googletest-master/build
    $ cmake ..
    -- The C compiler identification is GNU 7.4.0
    :

    CORP+andy.shlee@andy-shlee01 /cygdrive/d/test/googletest-master/build
    $ make
    Scanning dependencies of target gtest
    [ 12%] Building CXX object CMakeFiles/gtest.dir/src/gtest-all.cc.o
    :

    CORP+andy.shlee@andy-shlee01 /cygdrive/d/test/googletest-master/build
    $ make install

    $ cp /usr/local/lib/libgtest* /usr/lib/
    ```
