set(LIBHEY_SRC hey.cpp)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/my_lib)


# 从 LIBHEY_SRC 添加一个 target lib 生成 MY_LIB_HEY
# Adds a library target called ``my_hey_lib`` to be built from the source files
# 生成my_lib/libmy_hey_lib.so  动态库
add_library(my_hey_sh SHARED ${LIBHEY_SRC})

# 生成my_lib/libmy_hey_lib.a   静态库
add_library(my_hey_st STATIC ${LIBHEY_SRC})

# 库不能重名，用一下指令，可以改成重名
set_target_properties(my_hey_sh PROPERTIES OUTPUT_NAME "hey_lib")
set_target_properties(my_hey_st PROPERTIES OUTPUT_NAME "hey_lib")

