This folder is for CMakeLists.txt in practice

## CMakeLists.txt 语法


## Learn from others

- 编译选项

    编译选项通常是在CMakeLists.txt 中或者option.cmake 文件中的 `option()` 函数中指定，如

    `option(DNNL_BUILD_EXAMPLES "builds examples"  ON)` 

    在`cmake .. -DDNNL_BUILD_EXAMPLES=OFF` 指定不编译examples

- 对于project t1, make 之后的log：

    ```
    [ 16%] Building CXX object my_bin/CMakeFiles/hello_c1.dir/main.cpp.o
    [ 33%] Linking CXX executable hello_c1
    [ 33%] Built target hello_c1
    [ 50%] Building CXX object my_lib/CMakeFiles/my_hey_sh.dir/hey.cpp.o
    [ 66%] Linking CXX shared library libhey_lib.so
    [ 66%] Built target my_hey_sh
    [ 83%] Building CXX object my_lib/CMakeFiles/my_hey_st.dir/hey.cpp.o
    [100%] Linking CXX static library libhey_lib.a
    [100%] Built target my_hey_st
    ```


## minimum files maximum structure

【一个复杂项目都包含哪些内容】

## maximum files minimum structure

见根目录的CMakeLists.txt，只有一个源文件，其他都是头文件
