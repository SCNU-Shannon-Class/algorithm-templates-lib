在你的比赛目录下新建脚本，整个脚本的作用域是当前目录

脚本错误情况见脚本注释，也可以不写错误情况以方便抄写

# 使用

## 设置权限(必要)
```sh
chmod 777 [脚本名字.sh]
```

## 编译
编译获得exe(这里设置好编译器也可以，这个脚本可以不写)
```sh
./run.sh [完整文件名]
```

## 测试
将目录下的.in文件生成对应的.out文件，并比较.ans文件

+ .in和.ans要一致 
+ .out和.ans要完全一致(包括空格和回车)，否则会出问题，所以可以手动设置好.ans的格式
+ 你输入的参赛代表.in文件的**前缀**
```sh
./test.sh [要测试的.in文件前缀]
```

# run.sh
```sh
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
```

# test.sh
```sh
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
```