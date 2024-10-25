#!/bin/bash

# 检查是否提供了文件名
if [ $# -eq 0 ]; then
    echo "err0"
    exit 1
fi

# 获取输入的文件名
n=$1

# 检查文件是否存在
if [ ! -f "$n" ]; then
    echo "err1"
    exit 1
fi

# 生成没有后缀的可执行文件名
out="${n%.cpp}"

# 执行编译命令
# 根据评测机设置编译命令
g++ -g -O2 -std=gnu++20 -static "$n" -o "$out"

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "OK"
else
    echo "err2"
fi