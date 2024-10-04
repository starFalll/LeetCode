### 7.Letter Combinations of a Phone Number

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

![img](http://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png)

**Example:**

```
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].


```

**Note:**

Although the above answer is in lexicographical order, your answer could be in any order you want.

#### 解析

同样是使用回溯法。

#### 代码

```cpp
class Solution {
private:
    const vector<string> keywords={" "," ","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};//0-9
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        string path;
        if(digits.empty()) return res;
        dfs(digits,0,path,res);
        return res;
    }
    void dfs(const string& digits,int len,string& path,vector<string>& res)
    {
        if(len==digits.size())
        {
            res.push_back(path);
            return;
        }
        for(auto i:keywords[digits[len]-'0']){
            path.push_back(i);
            dfs(digits,len+1,path,res);
            path.pop_back();
        }
    }
};
```

### 8.String to Integer (atoi)

Implement `atoi` which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

**Note:**

- Only the space character `' '` is considered as whitespace character.
- Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.

**Example 1:**

```
Input: "42"
Output: 42


```

**Example 2:**

```
Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.


```

**Example 3:**

```
Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.


```

**Example 4:**

```
Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.

```

**Example 5:**

```
Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.
```

#### 解析

细节题，注意：

- 不规则输入
- 无效格式
- 溢出数据

#### 代码

```cpp
class Solution {
public:
    int myAtoi(string str) {
        if(str.empty())
            return 0;
        long long res=0;
        int flag=0;//0 -> positive number ,1->negative number
        int j=0;
        while(str[j]==' ')
            j++;
        if(str[j]=='-'){
            flag=1;
            j++;
        }
        else if(str[j]=='+'){
            flag=0;
            j++;
        }
        for(;j<str.size();j++){
            
            int tmp=str[j]-'0';
            if(tmp<0||tmp>9){
                break;
            }
            res*=10;  
            res+=tmp;
            if(flag==1&&(-res)<INT_MIN)//out of the range of representable values
            {
                
                return INT_MIN;
            }
                
            else if((flag==0)&&(res>INT_MAX))
                return INT_MAX;
        }
        if(flag==1)
            res=-res;
        return (int)res;
    }
};
```

### 10.Regular Expression Matching

Given an input string (`s`) and a pattern (`p`), implement regular expression matching with support for `'.'` and `'*'`.

```
'.' Matches any single character.
'*' Matches zero or more of the preceding element.


```

The matching should cover the **entire** input string (not partial).

**Note:**

- `s` could be empty and contains only lowercase letters `a-z`.
- `p` could be empty and contains only lowercase letters `a-z`, and characters like `.` or `*`.

**Example 1:**

```
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".


```

**Example 2:**

```
Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".


```

**Example 3:**

```
Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".


```

**Example 4:**

```
Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".


```

**Example 5:**

```
Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
```

#### 解析

`dp[i][j]` indicates whether the first i characters of string s and the first j characters of pattern p match.

$$dp[i][j] = 
\begin{cases}
dp[i][j - 2] \lor (i \land dp[i - 1][j] \land (s[i - 1] = p[j - 2] \lor p[j - 2] = '.')), & \text{if } p_{j-1} is a star \\
i \land dp[i - 1][j - 1] \land (s[i - 1] = p[j - 1] \lor p[j - 1] = '.'), & \text{if } p_j \text{ is not a star} \\
\text{False}, & \text{otherwise}
\end{cases}$$

$`dp[0][0]=True`$

#### 代码

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2] || (i && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                } else {
                    dp[i][j] = i && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }
        return dp[m][n];
    }
};
```

### 26.Remove Duplicates from Sorted Array

Given a sorted array *nums*, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that each element appear only *once* and return the new length.

Do not allocate extra space for another array, you must do this by **modifying the input array in-place** with O(1) extra memory.

#### 代码1

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        auto it1 = nums.begin()+1;
        auto it2 = nums.begin();
        for(;it1<nums.end();it1++){
            if(*it1!=*it2){
                it2=it1;
            }
            else{
                nums.erase(it1);
                it1=it2;
            }
        }
        
        return nums.size();
        
    }
};
```

#### 代码2

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty())
            return 0;
        int index = 0;
        for(int i=1;i<nums.size();i++){
            if(nums[i] != nums[index])
                nums[++index]=nums[i];
        }
        return index+1;
        
    }
};
```

#### 代码3

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        return distance(nums.begin(),unique(nums.begin(),nums.end()));
    }
};
```

### ### 28.Implement strStr()

Implement [strStr()](http://www.cplusplus.com/reference/cstring/strstr/).

Return the index of the first occurrence of needle in haystack, or **-1** if needle is not part of haystack.

**Example 1:**

```
Input: haystack = "hello", needle = "ll"
Output: 2


```

**Example 2:**

```
Input: haystack = "aaaaa", needle = "bba"
Output: -1


```

**Clarification:**

What should we return when `needle` is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when `needle` is an empty string. This is consistent to C's [strstr()](http://www.cplusplus.com/reference/cstring/strstr/) and Java's [indexOf()](https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#indexOf(java.lang.String)).

#### 解析

字符串匹配，可以使用暴力或者kmp，面试的时候暴力即可，但是要bug free

注意，类似于i\<haystack.size()-needle.size()+1，当i=0时候仍然会判true，因为c++中容器的size返回的是size_t类型，大小由机器位数决定，32位机器为4字节无符号数，64位为8字节无符号数，所以haystack.size()-needle.size()+1\>0

#### 代码

暴力：

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.size()==0) return 0;
        const int n=haystack.size()-needle.size()+1;
        for(int i=0;i<n;i++){
            if(haystack[i]==needle[0]){
                int j=0,k=i;
                while(j<needle.size()&&k<haystack.size()){
                    if(haystack[k]!=needle[j])
                        break;
                    j++;k++;
                }
                if(j==needle.size())
                    return i;
            }
        }
        return -1;
    }
};
```

### 29.Divide Two Integers

Given two integers `dividend` and `divisor`, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing `dividend` by `divisor`.

The integer division should truncate toward zero.

**Example 1:**

```
Input: dividend = 10, divisor = 3
Output: 3
```

**Example 2:**

```
Input: dividend = 7, divisor = -3
Output: -2
```

**Note:**

- Both dividend and divisor will be 32-bit signed integers.
- The divisor will never be 0.
- Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.

#### 解析

移位减，加快运算，注意溢出。

#### 代码

```c++
class Solution {
public:
    int divide(int dividend, int divisor) {
        long long a = dividend > 0 ? dividend : -(long long)dividend;
        long long b = divisor > 0 ? divisor : -(long long)divisor;
        long long res = 0;
        while (a >= b) {
            long long c = b;
            for (int i = 0; a >= c; i++, c<<=1) {
                a -= c;
                res += (1<<i);
            }
        }
        bool flag = (dividend >= 0 && divisor > 0 || dividend < 0 && divisor < 0) ? true : false;
        if (flag && res > INT_MAX) return INT_MAX;
        long long min_val = INT_MIN;
        if (!flag && res > -min_val) return INT_MIN;
        if (!flag) res = -res;
        return res;
    }
};
```

### 36.Valid Sudoku

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated **according to the following rules**:

1. Each row must contain the digits `1-9` without repetition.
2. Each column must contain the digits `1-9` without repetition.
3. Each of the 9 `3x3` sub-boxes of the grid must contain the digits `1-9` without repetition.

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png)
A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character `'.'`.

**Example 1:**

```
Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true

```

**Example 2:**

```
Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being 
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

```

**Note:**

- A Sudoku board (partially filled) could be valid but is not necessarily solvable.
- Only the filled cells need to be validated according to the mentioned rules.
- The given board contain only digits `1-9` and the character `'.'`.
- The given board size is always `9x9`.

#### 代码

```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<int> uniq(9,0);
        for(int i=0;i<9;i++){//check row
            for(int j=0;j<9;j++){
                if(board[i][j]>='1'&&board[i][j]<='9'){
                    uniq[board[i][j]-'1']++;
                    if(uniq[board[i][j]-'1']>1)
                        return false;
                }
            }
            returnzero(uniq);
        }
        for(int i=0;i<9;i++){//check column
            for(int j=0;j<9;j++){
                if(board[j][i]>='1'&&board[j][i]<='9'){
                    uniq[board[j][i]-'1']++;
                    if(uniq[board[j][i]-'1']>1)
                        return false;
                }
            }
            returnzero(uniq);
        }
        
        for(int m=0;m<9;m+=3){//check 3*3 box
            for(int k=0;k<9;k+=3){
                for(int i=m;i<m+3;i++){
                    for(int j=k;j<k+3;j++){
                        if(board[i][j]>='1'&&board[i][j]<='9'){
                            uniq[board[i][j]-'1']++;
                            if(uniq[board[i][j]-'1']>1)
                                return false;
                        }
                    }
                    
                }
                returnzero(uniq);
            }
        }
        return true;
        
    }
    void returnzero(vector<int>& a)
    {
        for(int i=0;i<a.size();i++)
            a[i]=0;
    }
};
```

### ### 38.Count and Say

The count-and-say sequence is the sequence of integers with the first five terms as following:

```
1.     1
2.     11
3.     21
4.     1211
5.     111221


```

`1` is read off as `"one 1"` or `11`.
`11` is read off as `"two 1s"` or `21`.
`21` is read off as `"one 2`, then `one 1"` or `1211`.

Given an integer *n* where 1 ≤ *n* ≤ 30, generate the *n*th term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

 

**Example 1:**

```
Input: 1
Output: "1"


```

**Example 2:**

```
Input: 4
Output: "1211"
```

#### 解析

这道题的题意很难理解，题意是n=1时输出字符串1；n=2时，数上次字符串中的数值个数，因为上次字符串有1个1，所以输出11；n=3时，由于上次字符是11，有2个1，所以输出21；n=4时，由于上次字符串是21，有1个2和1个1，所以输出1211。依次类推，写个countAndSay(n)函数返回字符串。

#### 代码

```cpp
class Solution {
public:
    string countAndSay(int n) {
        string ret="1";
        if(n==1)
            return ret;
        string tmp;
        while(--n>0){
            tmp=ret;
            ret="";
            int len=tmp.size();
            int i=0;
            while(i<len){
                int j=i+1;
                while(j<len&&j-i<9&&tmp[i]==tmp[j]) j++;
                ret+=((j-i)+'0');
                ret+=tmp[i];
                i=j;
            }
        }
        return ret;
    }
};
```





### 44.Wildcard Matching

Given an input string (`s`) and a pattern (`p`), implement wildcard pattern matching with support for `'?'` and `'*'`.

```
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).


```

The matching should cover the **entire** input string (not partial).

**Note:**

- `s` could be empty and contains only lowercase letters `a-z`.
- `p` could be empty and contains only lowercase letters `a-z`, and characters like `?` or `*`.

**Example 1:**

```
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".


```

**Example 2:**

```
Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.


```

**Example 3:**

```
Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.


```

**Example 4:**

```
Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".


```

**Example 5:**

```
Input:
s = "acdcb"
p = "a*c?b"
Output: false
```

#### 解析

`dp[i][j]` indicates whether the first i characters of string s and the first j characters of pattern p match.

$$dp[i][j] = 
\begin{cases}
dp[i-1][j-1], & \text{if } s_i \text{ is equal to } p_j \text{ or } p_j \text{ is a question mark} \\
dp[i][j-1] \lor dp[i-1][j], & \text{if } p_j \text{ is a star} \\
\text{False}, & \text{otherwise}
\end{cases}$$

$`dp[0][0]=True, dp[i][0] = False.`$

$`dp[0][j] = True, \text{when When the first j characters are all stars}`$

#### 代码

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        dp[0][0] = true;

        for (int i = 1; i <= m; i++) {
            if (p[i-1] == '*') {
                dp[0][i] = true;
            }
            else break;
        }
        if (s.empty()) return dp[0][m];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i-1] == p[j-1] || p[j-1] == '?') {
                    dp[i][j] = dp[i-1][j-1];
                }
                else if (p[j-1] == '*') {
                    dp[i][j] = dp[i][j-1] || dp[i-1][j];
                }
                else {
                    dp[i][j] = false;
                }
            }
        }
        return dp[n][m];
    }
};
```

### 50.Pow(x, n)

