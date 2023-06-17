#! /bin/bash
# 自动push，参数为conmmit内容
# push script
git status
git add -A
git status
git commit -m "$*"
git push origin master
echo "git commit $*"
