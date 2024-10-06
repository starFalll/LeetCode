# String

## Nested processing

[1096. Brace Expansion II](https://leetcode.com/problems/brace-expansion-ii/)

Template:

```c++
#include <sstream> // std::stringstream
class Solution {
    set<string> s;
    void DFS(string exp) {
        auto j = exp.find('}');
        if (j == string::npos) {
            s.insert(exp);
            return;
        }
        auto i = exp.rfind('{', j);
        string before = exp.substr(0, i);
        string after = exp.substr(j+1);
        string mid = exp.substr(i+1, j-i-1);
        stringstream ss(mid);
        string tmp;
        while (getline(ss, tmp, ',')) {
            DFS(before + tmp + after);
        }
    }
public:
    vector<string> braceExpansionII(string expression) {
        DFS(expression);
        return vector<string> (s.begin(), s.end());
    }
};
```

Similar:[394. Decode String](https://leetcode.com/problems/decode-string/)

## KMP

[28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)

如何更好地理解和掌握 KMP 算法? - 海纳的回答 - 知乎
https://www.zhihu.com/question/21923021/answer/281346746

![img](https://picx.zhimg.com/80/v2-40b4885aace7b31499da9b90b7c46ed3_720w.webp?source=1def8aca)

![img](https://picx.zhimg.com/80/v2-03a0d005badd0b8e7116d8d07947681c_720w.webp?source=1def8aca)

Time complexity: O(n+m) length of s+length of p

Space complexity: O(m)

```c++
void getNext(string& s, vector<int>& next)
{
    next.assign(s.size(), 0);
    next[0] = -1;
    int i = 0, j = -1;
    // because we first ++i, then assign value to next, so i < s.size()-1
    while (i < s.size()-1) {
        if (j == -1 || s[i] == s[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

int KMP(string& s, string& p)
{
    vector<int> next;
    getNext(p, next);
    int i = 0, j = 0;
    // note: the p.size is unsigned interger, but j can be -1 which would be wrong, so using type convert
    while (i < s.size() && j < (int) p.size()) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j == p.size()) return i-j;
    return -1;
}
```

### PMT (Partial Match Table)

The value inside of Partial Match Table is the **longest common prefix and suffix** of str.

Calculate the pmt table, which can be used to calculate the **longest common prefix and suffix** of str

[214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/)

```c++
void getPMT(string& s, vector<int>& pmt)
{
    pmt.assign(s.size(), 0);
    pmt[0] = 0;
    int i = 1, j = 0;
    while (i < s.size()) {
        if (s[i] == s[j]) {
            pmt[i] = j+1;
            i++;
            j++;
        }
        else if (j == 0) {
            pmt[i] = 0;
            i++;
        }
        else {
            j = pmt[j-1];
        }
    }
}
```