Implement [pow(*x*, *n*)](http://www.cplusplus.com/reference/valarray/pow/), which calculates *x* raised to the power *n* (xn).

**Example 1:**

```
Input: 2.00000, 10
Output: 1024.00000


```

**Example 2:**

```
Input: 2.10000, 3
Output: 9.26100


```

**Example 3:**

```
Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25


```

**Note:**

- -100.0 < *x* < 100.0
- *n* is a 32-bit signed integer, within the range [−231, 231 − 1]

#### 解析

二分法，$x^n = x^{n/2} \times x^{n/2} \times x^{n\%2}$

#### 代码

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if(n<0) return (1.0)/power(x,-n);
        return power(x,n);
    }
    double power(double x,int n)
    {
        if(n==0) return 1;
        double v=power(x,n/2);
        if(n%2==0) return v*v;
        else return v*v*x;
    }
};
```

### 66.Plus One

Given a **non-empty** array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

**Example 1:**

```
Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.


```

**Example 2:**

```
Input: [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
```

#### 代码

```cpp
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        bool flag;
        for(int i=digits.size()-1;i>=0;i--){
            if(i==0){
                if(digits[i]+1>9){
                    digits[i]=(digits[i]+1)%10;
                    digits.insert(digits.begin(),1);
                    break;
                }
                else{
                    digits[i]=digits[i]+1;
                    break;
                }    
            }
            else{
                flag=false;
                if(digits[i]+1>9){
                    flag=true;
                }
                digits[i]=(digits[i]+1)%10;
                if(flag==false)
                    break;
            }
               
        }
        return digits;
    }
};
```

### 69.Sqrt(x)

Implement `int sqrt(int x)`.

Compute and return the square root of *x*, where *x* is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

**Example 1:**

```
Input: 4
Output: 2


```

**Example 2:**

```
Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.
```

#### 解析

二分法。

#### 代码

```cpp
class Solution {
public:
    int mySqrt(int x) {
        if(x==0) return 0;
        if(x==1||x==2)return 1;
        int high=x/2;
        int low=1;
        int last=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(x/mid<mid){
                high=mid-1;
            }
            else if(x/mid>mid){
                low=mid+1;
                last=mid;
            }
            else
                return mid;
        }
        return last;
    }
};
```

### 88.Merge Sorted Array

Given two sorted integer arrays *nums1* and *nums2*, merge *nums2* into *nums1* as one sorted array.

**Note:**

- The number of elements initialized in *nums1* and *nums2* are *m* and *n* respectively.
- You may assume that *nums1* has enough space (size that is greater or equal to *m* + *n*) to hold additional elements from *nums2*.

**Example:**

```
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]
```

#### 解析

nums1的空间大于等于 m+n，则可以从末尾往前排序。

#### 代码

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=m+n-1;
        int l1=m-1;
        int l2=n-1;
        while(l1>=0&&l2>=0){
            nums1[i--]=nums2[l2]>=nums1[l1]?nums2[l2--]:nums1[l1--];
        }
        while(l2>=0){
            nums1[i--]=nums2[l2--];
        }
    }
};
```

### 91.Decode Ways

A message containing letters from `A-Z` is being encoded to numbers using the following mapping:

```
'A' -> 1
'B' -> 2
...
'Z' -> 26

```

Given a **non-empty** string containing only digits, determine the total number of ways to decode it.

**Example 1:**

```
Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).

```

**Example 2:**

```
Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
```

#### 解析

Special Fibonacci sequence

f(n) How many encodings are there for a string ending with s[n-1]

```
f(n) = f(n-1)+f(n-2)
// f(n) can add f(n-1) if s[n-1] is valid
// f(n) can add f(n-2) if s[n-2, n-1] is valid
f(0) = 1  
f(1) = 1 // s=12, f(2) = f(0)+f(1) = 2
```

#### 代码

```c++
class Solution {
public:
    int numDecodings(string s) {
        if(s.empty()) return 0;
        if(s.size()==1&&s[0]!='0') return 1;
        if(s[0]=='0') return 0;
        int a = 1, b = 1;
        int res = 0;
        int len = s.size();
        for(int i = 1;i<len;++i)
        {
            res = 0;
            if(!invalid(s[i-1],s[i])&&!invalid(s[i])) return 0;
            if(invalid(s[i])) res+=b;
            if(invalid(s[i-1],s[i])) res+=a;
            a = b;
            b = res;
        }
        return res;
    }
    bool invalid(char a, char b)
    {
        return (a=='1'||a=='2'&&b<='6');
    }
    bool invalid(char a)
    {
        return a != '0';
    }
};
```

### 103.Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the *zigzag level order* traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7


```

return its zigzag level order traversal as:

```
[
  [3],
  [20,9],
  [15,7]
]
```

#### 解析

每隔一层反转一次。

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        queue<TreeNode*> q,next;
        q.push(root);
        bool flag=false;//false for postive
        while(!q.empty()){
            vector<int> line;
            while(!q.empty()){   
                TreeNode* tmp=q.front();
                q.pop();
                line.push_back(tmp->val);
                if(tmp->left) next.push(tmp->left);
                if(tmp->right) next.push(tmp->right);
                
            }
            if(flag){
                reverse(line.begin(),line.end());
                flag=false;
            }
            else
                flag=true;
            res.push_back(line);
            swap(q,next);
        }
        return res;
    }
};
```

### 108.Convert Sorted Array to Binary Search Tree

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of *every* node never differ by more than 1.

**Example:**

```
Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums,0,nums.size());
        
    }
    TreeNode* sortedArrayToBST(vector<int>& nums,int low,int hight)
    {
        if(low>=hight) return nullptr;
        int mid=(hight+low)/2;
        TreeNode* root=new TreeNode(nums[mid]);
        root->left=sortedArrayToBST(nums,low,mid);
        root->right=sortedArrayToBST(nums,mid+1,hight);
        return root;
    }
    
};
```

### 116.Populating Next Right Pointers in Each Node

Given a binary tree

```
struct TreeLinkNode {
  TreeLinkNode *left;
  TreeLinkNode *right;
  TreeLinkNode *next;
}


```

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to `NULL`.

Initially, all next pointers are set to `NULL`.

**Note:**

- You may only use constant extra space.
- Recursive approach is fine, implicit stack space does not count as extra space for this problem.
- You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

**Example:**

Given the following perfect binary tree,

```
     1
   /  \
  2    3
 / \  / \
4  5  6  7


```

After calling your function, the tree should look like:

```
     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \  / \
4->5->6->7 -> NULL
```

#### 代码

1.通用版本，不仅仅适用于完全二叉树

```cpp
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        while(root){
            TreeLinkNode* prev=nullptr;
            TreeLinkNode* next=nullptr;
            for(;root;root=root->next){
                if(!next) next=root->left?root->left:root->right;
                if(root->left){
                    if(prev) prev->next=root->left;
                    prev=root->left;
                }
                if(root->right){
                    if(prev) prev->next=root->right;
                    prev=root->right;
                }
            }
            root=next;
        }
    }
};
```

2.仅仅适用于完全二叉树

```cpp
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        if(!root->left&&!root->right) return;
        root->left->next=root->right;
        if(root->next){
            root->right->next=root->next->left;
        }
        connect(root->left);
        connect(root->right);
    }
};
```

### 122.Best Time to Buy and Sell Stock II

Say you have an array for which the *i*th element is the price of a given stock on day *i*.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).

**Note:** You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

**Example 1:**

```
Input: [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
             Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.

```

**Example 2:**

```
Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.

```

**Example 3:**

```
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```

#### 解析

1. 可以采用和上一题类似的解法，只是遇到减少的数值`m[i]`就清0。
2. 根据规律，可以看出就是求递增数列的和。

#### 代码

动态规划：

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;
        int len = prices.size();
        vector<int> m(len, 0);
        m[0] = 0;
        int res = 0;
        for(int i=1;i<len;++i)
        {
            if(prices[i] <= prices[i-1])
            {
                m[i] = 0;
                res+=m[i-1];
                continue;
            }
            m[i] = m[i-1] + prices[i] - prices[i-1];
        }
        //针对最后一段单增的处理
        if(m[len-1]>0) res+=m[len-1];
        return res;
    }
};
```

解法2：

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;
        int res = 0;
        int len = prices.size();
        for(int i = 1;i<len;++i)
        {
            if(prices[i] > prices[i-1])
                res+=prices[i] - prices[i-1];
        }
        return res;
    }
};
```

### 125.Valid Palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

**Note:** For the purpose of this problem, we define empty string as valid palindrome.

**Example 1:**

```
Input: "A man, a plan, a canal: Panama"
Output: true

```

**Example 2:**

```
Input: "race a car"
Output: false
```

#### 代码

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        if(s.size()==0) return true;
        auto head=s.begin();
        auto last=--s.end();
        while(head<last){
            while(!isalnum(*head)&&head<last)head++;
            while(!isalnum(*last)&&head<last)last--;
            if(toupper(*head)!=toupper(*last))
                return false;
            head++;last--;
        }
        return true;
    }
};
```

### 127.Word Ladder

Given two words (*beginWord* and *endWord*), and a dictionary's word list, find the length of shortest transformation sequence from *beginWord* to *endWord*, such that:

1. Only one letter can be changed at a time.
2. Each transformed word must exist in the word list. Note that *beginWord* is *not* a transformed word.

**Note:**

- Return 0 if there is no such transformation sequence.
- All words have the same length.
- All words contain only lowercase alphabetic characters.
- You may assume no duplicates in the word list.
- You may assume *beginWord* and *endWord* are non-empty and are not the same.

**Example 1:**

```
Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

```

**Example 2:**

```
Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
```

#### 解析

广度优先搜索，每次扫描当初层数，将当前字符串相邻并存在List中的所有字符串放到下一层（用队列）。

#### 代码

```c++
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if(wordList.empty()) return 0;
        unordered_set<string> MySet(wordList.begin(), wordList.end());
        queue<string> MyQueue;
        MyQueue.push(beginWord);
        int res = 1;
        while(!MyQueue.empty())
        {
            int CurLen = MyQueue.size();
            for(int i=0;i<CurLen;++i)
            {
                string word = MyQueue.front();
                MyQueue.pop();
                if(word == endWord)
                {
                    return res;
                }
                MySet.erase(word);
                for(int j=0;j<word.size();++j)
                {
                    char c = word[j];
                    for(int k=0;k<26;++k)
                    {
                        word[j] = 'a'+ k;
                        if(MySet.find(word) != MySet.end())
                        {
                            MyQueue.push(word);
                        }
                    }
                    word[j] = c;
                }
            }
            res++;
        }
        return 0;
    }
};
```

### 130.Surrounded Regions

Given a 2D board containing `'X'` and `'O'` (**the letter O**), capture all regions surrounded by `'X'`.

A region is captured by flipping all `'O'`s into `'X'`s in that surrounded region.

**Example:**

```
X X X X
X O O X
X X O X
X O X X

```

After running your function, the board should be:

```
X X X X
X X X X
X X X X
X O X X

