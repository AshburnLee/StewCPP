# 默认为空
message("exe output: ${EXECUTABLE_OUTPUT_PATH}")
message("lib output: ${LIBRARY_OUTPUT_PATH}")
# 默认是build/
message("bin dir: ${PROJECT_BINARY_DIR}")

# 设置bin和lib的生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/my_bin)


message("exe output: ${EXECUTABLE_OUTPUT_PATH}")
message("lib output: ${LIBRARY_OUTPUT_PATH}")

# Adds an executable target called ``hell_c1`` to be built from the source:main.cpp
add_executable(hello_c1 main.cpp)


