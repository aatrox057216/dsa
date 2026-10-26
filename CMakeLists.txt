cmake_minimum_required(VERSION 3.20)
project(ds-yan-data-structure C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON) # gnu11

# 编译参数
add_compile_options(-Wall -Wextra)

# 头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# ========== 方案A：沿用你原来的 meson_file.sh 脚本（和meson行为对齐） ==========
# 注意：Windows下需要有bash环境(WSL/git bash)才能跑这个sh脚本
#execute_process(
#    COMMAND bash ${PROJECT_SOURCE_DIR}/script/meson_file.sh
#    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#    OUTPUT_VARIABLE ds_src_raw
#    RESULT_VARIABLE sh_ret
#)
#if(NOT sh_ret EQUAL 0)
#    message(FATAL_ERROR "script/meson_file.sh run failed")
#endif()
#string(REPLACE "\n" ";" ds_src "${ds_src_raw}")
#list(FILTER ds_src EXCLUDE REGEX "^$") # 剔除空行

# ========== 方案B（推荐，注释掉方案A，打开这个，不用shell脚本） ==========
file(GLOB_RECURSE ds_src CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/*.c
 )

# 静态库 libds.a
add_library(ds STATIC ${ds_src})
target_include_directories(ds PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(ds PRIVATE -Wall -Wextra)

# 可执行文件 demo_StaticList
add_executable(demo_StaticList demo/demo_StaticList.c)
target_link_libraries(demo_StaticList PRIVATE ds)