```

**Explanation:**

Surrounded regions shouldn’t be on the border, which means that any `'O'` on the border of the board are not flipped to `'X'`. Any `'O'` that is not on the border and it is not connected to an `'O'` on the border will be flipped to `'X'`. Two cells are connected if they are adjacent cells connected horizontally or vertically.

#### 解析

环绕着矩形走一圈，对于边上是`'O'`的点做DFS。真正保留的`'O'`用`'M'`代替。

#### 代码

```c++
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty()||board[0].empty()) return;
        vector<vector<int>> visited(board.size(),vector<int>(board[0].size(), 0));
        for(int i=0;i<board[0].size();++i)
        {
            if(visited[0][i]==0&&board[0][i]=='O')
            {
                DFS(board, visited, 0, i);
            }
            visited[0][i]=1;
        }
        for(int i=1;i<board.size();++i)
        {
            if(visited[i][board[0].size()-1]==0&&board[i][board[0].size()-1]=='O')
            {
                DFS(board, visited, i, board[0].size()-1);
            }
            visited[i][board[0].size()-1]=1;
        }
        for(int i=board[0].size()-2;i>=0;--i)
        {
            if(visited[board.size()-1][i]==0&&board[board.size()-1][i]=='O')
            {
                DFS(board, visited, board.size()-1, i);
            }
            visited[board.size()-1][i] = 1;
        }
        for(int i=board.size()-2;i>0;--i)
        {
            if(visited[i][0]==0&&board[i][0]=='O')
            {
                DFS(board, visited, i, 0);
            }
            visited[i][0] = 1;
        }
        for(int i=0;i<board.size();++i)
        {
            for(int j=0;j<board[0].size();++j)
            {
                if(board[i][j]!='M')
                {
                    board[i][j]='X';
                }
                else
                {
                    board[i][j]='O';
                }
            }
        }
        
    }
    
    void DFS(vector<vector<char>>& board, vector<vector<int>>& visited, int row, int col)
    {
        if(row<0||row>=board.size()||col<0||col>=board[0].size()||visited[row][col]==1)
        {
            return;
        }
        visited[row][col]=1;
        if(board[row][col]!='O')
        {
            return;
        }
        board[row][col]='M';
        DFS(board, visited, row+1, col);
        DFS(board,visited, row, col+1);
        DFS(board,visited, row-1, col);
        DFS(board,visited, row, col-1);
    }
};
```

### 134.Gas Station

There are *N* gas stations along a circular route, where the amount of gas at station *i* is `gas[i]`.

You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from station *i* to its next station (*i*+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.

**Note:**

- If there exists a solution, it is guaranteed to be unique.
- Both input arrays are non-empty and have the same length.
- Each element in the input arrays is a non-negative integer.

**Example 1:**

```
Input: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
```

**Example 2:**

```
Input: 
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
```

#### 解析

简单解释见：https://programmercarl.com/0134.%E5%8A%A0%E6%B2%B9%E7%AB%99.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BEhttps://programmercarl.com/0134.%E5%8A%A0%E6%B2%B9%E7%AB%99.html#%E7%AE%97%E6%B3%95%E5%85%AC%E5%BC%80%E8%AF%BE

这题要想清楚不容易，尽管想清楚后代码写起来很简单。

I.  显然当gas[i]<cost[i]时，i不能作为起点。

II. 当对所有加油站求和：sum(gas[i] - cost[i]) <0时，无法环绕一圈。反之，则一定能环绕一圈。

问题是如果可以环绕一圈，如何找起点？

性质1. 对于任意一个加油站i，假如从i出发可以环绕一圈，则i一定可以到达任何一个加油站。显而易见。

性质2. 如果这样的i是唯一的，则必然不存在j!=i， 从j出发可以到达i。

反证法：如果存在这样的j，则必然存在j->i->i的路径，而这个路径会覆盖j->j一周的路径。那么j也将是一个符合条件的起点。与唯一解的限制条件矛盾。

性质3. 假如i是最后的解，则由1可知，从0 ~ i-1出发无法达到i。而从i出发可以到达i+1 ~ n-1。

结合以上三条性质，得出解决的思路：

1. 如果对所有加油站的sum(gas[i] - cost[i])<0，则无解。否则进入1。
2. 从0开始计算sum(gas[i] - cost[i])，当遇到i1使sum<0时，说明从0出发无法到达i1。根据性质1，0不是起始点。而由于从0出发已经到达了1 ~ i1-1。根据性质2，1 ~ i1-1一定不是正确的起始点。又因为gas[i]-cost[i]导致sum小于0，所以i1+1为新的起始点候选。
3. 将sum清0，并从i1出发，假如又遇到i2使sum(gas[i] - cost[i]) < 0 时，说明i1出发无法绕一圈，更具性质1，排除i1。又因为i1+1 ~ i2-1都能从i1出发到达,。根据性质2，它们也必然不是起始点。此时i2+1为起始点的候选。
4. 以此类推，直到遇到ik，使从ik出发可以到达ik+1 ~ n-1。

其中步骤0可以合并到1~3的扫描中，一个pass来得到解。

#### 代码

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start=0,total=0,curnum=0;
        for(int i=0;i<gas.size();i++){
            total+=gas[i]-cost[i];
            curnum+=gas[i]-cost[i];
            if(curnum<0){
                start=i+1;
                curnum=0;
            }
        }
        if(total<0) return -1;
        return start;
    }
};
```
### 140. Word Break II

Given a string `s` and a dictionary of strings `wordDict`, add spaces in `s` to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in **any order**.

**Note** that the same word in the dictionary may be reused multiple times in the segmentation.

**Example 1:**

```
Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]
```

**Example 2:**

```
Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.
```

**Example 3:**

```
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
```

### Solution

This problem is similar with 139.Word Break. **01 knapsack problem, permutation**. But it need return all results.

We can use a vector to restore substr's results, and need store the beginning index of a word.

So using DP + hashmap.

#### Code

```c++
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        set<string> tables(wordDict.begin(), wordDict.end());
        unordered_map<int, pair<int, vector<string>>> m;
        m[0].first = 1;
        m[0].second = {""};
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 0; j < i; j++) {
                auto tmp = s.substr(j, i - j);
                if (m[j].first && tables.find(tmp) != tables.end()) {
                    m[i].first = 1;
                    for (auto& substr : m[j].second) {
                        if (i != s.size())
                            m[i].second.push_back(substr + tmp + " ");
                        else 
                            m[i].second.push_back(substr + tmp);
                    }
                }
            }
        }
        return m[s.size()].second;
    }
};
```
### [149. Max Points on a Line](https://leetcode.com/problems/max-points-on-a-line/)

Given an array of `points` where `points[i] = [xi, yi]` represents a point on the **X-Y** plane, return *the maximum number of points that lie on the same straight line*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/25/plane1.jpg)

```
Input: points = [[1,1],[2,2],[3,3]]
Output: 3
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/02/25/plane2.jpg)

```
Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
```

 

**Constraints:**

- `1 <= points.length <= 300`
- `points[i].length == 2`
- `-104 <= xi, yi <= 104`
- All the `points` are **unique**.

#### Solution

针对每个点，计算其他点和它的斜率，统计斜率最多的点数。斜率直接求会有小数可能约不尽导致有误差，所以约到最小然后整除。

#### Code

```cpp
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int res = 0;
        for (int i = 0; i < points.size(); i++) {
            map<pair<int, int>, int> m;
            int duplicate = 1;
            for (int j = i + 1; j < points.size(); j++) {
                if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                    duplicate++;
                    continue;
                }
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                int d = gcd(dx, dy);
                ++m[{dx/d, dy/d}];
            }
            res = max(res, duplicate);
            for (auto& p : m) {
                res = max(res, p.second + duplicate);
            }
        }
        return res;
    }
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
};
```
### 150.Evaluate Reverse Polish Notation

Evaluate the value of an arithmetic expression in [Reverse Polish Notation](http://en.wikipedia.org/wiki/Reverse_Polish_notation).

Valid operators are `+`, `-`, `*`, `/`. Each operand may be an integer or another expression.

**Note:**

- Division between two integers should truncate toward zero.
- The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.

**Example 1:**

```
Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9


```

**Example 2:**

```
Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6


```

**Example 3:**

```
Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation: 
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

```

#### 解析

逆波兰表达式，做计算器会用到。

#### 代码

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if(tokens.empty()) return 0;
        stack<string> s;
        for(int i=0;i<tokens.size();i++){
            if(tokens[i].size()!=1||string("+-*/").find(tokens[i])==string::npos)
                s.push(tokens[i]);
            else{
                int n2=stoi(s.top());
                s.pop();
                int n1=stoi(s.top());
                s.pop();
                switch(tokens[i][0]){
                case '+':n1+=n2;break;
                case '-':n1-=n2;break;
                case '*':n1*=n2;break;
                case '/':n1/=n2;break;
                }
                s.push(to_string(n1));
            }
        }
        return stoi(s.top());
    }
};
```

### 162.Find Peak Element

A peak element is an element that is greater than its neighbors.

Given an input array `nums`, where `nums[i] ≠ nums[i+1]`, find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that `nums[-1] = nums[n] = -∞`.

**Example 1:**

```
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
```

**Example 2:**

```
Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5 
Explanation: Your function can return either index number 1 where the peak element is 2, 
             or index number 5 where the peak element is 6.

```

**Note:**

Your solution should be in logarithmic complexity.

#### 解析

对数时间复杂度，用二分查找。

注意，由于`nums[-1] = nums[n] = -∞`.即使数列单增，也能找到peak元素（即最后一个值）。

#### 代码

```c++
class Solution {
public:
    int findPeakElement(const vector<int> &num) 
    {
        int low = 0;
        int high = num.size()-1;
        
        while(low < high)
        {
            int mid1 = (low+high)/2;
            int mid2 = mid1+1;
            if(num[mid1] < num[mid2])//大的数才有可能是peak element
                low = mid2;
            else
                high = mid1;
        }
        return low;
    }
};
```

### [163. Missing Ranges](https://leetcode.com/problems/missing-ranges/)

You are given an inclusive range `[lower, upper]` and a **sorted unique** integer array `nums`, where all elements are within the inclusive range.

A number `x` is considered **missing** if `x` is in the range `[lower, upper]` and `x` is not in `nums`.

Return *the **shortest sorted** list of ranges that **exactly covers all the missing numbers***. That is, no element of `nums` is included in any of the ranges, and each missing number is covered by one of the ranges.

 

 

**Example 1:**

```
Input: nums = [0,1,3,50,75], lower = 0, upper = 99
Output: [[2,2],[4,49],[51,74],[76,99]]
Explanation: The ranges are:
[2,2]
[4,49]
[51,74]
[76,99]
```

**Example 2:**

```
Input: nums = [-1], lower = -1, upper = -1
Output: []
Explanation: There are no missing ranges since there are no missing numbers.
```

 

**Constraints:**

- `-109 <= lower <= upper <= 109`
- `0 <= nums.length <= 100`
- `lower <= nums[i] <= upper`
- All the values of `nums` are **unique**.

#### 解析

#### 代码

```c++
class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<vector<int>> res;
        if (nums.empty()) {
            res.push_back({lower, upper});
            return res;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0 || nums[i] != nums[i-1]+1) {
                if (i == 0) {
                    if (nums[i] > lower) res.push_back({lower, nums[i]-1});
                }
                else {
                    res.push_back({nums[i-1]+1, nums[i]-1});
                }
            }
        }
        if (nums.back() < upper) {
            res.push_back({nums.back()+1, upper});
        }
        return res;
    }
};
```
### [166. Fraction to Recurring Decimal](https://leetcode.com/problems/fraction-to-recurring-decimal/)

Given two integers representing the `numerator` and `denominator` of a fraction, return *the fraction in string format*.

If the fractional part is repeating, enclose the repeating part in parentheses.

If multiple answers are possible, return **any of them**.

It is **guaranteed** that the length of the answer string is less than `104` for all the given inputs.

 

**Example 1:**

```
Input: numerator = 1, denominator = 2
Output: "0.5"
```

**Example 2:**

```
Input: numerator = 2, denominator = 1
Output: "2"
```

**Example 3:**

```
Input: numerator = 4, denominator = 333
Output: "0.(012)"
```

 

**Constraints:**

- `-231 <= numerator, denominator <= 231 - 1`
- `denominator != 0`

#### Solution

For each remainder, record it's position, if we encountered same reminder, it means the fractional part is repeating.

#### Code

```c++
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        int s1 = numerator > 0 ? 1 : -1;
        int s2 = denominator > 0 ? 1 : -1;
        long long num = abs(numerator);
        long long den = abs(denominator);
        long long out = num / den;
        long long rem = num % den;
        unordered_map<int, int> m;
        string res;
        if (s1*s2 == -1 && (out > 0 || rem > 0)) res += "-";
        res += to_string(out);
        if (rem == 0) return res;
        res+=".";
        string s;
        int pos = 0;
        while (rem != 0) {
            if (m.find(rem) != m.end()) {
                s.insert(m[rem], "(");
                s += ")";
                return res + s;
            }
            m[rem] = pos;
            s += to_string((rem * 10) / den);
            rem = rem*10 % den;
            pos++;
        }
        return res + s;
        
    }
};
```



### 171.Excel Sheet Column Number

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

```
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
    ...

```

**Example 1:**

```
Input: "A"
Output: 1

```

**Example 2:**

```
Input: "AB"
Output: 28

```

**Example 3:**

```
Input: "ZY"
Output: 701
```

#### 代码

```c++
class Solution {
public:
    int titleToNumber(string s) {
        int res = 0;
        for(int i=0;i<s.size();++i)
        {
            res+=(int)(s[i]-'A'+1)*pow(26,s.size()-i-1);
        }
        return res;
    }
};
```

### 172.Factorial Trailing Zeroes

Given an integer *n*, return the number of trailing zeroes in *n*!.

**Example 1:**

```
Input: 3
Output: 0
Explanation: 3! = 6, no trailing zero.
```

**Example 2:**

```
Input: 5
Output: 1
Explanation: 5! = 120, one trailing zero.
```

**Note: **Your solution should be in logarithmic time complexity.

### 解析

Because all trailing 0 is from factors 5 * 2.

But sometimes one number may have several 5 factors, for example, 25 have two 5 factors, 125 have three 5 factors. In the n! operation, factors 2 is always ample. So we just count how many 5 factors in all number from 1 to n.

Therefore, count = n / 5 + n / 25 + n / 125 + ... + 0

#### 代码

```c++
class Solution {
public:
    int trailingZeroes(int n) {
        int res=0;
        while(n>=5)
        {
            n/=5;
            res+=n;
        }
        return res;
    }
};
```

### 179.Largest Number

Given a list of non negative integers, arrange them such that they form the largest number.

**Example 1:**

```
Input: [10,2]
Output: "210"
```

**Example 2:**

