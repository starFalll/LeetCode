#! /bin/bash
# 针对之前从未整理过的文件进行整理，请根据自己的目录结构修改
# Organize the previously unsorted files and modify according to your own directory structure.
# usage: ./initindex.sh

echo "# LeetCode

LeetCode Solution

| #    | Title                                                                                                                                                               | Solution                                                                                                                                            |
|:---- |:-------------------------------------------------------------------------------------------------------------------------------------------------------------------:| ---------------------------------------------------------------------------------------------------------------------------------------------------:|" > README.md
ls algorithms| grep '^[0-9]'|sort -n|while read line
do
    title=`echo ${line}|cut -d . -f 2`
    url=$(echo $title | awk '{print tolower($0)}')
    echo "|${line%%.*}|[$title](https://leetcode.com/problems/${url//' '/-}/description/)|[C++](https://github.com/starFalll/LeetCode/blob/master/algorithms/${line//' '/%20})|" >>README.md 
done
