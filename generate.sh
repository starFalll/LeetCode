# !/bin/bash

# 检查是否提供了数字作为输入参数
if [ $# -eq 0 ]; then
    echo "Usage: $0 <number1> <number2> ..."
    exit 1
fi
# 输出文件
output_file="Top_Interview_Questions.md"

# 清空输出文件（如果存在）
> "$output_file"
cd algorithms


# 循环处理每个数字参数
for number in "$@"; do
    # 构造文件名
    filename=`ls | grep "^${number}\."`

    # 检查文件是否存在
    if [ ! -f "$filename" ]; then
        echo "File ${number} not found."
        continue
    fi

    # 合并文件内容到输出文件
    cat "$filename" >> "../$output_file"
    echo "Merged content of $filename"
done

echo "Files merged successfully into $output_file"