```
Input: [3,30,34,5,9]
Output: "9534330"

```

**Note:** The result may be very large, so you need to return a string instead of an integer.

### 解析

注意输入全为0的情况。比如[0, 0]

#### 代码

```c++
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if(nums.empty()) return "";
        if(nums.size()==1) return to_string(nums[0]);
        vector<string> mystrs;
        for(int i=0;i<nums.size();++i)
        {
            mystrs.push_back(to_string(nums[i]));
        }
        sort(mystrs.begin(),mystrs.end(), mycompare);
        string res="";
        int len = 0;
        for(int i=0;i<mystrs.size();++i)
        {
            res+=mystrs[i];
            if("0"==mystrs[i]) len++;
        }
        if(len==mystrs.size()) return "0";
        return res;
    }
    static bool mycompare(string& a, string& b)
    {
        string ab = a+b;
        string ba = b+a;
        return ab>ba;
    }
};
```

### 190.Reverse Bits

Reverse bits of a given 32 bits unsigned integer.

 

**Example 1:**

```
Input: 00000010100101000001111010011100
Output: 00111001011110000010100101000000
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, so return 964176192 which its binary representation is 00111001011110000010100101000000.

```

**Example 2:**

```
Input: 11111111111111111111111111111101
Output: 10111111111111111111111111111111
Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293, so return 3221225471 which its binary representation is 10101111110010110010011101101001.
```

 

**Note:**

- Note that in some languages such as Java, there is no unsigned integer type. In this case, both input and output will be given as signed integer type and should not affect your implementation, as the internal binary representation of the integer is the same whether it is signed or unsigned.
- In Java, the compiler represents the signed integers using [2's complement notation](https://en.wikipedia.org/wiki/Two%27s_complement). Therefore, in **Example 2** above the input represents the signed integer `-3` and the output represents the signed integer `-1073741825`.

#### 解析

移位到另一个变量中，相当于出栈再压栈。

#### 代码

```c++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res=0;
        for(uint32_t i=0;i<32;++i)
        {
            res = (n>>i) & 1 | res;
            if(i<31)
                res=res<<1;
        }
        return res;
    }
};
```

### 191.Number of 1 Bits

Write a function that takes an unsigned integer and return the number of '1' bits it has (also known as the [Hamming weight](http://en.wikipedia.org/wiki/Hamming_weight)).

 

**Example 1:**

```
Input: 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.

```

**Example 2:**

```
Input: 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.

```

**Example 3:**

```
Input: 11111111111111111111111111111101
Output: 31
Explanation: The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.
```

 #### 解析

剑指offer原题

#### 代码

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while(n)
        {
            res++;
            n=(n-1)&n;
        }
        return res;
    }
};
```

###202.Happy Number

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

**Example:** 

```
Input: 19
Output: true
Explanation: 
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```

#### 解析

不是happy数的终止条件是出现重复的结果。所以可以使用一个set来存，之前出现的结果。

#### 代码

```c++
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> myset;
        while(myset.insert(n).second)
        {
            n = GetSum(n);
            if(n==1) return true;
        }
        return false;
    }
    int GetSum(int n)
    {
        int res = 0;
        while(n)
        {
            int m = n%10;
            res += m*m;
            n /= 10;
        }
        return res;
    }
};
```

### 204.Count Primes

Count the number of prime numbers less than a non-negative number, **n**.

**Example:**

```
Input: 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
```

#### 解析

欧拉筛选法。

#### 代码

```c++
class Solution {
public:
    int countPrimes(int n) {
        if(n<=1) return 0;
        int Prime[n];
        int Check[n];
        int cnt = 0;
        memset(Check,0,sizeof(Check));
        for(int i=2;i<n;i++)
        {
            if(!Check[i])
                Prime[cnt++] = i;
            for(int j=0;j<cnt&&Prime[j]*i<n;j++)
            {
                Check[Prime[j]*i] = 1;
                if(i%Prime[j]==0) break;
            }
        }
        return cnt;
    }
};
```

### 210.Course Schedule II

There are a total of *n* courses you have to take, labeled from `0` to `n-1`.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: `[0,1]`

Given the total number of courses and a list of prerequisite **pairs**, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

**Example 1:**

```
Input: 2, [[1,0]] 
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished   
             course 0. So the correct course order is [0,1] .
```

**Example 2:**

```
Input: 4, [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both     
             courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. 
             So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3] .
```

**Note:**

1. The input prerequisites is a graph represented by **a list of edges**, not adjacency matrices. Read more about [how a graph is represented](https://www.khanacademy.org/computing/computer-science/algorithms/graph-representation/a/representing-graphs).
2. You may assume that there are no duplicate edges in the input prerequisites.

### 解析

有向图，存在依赖关系的，仍然可以使用拓扑排序来遍历。用graph保存每个结点及其出度，用InDegree保存每个结点的入度。这样减去入度为0的结点以后，还能根据其graph中的出度结点，更新这些出度结点的入度。

#### 代码

```c++
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph = GetGraph(numCourses, prerequisites);
        vector<int> InDegree(numCourses, 0);
        GetInDegree(InDegree, graph);
        stack<int> zeroingree;
        vector<int> result;
        for(int i=0; i<numCourses; ++i)
        {
            if(InDegree[i]==0) zeroingree.push(i);
        }
        for(int i=0;i<numCourses&&!zeroingree.empty();++i)
        {
            int index = zeroingree.top();
            zeroingree.pop();
            result.push_back(index);
            for(int j=0;j<graph[index].size();++j)
            {
                InDegree[graph[index][j]]--;
                if(InDegree[graph[index][j]]==0) zeroingree.push(graph[index][j]);
            }
            if(i+1<numCourses&&zeroingree.empty())
            {
                result.clear();
                return result;
            }
        }
        return result;
    }
    vector<vector<int>> GetGraph(int num, vector<vector<int>>& nodes)
    {
        vector<vector<int>> graph(num);
        for(int i=0;i<nodes.size();++i)
        {
            graph[nodes[i][1]].push_back(nodes[i][0]);
        }
        return graph;
    }
    void GetInDegree(vector<int>& InDegree, vector<vector<int>>& graph)
    {
        for(int i=0;i<graph.size();++i)
        {
            for(int j=0;j<graph[i].size();++j)
            {
                InDegree[graph[i][j]]++;
            }
        }
    }
};
```

### 212.Word Search II

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

**Example:**

```
Input: 
board = [
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
words = ["oath","pea","eat","rain"]

Output: ["eat","oath"]
```

 

**Note:**

1. All inputs are consist of lowercase letters `a-z`.
2. The values of `words` are distinct.

#### 解析

简单的DFS会超时，多模匹配可以用字典树的方式，将需要匹配的多个字符串生成一棵字典树，可以降低时间复杂度，只需要扫描一遍board就可以的到答案，而普通的DFS需要再乘以N倍。

#### 代码

```c++
struct TrieNode {
    bool is_word;
    shared_ptr<vector<shared_ptr<TrieNode>>> next;
    TrieNode() {
        is_word = false;
        next = make_shared<vector<shared_ptr<TrieNode>>>(26);
    }
};

class Solution {
private:
    void buildTree(shared_ptr<TrieNode> root, string& word) {
        auto node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->next->at(word[i]-'a')) {
                node->next->at(word[i]-'a') = make_shared<TrieNode>();
            }
            node = node->next->at(word[i]-'a');
        }
        node->is_word = true;
    }
    vector<int> next = {0, 1, 0, -1, 0};
    void DFS(vector<vector<char>>& board, int row, int col, string s, unordered_set<string>& res,
        shared_ptr<TrieNode> root, vector<vector<bool>>& visited) {
            if (root->is_word) {
                res.insert(s);
            }
            for (int i = 0; i < 4; i++) {
                int nr = row + next[i];
                int nc = col + next[i+1];
                if (nr < 0 || nr >= board.size() 
                || nc < 0 || nc >= board[0].size() 
                || visited[nr][nc] || !root->next->at(board[nr][nc]-'a')) continue;
                visited[nr][nc] = true;
                DFS(board, nr, nc, s+board[nr][nc], res, root->next->at(board[nr][nc]-'a'), visited);
                visited[nr][nc] = false;
            }
    }
