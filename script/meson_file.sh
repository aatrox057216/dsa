#!/bin/sh
# 获取脚本所在目录
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
# 项目根目录 = 脚本目录的上一级
PROJ_ROOT=$(cd "${SCRIPT_DIR}/.." && pwd)

# 方式A：glob 遍历 src/*.c
for cfile in "${PROJ_ROOT}/src"/*.c; do
  # 排除不存在的情况（src为空时glob会保留字面字符串）
  [ -f "${cfile}" ] && echo "${cfile}"
done

# 方式B：find 版本（二选一，不要同时两个都输出）
# find "${PROJ_ROOT}/src" -maxdepth 1 -type f -name "*.c"
