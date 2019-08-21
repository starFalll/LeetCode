#! /bin/bash
#针对之前从未整理过的文件进行整理，请根据自己的目录结构修改
ls algorithms| grep '^[0-9]'|sort -n|while read line
do
    title=`echo ${line}|cut -d . -f 2`
    declare -l url=${title}
    echo "|${line%%.*}|[$title](https://leetcode.com/problems/algorithms/${url//' '/'-'}/description/)|[C++](https://github.com/starFalll/LeetCode/blob/master/algorithms/${line//' '/'%20'})|" >>README.md 
done