public:
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        auto root = make_shared<TrieNode>();
        for (auto& word : words) {
            buildTree(root, word);
        }
        unordered_set<string> res;
        vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (!root->next->at(board[i][j]-'a')) continue;
                visited[i][j] = true;
                string s(1, board[i][j]);
                DFS(board, i, j, s, res, root->next->at(board[i][j]-'a'), visited);
                visited[i][j] = false;
            }
        }
        return vector<string>(res.begin(), res.end());
    }
};
```

### [217. Contains Duplicate](https://leetcode.com/problems/contains-duplicate/)

Given an integer array `nums`, return `true` if any value appears **at least twice** in the array, and return `false` if every element is distinct.

 

**Example 1:**

```
Input: nums = [1,2,3,1]
Output: true
```

**Example 2:**

```
Input: nums = [1,2,3,4]
Output: false
```

**Example 3:**

```
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`

#### Solution



#### Code

```c++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> tables;
        for (const auto& num : nums) {
            if(!(tables.insert(num).second)) return true;
        }
        return false;
    }
};
```



### [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/)

A city's **skyline** is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return *the **skyline** formed by these buildings collectively*.

The geometric information of each building is given in the array `buildings` where `buildings[i] = [lefti, righti, heighti]`:

- `lefti` is the x coordinate of the left edge of the `ith` building.
- `righti` is the x coordinate of the right edge of the `ith` building.
- `heighti` is the height of the `ith` building.

You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height `0`.

The **skyline** should be represented as a list of "key points" **sorted by their x-coordinate** in the form `[[x1,y1],[x2,y2],...]`. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate `0` and is used to mark the skyline's termination where the rightmost building ends. Any ground between the leftmost and rightmost buildings should be part of the skyline's contour.

**Note:** There must be no consecutive horizontal lines of equal height in the output skyline. For instance, `[...,[2 3],[4 5],[7 5],[11 5],[12 7],...]` is not acceptable; the three lines of height 5 should be merged into one in the final output as such: `[...,[2 3],[4 5],[12 7],...]`

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/12/01/merged.jpg)

```
Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
Explanation:
Figure A shows the buildings of the input.
Figure B shows the skyline formed by those buildings. The red points in figure B represent the key points in the output list.
```

**Example 2:**

```
Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]
```

 

**Constraints:**

- `1 <= buildings.length <= 104`
- `0 <= lefti < righti <= 231 - 1`
- `1 <= heighti <= 231 - 1`
- `buildings` is sorted by `lefti` in non-decreasing order.

#### Solution

将begin按照从小到大排序，end按照从小到大排序，begin对应的height从大到小排序，end对应的height从小到大排序。

然后这样就类似于room meeting问题，每次最大height有更新就添加结果。

#### Code

```cpp
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> tables, res;
        map<int, int> m;
        int pre = 0, cur = 0;
        for (const auto& item : buildings) {
            tables.push_back({item[0], -item[2]});
            tables.push_back({item[1], item[2]});
        }
        sort(tables.begin(), tables.end());
        m[0] = 1;
        for (const auto& item : tables) {
            if (item[1] < 0) m[-item[1]]++;
            else {
                m[item[1]]--;
                if (m[item[1]] == 0)
                    m.erase(item[1]);
            };
            cur = (*m.rbegin()).first;
            if (cur != pre) {
                res.push_back({item[0], cur});
                pre = cur;
            }
        }
        return res;
    }
};
```
### [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)

Given a string `s` representing a valid expression, implement a basic calculator to evaluate it, and return *the result of the evaluation*.

**Note:** You are **not** allowed to use any built-in function which evaluates strings as mathematical expressions, such as `eval()`.

 

**Example 1:**

```
Input: s = "1 + 1"
Output: 2
```

**Example 2:**

```
Input: s = " 2-1 + 2 "
Output: 3
```

**Example 3:**

```
Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
```

 

**Constraints:**

- `1 <= s.length <= 3 * 105`
- `s` consists of digits, `'+'`, `'-'`, `'('`, `')'`, and `' '`.
- `s` represents a valid expression.
- `'+'` is **not** used as a unary operation (i.e., `"+1"` and `"+(2 + 3)"` is invalid).
- `'-'` could be used as a unary operation (i.e., `"-1"` and `"-(2 + 3)"` is valid).
- There will be no two consecutive operators in the input.
- Every number and running calculation will fit in a signed 32-bit integer.

#### Solution

1. 将中缀表达式转为后缀表达式:

   >声明 Q：输出队列 
   >
   >声明 S：操作符栈 
   >
   >遍历中缀表达式中的每一个单词符号 x：    
   >
   >​                        如果 x 是一个操作数，直接将 x 追加到输出队列 Q 末尾，否则往下检查；    
   >
   >​                        如果 x 是一个左括号“(”，将 x 压入操作符栈 S 栈顶，否则往下检查；   
   >
   >​                        如果 x 是一个操作符：        
   >
   >​                                         如果操作符栈 S 栈顶为一个优先级大于等于 x 的操作符，则将 S 栈顶的运算符弹出并且追加到输出队列 Q 末尾，最后将 x 压入栈顶；        
   >
   >​                                         如果操作符栈 S 栈顶为一个优先级小于 x 的操作符，或者不为操作符（在这个简化算法里，只有可能是左括号），则直接将 x 压入栈顶即可。    
   >
   >​                        如果 x 是一个右括号“)”，则将操作符栈 S 栈顶到往下第一个左括号“(”之间的元素依次弹出并且追加到输出队列末尾，将“(”出栈丢弃，x 也不用入栈。注意：如果栈到底后仍没有找到左括号，则说明表达式不合法，左右括号不匹配。 最后将栈 S 中的元素全部依次弹出并且入队列 Q。
   >
   >

2. 计算后缀表达式

#### Code

```cpp
class Solution {
public:
    int calculate(string s) {
        auto reverse_polish = ConvertToReversePolish(s);
        stack<long long> st;
        for (int i = 0; i < reverse_polish.size(); i++) {
            if (reverse_polish[i] == "+" || reverse_polish[i] == "-") {
                long long second = st.top(); st.pop();
                long long first = st.top(); st.pop();
                long long num = 0;
                switch (reverse_polish[i][0]) {
                    case '-' :
                        num = first - second;
                        break;
                    case '+' :
                        num = first + second;
                        break;
                    case '/' :
                        num = first / second;
                        break;
                    case '*' :
                        num = first * second;
                        break;
                }
                st.push(num);
            }
            else {
                st.push(stoi(reverse_polish[i]));
            }
        }
        return st.top();
    }
private:
    vector<string> ConvertToReversePolish(const string& s) {
        if (s.empty()) return {};
        
        stack<char> st;
        vector<string> res;
        string num;
        string real_s;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                num += s[i];
                real_s += s[i];
                if (i+1 >= s.size() || s[i+1] < '0' || s[i+1] > '9') {
                    res.push_back(num);
                    num.clear();
                }
            }
            else if (s[i] == '(') {
                st.push(s[i]);
                real_s += s[i];
            }
            else if (s[i] == '+' || s[i] == '-') {
                // -1+1
                if (s[i] == '-' && (real_s.empty() || real_s.back() == '(')) {
                    // num += s[i];
                    res.push_back("0");
                    // continue;
                }
                while (!st.empty() && 
                       (st.top() == '+' || st.top() == '-')) {
                    res.push_back(string(1, st.top()));
                    st.pop();
                }
                st.push(s[i]);
                real_s += s[i];
            }
            else if (s[i] == ')') {
                while (!st.empty() && st.top() != '(') {
                    res.push_back(string(1, st.top()));
                    st.pop();
                }
                if (!st.empty()) st.pop();
                real_s += s[i];
            }
            
        }
        while (!st.empty()) {
            res.push_back(string(1, st.top()));
            st.pop();
        }
        return res;
    }
};
```
### [227. Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/)

Given a string `s` which represents an expression, *evaluate this expression and return its value*. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of `[-231, 231 - 1]`.

**Note:** You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as `eval()`.

 

**Example 1:**

```
Input: s = "3+2*2"
Output: 7
```

**Example 2:**

```
Input: s = " 3/2 "
Output: 1
```

**Example 3:**

```
Input: s = " 3+5 / 2 "
Output: 5
```

 

**Constraints:**

- `1 <= s.length <= 3 * 105`
- `s` consists of integers and operators `('+', '-', '*', '/')` separated by some number of spaces.
- `s` represents **a valid expression**.
- All the integers in the expression are non-negative integers in the range `[0, 231 - 1]`.
- The answer is **guaranteed** to fit in a **32-bit integer**.

#### Solution

Simplified version of [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)

#### Code

```c++
class Solution {
public:
    int calculate(string s) {
        if (s.empty()) return 0;
        stack<int> tables;
        long long num = 0;
        int op = '+';
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            if (ch >= '0' && ch <= '9') {
                num = num * 10 + ch - '0';
            }
            if (ch < '0' && ch != ' ' || i == s.size() - 1) {
                if (op == '+') tables.push(num);
                else if (op == '-') tables.push(-num);
                else if (op == '*' || op == '/') {
                    int tmp = (op == '*') ? tables.top() * num : tables.top() / num;
                    tables.pop();
                    tables.push(tmp);
                }
                op = ch;
                num = 0;
            }
        }
        int res = 0;
        while(!tables.empty()) {
            res += tables.top();
            tables.pop();
        }
        return res;
    }

    
};
```



### [237. Delete Node in a Linked List](https://leetcode.com/problems/delete-node-in-a-linked-list/)

There is a singly-linked list `head` and we want to delete a node `node` in it.

You are given the node to be deleted `node`. You will **not be given access** to the first node of `head`.

All the values of the linked list are **unique**, and it is guaranteed that the given node `node` is not the last node in the linked list.

Delete the given node. Note that by deleting the node, we do not mean removing it from memory. We mean:

- The value of the given node should not exist in the linked list.
- The number of nodes in the linked list should decrease by one.
- All the values before `node` should be in the same order.
- All the values after `node` should be in the same order.

**Custom testing:**

- For the input, you should provide the entire linked list `head` and the node to be given `node`. `node` should not be the last node of the list and should be an actual node in the list.
- We will build the linked list and pass the node to your function.
- The output will be the entire list after calling your function.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/01/node1.jpg)

```
Input: head = [4,5,1,9], node = 5
Output: [4,1,9]
Explanation: You are given the second node with value 5, the linked list should become 4 -> 1 -> 9 after calling your function.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/09/01/node2.jpg)

```
Input: head = [4,5,1,9], node = 1
Output: [4,5,9]
Explanation: You are given the third node with value 1, the linked list should become 4 -> 5 -> 9 after calling your function.
```

 

**Constraints:**

- The number of the nodes in the given list is in the range `[2, 1000]`.
- `-1000 <= Node.val <= 1000`
- The value of each node in the list is **unique**.
- The `node` to be deleted is **in the list** and is **not a tail** node.

#### Solution

Copy next value and delete next node.

#### Code

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        auto* tmp = node->next;
        node->next = tmp->next;
        delete tmp;
        tmp = nullptr;
    }
};
```



### [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/)

Given two strings `s` and `t`, return `true` *if* `t` *is an anagram of* `s`*, and* `false` *otherwise*.

An **Anagram** is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

**Example 1:**

```
Input: s = "anagram", t = "nagaram"
Output: true
```

**Example 2:**

```
Input: s = "rat", t = "car"
Output: false
```

 

**Constraints:**

- `1 <= s.length, t.length <= 5 * 104`
- `s` and `t` consist of lowercase English letters.

 

**Follow up:** What if the inputs contain Unicode characters? How would you adapt your solution to such a case?

#### Solution

hashtable.

#### Code

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        vector<int> tables(26, 0);
        for (const auto& ch : s) {
            tables[ch-'a']++;
        }
        for (const auto& ch : t) {
            if (tables[ch-'a'] <= 0) return false;
            tables[ch-'a']--;
        }
        return true;
    }
};
```



### [251. Flatten 2D Vector](https://leetcode.com/problems/flatten-2d-vector/)

Design an iterator to flatten a 2D vector. It should support the `next` and `hasNext` operations.

Implement the `Vector2D` class:

- `Vector2D(int[][] vec)` initializes the object with the 2D vector `vec`.
- `next()` returns the next element from the 2D vector and moves the pointer one step forward. You may assume that all the calls to `next` are valid.
- `hasNext()` returns `true` if there are still some elements in the vector, and `false` otherwise.

 

**Example 1:**

```
Input
["Vector2D", "next", "next", "next", "hasNext", "hasNext", "next", "hasNext"]
[[[[1, 2], [3], [4]]], [], [], [], [], [], [], []]
Output
[null, 1, 2, 3, true, true, 4, false]

Explanation
Vector2D vector2D = new Vector2D([[1, 2], [3], [4]]);
vector2D.next();    // return 1
vector2D.next();    // return 2
vector2D.next();    // return 3
vector2D.hasNext(); // return True
vector2D.hasNext(); // return True
vector2D.next();    // return 4
vector2D.hasNext(); // return False
```

 

**Constraints:**

- `0 <= vec.length <= 200`
- `0 <= vec[i].length <= 500`
- `-500 <= vec[i][j] <= 500`
- At most `105` calls will be made to `next` and `hasNext`.

 

**Follow up:** As an added challenge, try to code it using only [iterators in C++](http://www.cplusplus.com/reference/iterator/iterator/) or [iterators in Java](http://docs.oracle.com/javase/7/docs/api/java/util/Iterator.html).

#### Solution

Iteration. When encountering end, move to next valid line.

#### Code

```c++
class Vector2D {
    vector<vector<int>>::iterator iter, end;
    int col;
public:
    Vector2D(vector<vector<int>>& vec) {
        iter = vec.begin();
        end = vec.end();
        col = 0;
    }
    
    int next() {
        hasNext();
        return iter->at(col++);
    }
    
    bool hasNext() {
        while (iter != end && col == iter->size()) {
            iter++;
            col = 0;
        }
        return iter != end;
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
```



### [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/)

Given an array of meeting time intervals `intervals` where `intervals[i] = [starti, endi]`, return *the minimum number of conference rooms required*.

 

**Example 1:**

```
Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2
```

**Example 2:**

```
Input: intervals = [[7,10],[2,4]]
Output: 1
```

 

**Constraints:**

- `1 <= intervals.length <= 104`
- `0 <= starti < endi <= 106`

#### Solution

对begins和ends排序，然后是上下车问题解决，遇到begins>ends，增加，反之减少（每结束一个，减少一个）。

#### Code

```c++
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> begins(n, 0);
        vector<int> ends(n, 0);
        for (int i = 0; i < intervals.size(); i++) {
            begins[i] = intervals[i][0];
            ends[i] = intervals[i][1];
        }
        sort(begins.begin(), begins.end());
        sort(ends.begin(), ends.end());
        int begin = 0, end = 0;
        int total = 0;
        int res = 0;
        while (begin < n && end < n) {
            if (begins[begin] < ends[end]) {
                total++;
                begin++;
                res = max(res, total);
            }
            else {
                end++;
                total--;
                res = max(res, total);
            }
        }
        return res;
    }
};
```



### [268. Missing Number](https://leetcode.com/problems/missing-number/)

Given an array `nums` containing `n` distinct numbers in the range `[0, n]`, return *the only number in the range that is missing from the array.*

 

**Example 1:**

```
Input: nums = [3,0,1]
Output: 2
Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.
```

**Example 2:**

```
Input: nums = [0,1]
Output: 2
Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in nums.
```

**Example 3:**

```
Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the range since it does not appear in nums.
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 104`
- `0 <= nums[i] <= n`
- All the numbers of `nums` are **unique**.

 

**Follow up:** Could you implement a solution using only `O(1)` extra space complexity and `O(n)` runtime complexity?

#### Solution

a^b^b =a

a^b^c=b^c^a

So each number xor its index, if one number does not exist, we can get the number.

#### Code

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            res ^= i^nums[i];
        }
        return res;
    }
};
```



### [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)

There is a new alien language that uses the English alphabet. However, the order of the letters is unknown to you.

You are given a list of strings `words` from the alien language's dictionary. Now it is claimed that the strings in `words` are 

**sorted lexicographically**

 by the rules of this new language.



If this claim is incorrect, and the given arrangement of string in `words` cannot correspond to any order of letters, return `"".`

Otherwise, return *a string of the unique letters in the new alien language sorted in **lexicographically increasing order** by the new language's rules**.* If there are multiple solutions, return ***any of them***.

 

**Example 1:**

```
Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
```

**Example 2:**

```
Input: words = ["z","x"]
Output: "zx"
```

**Example 3:**

```
Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".
```

 

**Constraints:**

- `1 <= words.length <= 100`
- `1 <= words[i].length <= 100`
- `words[i]` consists of only lowercase English letters.

#### Solution

// graph + BFS + topological sort

// for zero in degree, can be set in any position

#### Code

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        vector<unordered_set<int>> m(26);
        unordered_map<int, bool> visited;
        unordered_map<int, int> indegree;
        unordered_set<int> tables;
        int n = words.size();
        string last = words[0];
        for (auto& ch : last) {
            tables.insert(ch-'a');
            visited[ch-'a'] = false;
        }
        for (int i = 1; i < n; i++) {
            bool can_add = true;
            for (int j = 0; j < words[i].size(); j++) {
                tables.insert(words[i][j]-'a');
                visited[words[i][j]-'a'] = false;
                // only first different pos can add
                if (can_add && j < last.size() && words[i][j] != last[j]) {
                    // insert success, add degree
                    if (m[last[j] - 'a'].insert(words[i][j] - 'a').second)
                        indegree[words[i][j] - 'a']++;
                    can_add = false;
                }
            }
            // ["abc","ab"]
            if (can_add && words[i].size() < last.size()) return "";
            last = words[i];
        }
        queue<int> q;
        // for zero in degree, can be set in any position
        for (auto& item : tables) {
            if (indegree.find(item) == indegree.end()) {
                q.push(item);
            }
        }
        string res;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            res += cur + 'a';
            if (visited[cur]) return "";
            visited[cur] = true;
            for (auto& next : m[cur]) {
                indegree[next]--;
                if (indegree[next] <= 0) {
                    q.push(next);
                }
            }
        }
        // exist some closed cycles
        for (auto& item : visited) {
            if (!item.second) return "";
        }
        return res;

    }
};
```
### [277. Find the Celebrity](https://leetcode.com/problems/find-the-celebrity/)

