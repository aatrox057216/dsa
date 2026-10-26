project('ds-yan-data-structure', 'c',
  meson_version: '>=1.12',
  version: '0.0.1'
)

# 全局编译参数：开启警告，适配严蔚敏C代码（C89/ANSI C，可选）
c_args = [
  '-Wall',
  '-Wextra',
  '-std=gnu11'
]

# 头文件目录
inc_dir = include_directories('include')

# 收集所有底层数据结构实现源码
meson_file = run_command('script/meson_file.sh', check: true)
ds_src = meson_file.stdout().strip().split('\n')

# 编译静态库：把所有数据结构封装成 libds.a，所有实验demo链接这个库
libds = static_library('ds', ds_src,
  include_directories: inc_dir,
  c_args: c_args
)

# ========== 多个实验可执行文件 ==========
# 顺序表实验
exe_sqlist = executable('demo_StaticList', 'demo/demo_StaticList.c',
  include_directories: inc_dir,
  link_with: libds,
  c_args: c_args
)
exe_sqlist = executable('demo_SqList', 'demo/demo_SqList.c',
  include_directories: inc_dir,
  link_with: libds,
  c_args: c_args
)
