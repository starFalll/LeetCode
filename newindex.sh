#! /bin/bash
#每次push之前先运行此脚本
for num in $*
do
    all=$(ls algorithms|sort -n)
    line=$(echo "${all}"|grep -n "^${num}\..*")
    echo "${line}"
    title=`echo ${line}|cut -d . -f 2`
    declare -l url=${title}
    newline=$(echo ${line}| cut -d : -f 2)
    declare -i num=$(echo ${line}|cut -d : -f 1)
    res=$(echo "|${newline%%.*}|[$title](https://leetcode.com/problems/${url//' '/'-'}/description/)|[C++](https://github.com/starFalll/LeetCode/blob/master/algorithms/${newline//' '/'%20'})|")
    num=num+6
    sed -i ''${num}'i\'"${res}"'' README.md
done