Suppose you are at a party with `n` people labeled from `0` to `n - 1` and among them, there may exist one celebrity. The definition of a celebrity is that all the other `n - 1` people know the celebrity, but the celebrity does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. You are only allowed to ask questions like: "Hi, A. Do you know B?" to get information about whether A knows B. You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).

You are given a helper function `bool knows(a, b)` that tells you whether `a` knows `b`. Implement a function `int findCelebrity(n)`. There will be exactly one celebrity if they are at the party.

Return *the celebrity's label if there is a celebrity at the party*. If there is no celebrity, return `-1`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2022/01/19/g1.jpg)

```
Input: graph = [[1,1,0],[0,1,0],[1,1,1]]
Output: 1
Explanation: There are three persons labeled with 0, 1 and 2. graph[i][j] = 1 means person i knows person j, otherwise graph[i][j] = 0 means person i does not know person j. The celebrity is the person labeled as 1 because both 0 and 2 know him but 1 does not know anybody.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2022/01/19/g2.jpg)

```
Input: graph = [[1,0,1],[1,1,0],[0,1,1]]
Output: -1
Explanation: There is no celebrity.
```

 

**Constraints:**

- `n == graph.length == graph[i].length`
- `2 <= n <= 100`
- `graph[i][j]` is `0` or `1`.
- `graph[i][i] == 1`

 

**Follow up:** If the maximum number of allowed calls to the API `knows` is `3 * n`, could you find a solution without exceeding the maximum number of calls?

#### Solution

for one pass, if knows(candidate, i), candidate = i

because a celebrity is that all the other n - 1 people know the celebrity, and the celebrity does not know any of them, so the last one must be possible the celebrity

Finally check

#### Code

```c++
/* The knows API is defined for you.
      bool knows(int a, int b); */

class Solution {
public:
    int findCelebrity(int n) {
        int candidate = 0;
        for(int i = 1; i < n; i++){
            if(knows(candidate, i))
                candidate = i;
        }
        for(int i = 0; i < n; i++){
            if(i != candidate && (knows(candidate, i) || !knows(i, candidate))) return -1;
        }
        return candidate;
    }
};
```



### 279.Perfect Squares

Given a positive integer *n*, find the least number of perfect square numbers (for example, `1, 4, 9, 16, ...`) which sum to *n*.

**Example 1:**

```
Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.
```

**Example 2:**

```
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
```

#### 解析

```
// unbounded knapsack 
// dp[j]  least number of perfect square numbers that sum to j
// dp[j] = min(dp[j], dp[j - i*i] + 1)
// dp[0] = 0
```

#### 代码

```c++
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for (int j = 1; j <= n; j++) {
            for (int i = 1; i * i <= j; i++) {
                dp[j] = min(dp[j], dp[j-i*i]+1);
            }
        }
        return dp.back();
    }
};
```
### [285. Inorder Successor in BST](https://leetcode.com/problems/inorder-successor-in-bst/)

Given the `root` of a binary search tree and a node `p` in it, return *the in-order successor of that node in the BST*. If the given node has no in-order successor in the tree, return `null`.

The successor of a node `p` is the node with the smallest key greater than `p.val`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/01/23/285_example_1.PNG)

```
Input: root = [2,1,3], p = 1
Output: 2
Explanation: 1's in-order successor node is 2. Note that both p and the return value is of TreeNode type.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/01/23/285_example_2.PNG)

```
Input: root = [5,3,6,2,4,null,null,1], p = 6
Output: null
Explanation: There is no in-order successor of the current node, so the answer is null.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- `-105 <= Node.val <= 105`
- All Nodes will have unique values.

#### Solution

inorder recursion

#### Code

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (!root) return nullptr;
        auto left = inorderSuccessor(root->left, p);
        if (left) return left;
        if (root->val > p->val) return root;
        return inorderSuccessor(root->right, p);
    }
};
```



### [289. Game of Life](https://leetcode.com/problems/game-of-life/)

According to [Wikipedia's article](https://en.wikipedia.org/wiki/Conway's_Game_of_Life): "The **Game of Life**, also known simply as **Life**, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

The board is made up of an `m x n` grid of cells, where each cell has an initial state: **live** (represented by a `1`) or **dead** (represented by a `0`). Each cell interacts with its [eight neighbors](https://en.wikipedia.org/wiki/Moore_neighborhood) (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

1. Any live cell with fewer than two live neighbors dies as if caused by under-population.
2. Any live cell with two or three live neighbors lives on to the next generation.
3. Any live cell with more than three live neighbors dies, as if by over-population.
4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously. Given the current state of the `m x n` grid `board`, return *the next state*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/12/26/grid1.jpg)

```
Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/12/26/grid2.jpg)

```
Input: board = [[1,1],[1,0]]
Output: [[1,1],[1,1]]
```

 

**Constraints:**

- `m == board.length`
- `n == board[i].length`
- `1 <= m, n <= 25`
- `board[i][j]` is `0` or `1`.

 

**Follow up:**

- Could you solve it in-place? Remember that the board needs to be updated simultaneously: You cannot update some cells first and then use their updated values to update other cells.
- In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches upon the border of the array (i.e., live cells reach the border). How would you address these problems?

#### Solution

状态0： 死细胞转为死细胞

状态1： 活细胞转为活细胞

状态2： 活细胞转为死细胞

状态3： 死细胞转为活细胞
https://www.cnblogs.com/grandyang/p/4854466.html

#### Code

```c++

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        vector<int> n_x = {-1, -1, 0, 1, 0, 1, -1, 1};
        vector<int> n_y = {-1, 0, -1, 1, 1, 0, 1, -1};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n ; j++) {
                int cut = 0;
                for (int t = 0; t < 8; t++){
                    int cur_x = n_x[t] + j;
                    int cur_y = n_y[t] + i;
                    if (cur_x >= 0 && cur_x < n && cur_y >=0 && cur_y < m && 
                        (board[cur_y][cur_x] == 1 || board[cur_y][cur_x] == 2)) {
                        cut++;
                    }
                }
                if (board[i][j] && (cut > 3 || cut < 2)) board[i][j] = 2;
                else if (!board[i][j] && cut == 3) board[i][j] = 3;
            }
        }
         for (int i = 0; i < m; i++) {
            for (int j = 0; j < n ; j++) {
                board[i][j] %= 2;
            }
         }
    }
};
```



### [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

**Clarification:** The input/output format is the same as [how LeetCode serializes a binary tree](https://support.leetcode.com/hc/en-us/articles/360011883654-What-does-1-null-2-3-mean-in-binary-tree-representation-). You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/15/serdeser.jpg)

```
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
```

**Example 2:**

```
Input: root = []
Output: []
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 104]`.
- `-1000 <= Node.val <= 1000`

#### Solution

剑指offer原题，前序遍历，保证nullptr结点在序列最后。

#### Code

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    void serial(TreeNode* root, vector<int>& vec) {
        if (!root) {
            vec.push_back(100000);
            return;
        }
        vec.push_back(root->val);
        serial(root->left, vec);
        serial(root->right, vec);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        vector<int> vec;
        serial(root, vec);
        int* tmp = new int[vec.size()];
        for (int i = 0; i < vec.size(); i++) {
            tmp[i] = vec[i];
        }
        string res(reinterpret_cast<const char*>(tmp), vec.size()*sizeof(int));
        return res;
    }
    TreeNode* deserialize(const int*& tree) {
        if (*tree == 100000) {
            return nullptr;
        } 
        TreeNode* node = new TreeNode(*tree);
        node->left = deserialize(++tree);
        node->right = deserialize(++tree);
        return node;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        const char* chr = data.c_str();
        const int* tree = reinterpret_cast<const int*>(chr);
        return deserialize(tree);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
```



### [308. Range Sum Query 2D - Mutable](https://leetcode.com/problems/range-sum-query-2d-mutable/)

Given a 2D matrix `matrix`, handle multiple queries of the following types:

1. **Update** the value of a cell in `matrix`.
2. Calculate the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.

Implement the NumMatrix class:

- `NumMatrix(int[][] matrix)` Initializes the object with the integer matrix `matrix`.
- `void update(int row, int col, int val)` **Updates** the value of `matrix[row][col]` to be `val`.
- `int sumRegion(int row1, int col1, int row2, int col2)` Returns the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/14/summut-grid.jpg)

```
Input
["NumMatrix", "sumRegion", "update", "sumRegion"]
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [3, 2, 2], [2, 1, 4, 3]]
Output
[null, 8, null, 10]

Explanation
NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e. sum of the left red rectangle)
numMatrix.update(3, 2, 2);       // matrix changes from left image to right image
numMatrix.sumRegion(2, 1, 4, 3); // return 10 (i.e. sum of the right red rectangle)
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 200`
- `-1000 <= matrix[i][j] <= 1000`
- `0 <= row < m`
- `0 <= col < n`
- `-1000 <= val <= 1000`
- `0 <= row1 <= row2 < m`
- `0 <= col1 <= col2 < n`
- At most `5000` calls will be made to `sumRegion` and `update`.

#### 解析

1. brute force solution can pass...
2. segment tree, each row is one tree. Query time complexity is O(logn * m), better than brute force

#### 代码

1. brute force

```c++
class NumMatrix {
    vector<vector<int>> m;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        m = matrix;
    }
    
    void update(int row, int col, int val) {
        m[row][col] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for (int i = row1; i <= row2; i++) {
            for (int j = col1; j <= col2; j++) {
                sum += m[i][j];
            }
        }
        return sum;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
```

2. segment tree

```c++
struct SegTree{
    vector<int> st;
    void update(int idx, int s, int e, int l, int r, int val) {
        if (l <= s && e <= r) {
            st[idx] = val;
            return;
        }
        int mid = (s + e) >> 1;
        if (l <= mid) update(idx*2+1, s, mid, l, r, val);
        if (r > mid) update(idx*2+2, mid+1, e, l, r, val);
        st[idx] = st[idx*2+1] + st[idx*2+2];
    }
    int query(int idx, int s, int e, int l, int r) {
        if (l <= s && e <= r) {
            return st[idx];
        }
        int mid = (s + e) >> 1;
        int ans = 0;
        if (l <= mid) ans = query(idx*2+1, s, mid, l, r);
        if (r > mid) ans += query(idx*2+2, mid+1, e, l, r);
        return ans;
    }
};
class NumMatrix {
private:
    vector<SegTree> roots;
    int mN;
    int row_len, col_len;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        row_len = matrix.size();
        col_len = matrix[0].size();
        mN = row_len * col_len;
        roots.resize(row_len);
        for (int i = 0; i < row_len; i++) {
            roots[i].st.resize(col_len*4);
            for (int j = 0; j < col_len; j++) {
                roots[i].update(0, 0, col_len-1, j, j, matrix[i][j]);
            }
        }
    }
    
    void update(int row, int col, int val) {
        roots[row].update(0, 0, col_len-1, col, col, val);
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for (int i = row1; i <= row2; i++) {
            sum += roots[i].query(0, 0, col_len-1, col1, col2);
        }
        return sum;
    }
};
/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
```



### [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)

Given an integer array `nums`, return *an integer array* `counts` *where* `counts[i]` *is the number of smaller elements to the right of* `nums[i]`.

 

**Example 1:**

```
Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
```

**Example 2:**

```
Input: nums = [-1]
Output: [0]
```

**Example 3:**

```
Input: nums = [-1,-1]
Output: [0,0]
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-104 <= nums[i] <= 104`

#### 解析

