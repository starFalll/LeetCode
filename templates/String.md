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