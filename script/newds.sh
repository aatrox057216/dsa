#!/bin/bash
# newds.sh
set -euo pipefail

if [ $# -ne 1 ]; then
    echo "usage: $0 SqList"
    exit 1
fi
NAME="$1"

# 目录列表
DIRS=("include" "src" "demo")
for d in "${DIRS[@]}"; do
    if [ ! -d "$d" ]; then
        mkdir -p "$d"
        echo "mkdir $d"
    fi
done

# 创建源文件（不存在才touch，不覆盖）
H_FILE="include/${NAME}.h"
C_FILE="src/${NAME}.c"
DEMO_FILE="demo/demo_${NAME}.c"
for f in "$H_FILE" "$C_FILE" "$DEMO_FILE"; do
    if [ ! -f "$f" ]; then
        touch "$f"
        echo "Created $f"
    else
        echo "Skip exists: $f"
    fi
done

# --------------------------
# 追加 meson.build
# --------------------------
MESON_TARGET="executable('demo_${NAME}', 'demo/demo_${NAME}.c',
  include_directories: inc_dir,
  link_with: libds,
  c_args: c_args
)"
if ! grep -q "exe_${NAME}" meson.build; then
    echo >> meson.build
    echo "$MESON_TARGET" >> meson.build
    echo "[meson.build] appended exe_${NAME}"
else
    echo "[meson.build] exe_${NAME} already exists, skip"
fi

# --------------------------
# 追加 CMakeLists.txt
# --------------------------
CMAKE_TARGET="add_executable(demo_${NAME} demo/demo_${NAME}.c)
target_link_libraries(demo_${NAME} PRIVATE ds)"
if ! grep -q "demo_${NAME}" CMakeLists.txt; then
    echo >> CMakeLists.txt
    echo "$CMAKE_TARGET" >> CMakeLists.txt
    echo "[CMakeLists.txt] appended demo_${NAME}"
else
    echo "[CMakeLists.txt] demo_${NAME} already exists, skip"
fi

# --------------------------
# 重新 configure meson
# --------------------------
echo "Run meson reconfigure..."
meson setup build/debug --buildtype=debug --reconfigure

echo "Done. New data structure: $NAME"
