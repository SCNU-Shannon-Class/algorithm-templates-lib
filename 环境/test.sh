#!/bin/bash

# 检查是否提供了文件名
if [ $# -eq 0 ]; then
    echo "err0"
    exit 1
fi


n="$1"

# 检查可执行文件是否存在
if [ ! -x "$n" ]; then
    echo "err1"
    exit 1
fi

# 查找以 n 开头的 .in 文件
f=("${n}"*.in)

# 遍历每个匹配的输入文件
for x in "${f[@]}"; do
    # 生成对应的输出文件名
    ans="${x%.in}.ans"
    out="${x%.in}.out"

    # 检查输出文件是否存在
    if [ ! -f "$ans" ]; then
        echo "not find $ans"
        exit 1
    fi

    # 执行程序并将结果重定向到输出文件
    "./$n" < "$x" > "$out"

    # 比较结果
    # 这里一定要完全相同！！，所以一定要写好.ans文件
    if ! diff -q "$out" "$ans"; then
        echo "WA"
        diff "$out" "$ans"  # 可选，查看具体差异
        exit 1
    fi
done

echo "AC"