Because this question can be solved by single point modification and interval sum, we can use binary indexed tree or segment tree. Moreover the number range is larger than num length, we can compress it.

1. Segment tree + compression
2. BIT + compression

#### 代码

```c++
struct SegTree {
    vector<int> st;
    SegTree(int n) {
        st.resize(n*4, 0);
    }

    void update(int idx, int start, int end, int l, int r, int val) {
        if (l <= start && end <= r) {
            st[idx] += val;
            return;
        }
        int mid = (start+end) >> 1;
        if (l <= mid) update(idx*2+1, start, mid, l, r, val);
        if (r > mid) update(idx*2+2, mid+1, end, l, r, val);
        st[idx] = st[idx*2+1] + st[idx*2+2];
    }
    int query(int idx, int start, int end, int l, int r) {
        if (l <= start && end <= r) {
            return st[idx];
        }
        int mid = (start+end) >> 1;
        int ans = 0;
        if (l <= mid) ans += query(idx*2+1, start, mid, l, r);
        if (r > mid) ans += query(idx*2+2, mid+1, end, l, r);
        return ans;
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        // compression
        set<int> s;
        for (auto& num : nums) s.insert(num);
        unordered_map<int, int> indexes;
        int idx = 1;
        for (auto& num : s) {
            indexes[num] = idx++;
        }
        int mN = 1e5+2;
        SegTree root(mN);
        vector<int> res(nums.size(), 0);
        for (int i = nums.size()-1; i >= 0; i--) {
            int cur = indexes[nums[i]];
            res[i] = root.query(0, 0, mN, 0, cur-1);
            root.update(0, 0, mN, cur, cur, 1);
        }
        return res;
    }
};
```

```c++
struct BIT {
    vector<int> tree;
    BIT(int n) {
        tree.resize(n+1, 0);
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int x, int val) {
        for (int i = x; i < tree.size(); i+=lowbit(i)) tree[i] += val;
    }
    int get(int x) {
        int res = 0;
        for (int i = x; i > 0; i-=lowbit(i)) res += tree[i];
        return res;
    }

    int query(int a, int b) {
        return get(b) - get(a-1);
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        map<int, int> m;
        auto copy = nums;
        sort(copy.begin(), copy.end());
        int idx = 1;
        for (auto& val : copy) {
            if (m.insert({val, idx}).second) {
                idx++;
            }
        }
        BIT tree(idx);
        vector<int> res(nums.size(), 0);
        for (int i = nums.size()-1; i >= 0; i--) {
            int val = m[nums[i]];
            res[i] = tree.query(1, val-1);
            tree.add(val, 1);
        }
        return res;
    }
};
```

### [324. Wiggle Sort II](https://leetcode.com/problems/wiggle-sort-ii/)

Given an integer array `nums`, reorder it such that `nums[0] < nums[1] > nums[2] < nums[3]...`.

You may assume the input array always has a valid answer.

 

**Example 1:**

```
Input: nums = [1,5,1,1,6,4]
Output: [1,6,1,5,1,4]
Explanation: [1,4,1,5,1,6] is also accepted.
```

**Example 2:**

```
Input: nums = [1,3,2,2,3,1]
Output: [2,3,1,3,1,2]
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 104`
- `0 <= nums[i] <= 5000`
- It is guaranteed that there will be an answer for the given input `nums`.

 

**Follow Up:** Can you do it in `O(n)` time and/or **in-place** with `O(1)` extra space?

#### Solution

https://leetcode.com/problems/wiggle-sort-ii/discuss/77677/O(n)%2BO(1)-after-median-Virtual-Indexing

https://leetcode.cn/problems/wiggle-sort-ii/solutions/45144/yi-bu-yi-bu-jiang-shi-jian-fu-za-du-cong-onlognjia/

#### Code

```c++
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        auto midptr = nums.begin() + n / 2;
        nth_element(nums.begin(), midptr, nums.end());
        int mid = *midptr;
        #define A(i) (nums[(1+2*i) % (n|1)])

        int i = 0, j = 0, k = n - 1;
        while (j <= k) {
            if (A(j) < mid) {
                swap(A(j), A(k--));
            }
            else if (A(j) > mid) {
                swap(A(i++), A(j++));
            }
            else {
                j++;
            }
        }
    }
};
```



### [326. Power of Three](https://leetcode.com/problems/power-of-three/)

Given an integer `n`, return *`true` if it is a power of three. Otherwise, return `false`*.

An integer `n` is a power of three, if there exists an integer `x` such that `n == 3x`.

 

**Example 1:**

```
Input: n = 27
Output: true
Explanation: 27 = 33
```

**Example 2:**

```
Input: n = 0
Output: false
Explanation: There is no x where 3x = 0.
```

**Example 3:**

```
Input: n = -1
Output: false
Explanation: There is no x where 3x = (-1).
```

 

**Constraints:**

- `-231 <= n <= 231 - 1`

 

**Follow up:** Could you solve it without loops/recursion?

#### Solution

3^20 > INT_MAX, 3^19%3==0

#### Code

```c++
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        if (n == 1) return true;
        while(n > 1) {
            if (n % 3 != 0) return false;
            n /= 3;
        }
        return true;
    }
};

class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && (int(pow(3, 19)) % 3 == 0);
    }
};
```



### [328. Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/)

Given the `head` of a singly linked list, group all the nodes with odd indices together followed by the nodes with even indices, and return *the reordered list*.

The **first** node is considered **odd**, and the **second** node is **even**, and so on.

Note that the relative order inside both the even and odd groups should remain as it was in the input.

You must solve the problem in `O(1)` extra space complexity and `O(n)` time complexity.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/10/oddeven-linked-list.jpg)

```
Input: head = [1,2,3,4,5]
Output: [1,3,5,2,4]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/03/10/oddeven2-linked-list.jpg)

```
Input: head = [2,1,3,5,6,4,7]
Output: [2,3,6,7,1,5,4]
```

 

**Constraints:**

- The number of nodes in the linked list is in the range `[0, 104]`.
- `-106 <= Node.val <= 106`

#### Solution



#### Code

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;
        auto* head2 = head->next;
        auto* odd = head;
        auto* even = head2;
        auto* prev = odd;
        while (odd && even) {
            odd->next = even->next;
            prev = odd;
            odd = odd->next;
            if (odd) {
                even->next = odd->next;
                even = even->next;
            }
        }
        if (odd) prev = odd;
        prev->next = head2;
        return head;
    }
};
```



### [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

Given an `m x n` integers `matrix`, return *the length of the longest increasing path in* `matrix`.

From each cell, you can either move in four directions: left, right, up, or down. You **may not** move **diagonally** or move **outside the boundary** (i.e., wrap-around is not allowed).

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/05/grid1.jpg)

```
Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/01/27/tmp-grid.jpg)

```
Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
```

**Example 3:**

```
Input: matrix = [[1]]
Output: 1
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 200`
- `0 <= matrix[i][j] <= 231 - 1`

#### Solution

Same with poj滑雪. DP + Memory. O(MN).

#### Code

```cpp
class Solution {
private:
    vector<int> nx = {0, 1, 0, -1, 0};
    int DFS(vector<vector<int>>& matrix, int row, int col, vector<vector<int>>& dp) {
        if (dp[row][col] > 0) return dp[row][col];
        int len = 1;
        for (int i = 0; i < 4; i++) {
            int n_i = row + nx[i];
            int n_j = col + nx[i+1];
            if (n_i >= 0 && n_i < matrix.size() && n_j >=0 
                && n_j < matrix[0].size() && matrix[n_i][n_j] > matrix[row][col]) {
                    len = max(len, DFS(matrix, n_i, n_j, dp)+1);
                }
        }
        dp[row][col] = len;
        return len;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res = max(res, DFS(matrix, i, j, dp));
            }
        }
        return res;
    }
};
```
### [334. Increasing Triplet Subsequence](https://leetcode.com/problems/increasing-triplet-subsequence/)

Given an integer array `nums`, return `true` *if there exists a triple of indices* `(i, j, k)` *such that* `i < j < k` *and* `nums[i] < nums[j] < nums[k]`. If no such indices exists, return `false`.

 

**Example 1:**

```
Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.
```

**Example 2:**

```
Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.
```

**Example 3:**

```
Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.
```

 

**Constraints:**

- `1 <= nums.length <= 5 * 105`
- `-231 <= nums[i] <= 231 - 1`

 

**Follow up:** Could you implement a solution that runs in `O(n)` time complexity and `O(1)` space complexity?

#### Solution

Use two extra values to store the 1st element and 2nd element.

#### Code

```c++
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int m1 = INT_MAX, m2 = INT_MAX;
        for (const auto& num : nums) {
            if (num <= m1) m1 = num;
            else if (num <= m2) m2 = num;
            else return true;
        }
        return false;
    }
};
```



### [340. Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/)

Given a string `s` and an integer `k`, return *the length of the longest* 

*substring*

 *of* `s` *that contains at most* `k` ***distinct** characters*.



 

**Example 1:**

```
Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.
```

**Example 2:**

```
Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.
```

 

**Constraints:**

- `1 <= s.length <= 5 * 104`
- `0 <= k <= 50`

#### Solution

slide windows

Time complexity: O(n)

#### Code

```c++
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        vector<int> tables(256, 0);
        int start = 0;
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            tables[s[i]]++;
            if (tables[s[i]] == 1) {
                while (k == 0) {
                    tables[s[start]]--;
                    if (tables[s[start++]] == 0) k++;
                }
                k--;
            }
            if (k == 0) {
                res = max(res, i-start+1);
            }
        }
        res = max(res, (int)s.size()-start);
        return res;
    }
};
```



### [341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/)

You are given a nested list of integers `nestedList`. Each element is either an integer or a list whose elements may also be integers or other lists. Implement an iterator to flatten it.

Implement the `NestedIterator` class:

- `NestedIterator(List<NestedInteger> nestedList)` Initializes the iterator with the nested list `nestedList`.
- `int next()` Returns the next integer in the nested list.
- `boolean hasNext()` Returns `true` if there are still some integers in the nested list and `false` otherwise.

Your code will be tested with the following pseudocode:

```
initialize iterator with nestedList
res = []
while iterator.hasNext()
    append iterator.next() to the end of res
return res
```

If `res` matches the expected flattened list, then your code will be judged as correct.

 

**Example 1:**

```
Input: nestedList = [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].
```

**Example 2:**

```
Input: nestedList = [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].
```

 

**Constraints:**

- `1 <= nestedList.length <= 500`
- The values of the integers in the nested list is in the range `[-106, 106]`.

#### Solution

https://leetcode.com/problems/wiggle-sort-ii/discuss/77677/O(n)%2BO(1)-after-median-Virtual-Indexing

https://leetcode.cn/problems/wiggle-sort-ii/solutions/45144/yi-bu-yi-bu-jiang-shi-jian-fu-za-du-cong-onlognjia/

#### Code

```c++
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        m_nested_list = nestedList;
        m_cur = 0;
        m_num = false;
        setIter(0);
    }
    
    int next() {
        if (m_num) {
            int res = m_nested_list[m_cur].getInteger();
            m_cur++;
            setIter(m_cur);
            return res;
        }
        if (!m_cur_iter) return -1;
        int res = m_cur_iter->next();
        if (!m_cur_iter->hasNext()) {
            m_cur++;
            setIter(m_cur);
        }
        return res;
    }
    
    bool hasNext() {
        if (m_cur >= m_nested_list.size()) return false;
        if (m_num) return true;
        if (m_cur_iter) {
            if (m_cur_iter->hasNext()) return true;
            m_cur++;
            setIter(m_cur);
            return hasNext();
        }
        return false;
    }
public:
    bool m_num;
    
private:
    void setIter(int cur) {
        if (cur >= m_nested_list.size()) return;
        if (m_nested_list[cur].isInteger()) {
            m_num = true;
        }
        else {
            m_cur_iter = make_shared<NestedIterator>(m_nested_list[cur].getList());
            m_num = false;

        }
    }
    
    
private:
    vector<NestedInteger> m_nested_list;
    int m_cur;
    
    shared_ptr<NestedIterator> m_cur_iter;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
