# 严蔚敏《数据结构》C语言版 — Meson 实验环境搭建

> 背景：严书代码是经典C风格，大量自定义结构体（顺序表、链表、栈、队列、树、图），头文件`.h` + 实现`.c` + 各个实验主程序`main_xxx.c`。
> 目标：用 Meson 管理项目，一键编译、支持 Zed/Neovim clangd（自动生成`compile_commands.json`），分离构建目录，不用手写Makefile。
> 环境：WSL Ubuntu 26.04 + GCC-16 + Meson 1.12.1

## 一、推荐目录结构（直接建好）

```
ds-yan/
├── meson.build          # Meson主构建文件
├── include/             # 所有头文件：SqList.h、LinkList.h、Stack.h ...
│   ├── SqList.h
│   ├── LinkList.h
│   └── ...
├── src/                 # 数据结构实现 .c
│   ├── SqList.c
│   ├── LinkList.c
│   └── ...
├── demo/                # 各个实验主程序（多个可执行程序，每个实验单独一个exe）
│   ├── main_sqlist.c
│   ├── main_linklist.c
│   └── main_tree.c
└── build/
    └── meson/           # meson setup 输出目录
```

## 二、meson.build 完整配置

```

project('ds-yan-data-structure', 'c',
  meson_version: '>=1.12'
)



# 下面保留你原有代码不变
c_args = [
  '-Wall',
  '-Wextra',
  '-std=c89'
]

inc_dir = include_directory('include')

ds_src = glob('src/*.c')

libds = static_library('ds', ds_src,
  include_directories: inc_dir,
  c_args: c_args
)

exe_sqlist = executable('demo_sqlist', 'demo/main_sqlist.c',
  include_directories: inc_dir,
  link_with: libds,
  c_args: c_args
)

```

## 三、WSL 执行命令

```
# 在项目根目录 ds-yan/
# 1. 初始化构建目录 build/meson
meson setup build/meson

# 2. 编译全部实验程序
meson compile -C build/meson

# 3. 运行某个实验，例如顺序表demo
./build/meson/demo_sqlist
```

> 生成 `build/meson/compile_commands.json`，Zed / Neovim clangd 自动读取，跳转头文件、静态检查。

## 四、最小示例代码测试（快速验证环境）

`include/SqList.h`

```
#ifndef SQLIST_H
#define SQLIST_H

#define MAXSIZE 100
typedef int ElemType;

typedef struct{
    ElemType data[MAXSIZE];
    int length;
}SqList;

void InitList(SqList *L);
void PrintList(SqList *L);

#endif
```

`src/SqList.c`

```
#include "SqList.h"
#include <stdio.h>

void InitList(SqList *L){
    L->length = 0;
}

void PrintList(SqList *L){
    for(int i=0; i<L->length; i++){
        printf("%d ", L->data[i]);
    }
    printf("\n");
}
```

`demo/main_sqlist.c`

```
#include "SqList.h"

int main(){
    SqList L;
    InitList(&L);
    L.data[0]=10;
    L.data[1]=20;
    L.length=2;
    PrintList(&L);
    return 0;
}
```

## 五、扩展使用方式

### 新增实验步骤

1. 在 `demo/` 新建 `main_xxx.c`
2. 在 meson.build 末尾新增一段 executable 代码，和上面demo写法一致
3. 直接 `meson compile -C build/meson`，自动增量编译，不会重编所有文件

### 切换C标准（严书部分代码也可以用c99）

修改 `c_args`：

```
c_args = [
  '-Wall',
  '-Wextra',
  '-std=c99'
]
```

### 清理项目

```
rm -rf build/meson
```

## 六、对应CMake版本（方便你对比Meson/CMake两套配置）

> CMakeLists.txt，同目录结构

```
cmake_minimum_required(VERSION 3.20)
project(ds-yan C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c89")
include_directories(include)

file(GLOB DS_SRC src/*.c)
add_library(ds STATIC ${DS_SRC})

add_executable(demo_sqlist demo/main_sqlist.c)
target_link_libraries(demo_sqlist ds)

add_executable(demo_linklist demo/main_linklist.c)
target_link_libraries(demo_linklist ds)

add_executable(demo_bitree demo/main_tree.c)
target_link_libraries(demo_bitree ds)
```

CMake构建命令

```
cmake -B build/cmake -S .
cmake --build build/cmake
```

## 七、Meson优势适配数据结构实验

1. **声明式**：只描述“要产出什么库/程序”，不用写编译步骤；非图灵完备，逻辑简单。
2. 增量编译：只编译改动的`.c`，写算法反复调试很舒服。
3. 自动生成 compile_commands.json，编辑器代码跳转、语法检查。
4. 可以方便切换编译器：`CC=gcc-15 meson setup build/meson`

如果你想要，我可以：

1. 直接给一套完整严蔚敏顺序表+链表+栈+队列+二叉树全套头文件源码，直接丢进项目跑
2. 或者增加单元测试（meson test），给每个数据结构写简单测试用例。

你打算先做：单元测试集成，还是直接全套基础数据结构源码？
