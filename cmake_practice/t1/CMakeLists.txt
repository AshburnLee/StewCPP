cmake_minimum_required(VERSION 3.22)
project(HELLO_C1)

# 将src子目录加入工程，编译结果包括中间结果放在 build/my_bin/中
# 在src/下的CMakeFiles.txt 中添加set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/my_bin)
add_subdirectory(src my_bin)

# 将lib子目录加入工程，编译结果包括中间结果放在 build/my_lib/中
# 在lib/下的CMakeFiles.txt 中添加set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/my_lib)
add_subdirectory(lib my_lib) 