```



### [344. Reverse String](https://leetcode.com/problems/reverse-string/)

Write a function that reverses a string. The input string is given as an array of characters `s`.

You must do this by modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm) with `O(1)` extra memory.

 

**Example 1:**

```
Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
```

**Example 2:**

```
Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is a [printable ascii character](https://en.wikipedia.org/wiki/ASCII#Printable_characters).

#### Solution

https://leetcode.com/problems/wiggle-sort-ii/discuss/77677/O(n)%2BO(1)-after-median-Virtual-Indexing

https://leetcode.cn/problems/wiggle-sort-ii/solutions/45144/yi-bu-yi-bu-jiang-shi-jian-fu-za-du-cong-onlognjia/

#### Code

```c++
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};
```



### [348. Design Tic-Tac-Toe](https://leetcode.com/problems/design-tic-tac-toe/)

Assume the following rules are for the tic-tac-toe game on an `n x n` board between two players:

1. A move is guaranteed to be valid and is placed on an empty block.
2. Once a winning condition is reached, no more moves are allowed.
3. A player who succeeds in placing `n` of their marks in a horizontal, vertical, or diagonal row wins the game.

Implement the `TicTacToe` class:

- `TicTacToe(int n)` Initializes the object the size of the board `n`.

- ```
  int move(int row, int col, int player)
  ```

   

  Indicates that the player with id

   

  ```
  player
  ```

   

  plays at the cell

   

  ```
  (row, col)
  ```

   

  of the board. The move is guaranteed to be a valid move, and the two players alternate in making moves. Return

  - `0` if there is **no winner** after the move,
  - `1` if **player 1** is the winner after the move, or
  - `2` if **player 2** is the winner after the move.

 

**Example 1:**

```
Input
["TicTacToe", "move", "move", "move", "move", "move", "move", "move"]
[[3], [0, 0, 1], [0, 2, 2], [2, 2, 1], [1, 1, 2], [2, 0, 1], [1, 0, 2], [2, 1, 1]]
Output
[null, 0, 0, 0, 0, 0, 0, 1]

Explanation
TicTacToe ticTacToe = new TicTacToe(3);
Assume that player 1 is "X" and player 2 is "O" in the board.
ticTacToe.move(0, 0, 1); // return 0 (no one wins)
|X| | |
| | | |    // Player 1 makes a move at (0, 0).
| | | |

ticTacToe.move(0, 2, 2); // return 0 (no one wins)
|X| |O|
| | | |    // Player 2 makes a move at (0, 2).
| | | |

ticTacToe.move(2, 2, 1); // return 0 (no one wins)
|X| |O|
| | | |    // Player 1 makes a move at (2, 2).
| | |X|

ticTacToe.move(1, 1, 2); // return 0 (no one wins)
|X| |O|
| |O| |    // Player 2 makes a move at (1, 1).
| | |X|

ticTacToe.move(2, 0, 1); // return 0 (no one wins)
|X| |O|
| |O| |    // Player 1 makes a move at (2, 0).
|X| |X|

ticTacToe.move(1, 0, 2); // return 0 (no one wins)
|X| |O|
|O|O| |    // Player 2 makes a move at (1, 0).
|X| |X|

ticTacToe.move(2, 1, 1); // return 1 (player 1 wins)
|X| |O|
|O|O| |    // Player 1 makes a move at (2, 1).
|X|X|X|
```

 

**Constraints:**

- `2 <= n <= 100`
- player is `1` or `2`.
- `0 <= row, col < n`
- `(row, col)` are **unique** for each different call to `move`.
- At most `n2` calls will be made to `move`.

 

**Follow-up:** Could you do better than `O(n2)` per `move()` operation?

#### Solution

using rows, cols, diagonals to store the number of players.

Time complexity:O(1)

Space complexity:O(n)

#### Code

```c++
class TicTacToe {
    // number of player1, player2
    vector<vector<int>> rows;
    vector<vector<int>> cols;
    vector<vector<int>> diagonals;
    int winner;
    int size;
public:
    TicTacToe(int n) {
        rows.resize(n, vector<int>(2, 0));
        cols.resize(n, vector<int>(2, 0));
        diagonals.resize(2, vector<int>(2, 0));
        winner = 0;
        size = n;
    }
    
    int move(int row, int col, int player) {
        if (winner > 0) return winner;
        rows[row][player-1]++;
        cols[col][player-1]++;
        if (row==col) {
            diagonals[0][player-1]++;
            // center
            if (size & 1 && row == size / 2) {
                diagonals[1][player-1]++;
            }
        }
        else if (row == size-1-col) {
            diagonals[1][player-1]++;
            // center
            if (size & 1 && row == size / 2) {
                diagonals[0][player-1]++;
            }
        }
        if (rows[row][player-1] == size || cols[col][player-1] == size 
            || diagonals[0][player-1] == size || diagonals[1][player-1] == size) {
                winner = player;
                return player;
            }

        return 0;
    }
};
```



### [350. Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/)

Given two integer arrays `nums1` and `nums2`, return *an array of their intersection*. Each element in the result must appear as many times as it shows in both arrays and you may return the result in **any order**.

 

**Example 1:**

```
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
```

**Example 2:**

```
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Explanation: [9,4] is also accepted.
```

 

**Constraints:**

- `1 <= nums1.length, nums2.length <= 1000`
- `0 <= nums1[i], nums2[i] <= 1000`

 

**Follow up:**

- What if the given array is already sorted? How would you optimize your algorithm?
- What if `nums1`'s size is small compared to `nums2`'s size? Which algorithm is better?
- What if elements of `nums2` are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

#### Solution

hashtable

#### Code

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> tables;
        for (int i = 0; i < nums2.size(); i++) {
            auto ret = tables.insert({nums2[i], 1});
            if (!ret.second) {
                ret.first->second++;
            }
        }
        vector<int> res;
        for (int i = 0; i < nums1.size(); i++) {
            auto iter = tables.find(nums1[i]);
            if (iter != tables.end()) {
                if (iter->second > 0) {
                    res.push_back(nums1[i]);
                    iter->second--;
                }
            }
        }
        return res;
    }
};
```



### [371. Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/)

Given two integers `a` and `b`, return *the sum of the two integers without using the operators* `+` *and* `-`.

 

**Example 1:**

```
Input: a = 1, b = 2
Output: 3
```

**Example 2:**

```
Input: a = 2, b = 3
Output: 5
```

 

**Constraints:**

- `-1000 <= a, b <= 1000`

#### Solution

Sum: XOR

carry: & <<

#### Code

```c++
class Solution {
public:
    int getSum(int a, int b) {
        do {
            int sum = a^b;
            int carry = (a&b)<<1;
            a = sum, b = carry;
        } while(b);
        
        return a;
    }
};
```



### [378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)

Given an `n x n` `matrix` where each of the rows and columns is sorted in ascending order, return *the* `kth` *smallest element in the matrix*.

Note that it is the `kth` smallest element **in the sorted order**, not the `kth` **distinct** element.

You must find a solution with a memory complexity better than `O(n2)`.

 

**Example 1:**

```
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
```

**Example 2:**

```
Input: matrix = [[-5]], k = 1
Output: -5
```

 

**Constraints:**

- `n == matrix.length == matrix[i].length`
- `1 <= n <= 300`
- `-109 <= matrix[i][j] <= 109`
- All the rows and columns of `matrix` are **guaranteed** to be sorted in **non-decreasing order**.
- `1 <= k <= n2`

 

**Follow up:**

- Could you solve the problem with a constant memory (i.e., `O(1)` memory complexity)?
- Could you solve the problem in `O(n)` time complexity? The solution may be too advanced for an interview but you may find reading [this paper](http://www.cse.yorku.ca/~andy/pubs/X+Y.pdf) fun.

#### Solution

Solution 1:**Max Heap keeps up to k elements**

Time: `O(M * N * logK)`

Space complexity: O(k)

**Solution 2: Min Heap to find kth smallest element from amongst N sorted list**

![image](https://assets.leetcode.com/users/images/47843946-761b-49f9-a06f-5a973fca3ddc_1625719598.4144652.png)

- Since each of the rows in matrix are already sorted, we can understand the problem as finding the **kth smallest element** from amongst `M` sorted rows.
- We start the pointers to point to the beginning of each rows, then we iterate `k` times, for each time `ith`, the top of the `minHeap` is the `ith` smallest element in the matrix. We pop the `top` from the `minHeap` then add the next element which has the same row with that `top` to the `minHeap`.

Complexity:

- Time: `O(K * logK)`
- Space: `O(K)`

#### Code

```c++
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int> q;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                q.push(matrix[i][j]);
                if (q.size() > k) {
                    q.pop();
                }
            }
        }
        return q.top();
    }
};
```

```c++
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
        for (int i = 0; i < min((int)matrix.size(), k); i++) {
            q.push({matrix[i][0], i, 0});
        }
        int ans = 0;
        for (int i = 0; i < k; i++) {
            auto cur = q.top(); q.pop();
            ans = cur[0];
            int row = cur[1], col = cur[2];
            int next_c = col + 1;
            if (next_c < matrix[0].size()) {
                q.push({matrix[row][next_c], row, next_c});
            }
        }
        return ans;
    }
};
```



### [380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/)

Implement the `RandomizedSet` class:

- `RandomizedSet()` Initializes the `RandomizedSet` object.
- `bool insert(int val)` Inserts an item `val` into the set if not present. Returns `true` if the item was not present, `false` otherwise.
- `bool remove(int val)` Removes an item `val` from the set if present. Returns `true` if the item was present, `false` otherwise.
- `int getRandom()` Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the **same probability** of being returned.

You must implement the functions of the class such that each function works in **average** `O(1)` time complexity.

 

**Example 1:**

```
Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
```

 

**Constraints:**

- `-231 <= val <= 231 - 1`
- At most `2 * ``105` calls will be made to `insert`, `remove`, and `getRandom`.
- There will be **at least one** element in the data structure when `getRandom` is called.

#### Solution

Vector and hashmap to store the position of vector.

#### Code

```c++
class RandomizedSet {
public:
    RandomizedSet() {
        m_nums.clear();
        m_index.clear();
    }
    
    bool insert(int val) {
        if (m_index.find(val) != m_index.end()) return false;
        m_nums.push_back(val);
        m_index.insert({val, m_nums.size() - 1});
        return true;
    }
    
    bool remove(int val) {
        auto iter = m_index.find(val);
        if (iter == m_index.end()) return false;
        int index = iter->second;
        swap(m_nums[index], m_nums[m_nums.size() - 1]);
        m_index[m_nums[index]] = index;
        m_index.erase(val);
        m_nums.pop_back();
        return true;
    }
    
    int getRandom() {
        return m_nums[rand() % (int)(m_nums.size())];
    }
private:
    vector<int> m_nums;
    unordered_map<int, int> m_index;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```



### [384. Shuffle an Array](https://leetcode.com/problems/shuffle-an-array/)

Given an integer array `nums`, design an algorithm to randomly shuffle the array. All permutations of the array should be **equally likely** as a result of the shuffling.

Implement the `Solution` class:

- `Solution(int[] nums)` Initializes the object with the integer array `nums`.
- `int[] reset()` Resets the array to its original configuration and returns it.
- `int[] shuffle()` Returns a random shuffling of the array.

 

**Example 1:**

```
Input
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
Output
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

Explanation
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();    // Shuffle the array [1,2,3] and return its result.
                       // Any permutation of [1,2,3] must be equally likely to be returned.
                       // Example: return [3, 1, 2]
solution.reset();      // Resets the array back to its original configuration [1,2,3]. Return [1, 2, 3]
solution.shuffle();    // Returns the random shuffling of array [1,2,3]. Example: return [1, 3, 2]
```

 

**Constraints:**

- `1 <= nums.length <= 50`
- `-106 <= nums[i] <= 106`
- All the elements of `nums` are **unique**.
- At most `104` calls **in total** will be made to `reset` and `shuffle`.

#### Solution

https://leetcode.com/problems/shuffle-an-array/solutions/1283088/c-solution-with-intuition-and-explanation/

#### Code

```c++
class Solution {
private:
    vector<int> nums;
    
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
    }
    
    vector<int> reset() {
        return nums;
    }
    
    vector<int> shuffle() {
        vector<int> res(nums);
        for (int i = 0; i < res.size(); i++) {
            int pos = rand() % (res.size() - i);
            swap(res[i], res[pos + i]);
        }
        return res;
        
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
```



### [387. First Unique Character in a String](https://leetcode.com/problems/first-unique-character-in-a-string/)

Given a string `s`, *find the first non-repeating character in it and return its index*. If it does not exist, return `-1`.

 

**Example 1:**

```
Input: s = "leetcode"
Output: 0
```

**Example 2:**

```
Input: s = "loveleetcode"
Output: 2
```

**Example 3:**

```
Input: s = "aabb"
Output: -1
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s` consists of only lowercase English letters.

#### Solution



#### Code

```c++
class Solution {
public:
    int firstUniqChar(string s) {
        if (s.empty()) return -1;
        vector<int> tables(26, 0);
        for (const auto& ch : s) {
            tables[ch-'a']++;
        }
        for (int i = 0; i < s.size(); i++) {
            if (tables[s[i] - 'a'] == 1) return i;
        }
        return -1;
    }
};
```



