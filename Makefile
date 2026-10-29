# Makefile
.PHONY: all meson cmake clean

# 默认目标：全部构建
all: meson cmake

# meson 构建：debug 版本，支持 reconfigure
meson:
	meson setup build/debug --buildtype=debug --reconfigure
	meson compile -C build/debug

# cmake 构建，使用 Ninja 生成器，--fresh 清空缓存
cmake:
	cmake -S . -B build/cmake -G Ninja --fresh
	cmake --build build/cmake

# 清理
clean:
	rm -rf build/debug build/cmake

