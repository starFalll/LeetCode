## Merge Intervals

[2158. Amount of New Area Painted Each Day](https://leetcode.com/problems/amount-of-new-area-painted-each-day/)

```c++
// Merge Intervals
//For each day, we first search for the existing painted interval on the left. If that interval exists and overlaps, we extend it. Otherwise, we create a new interval.

// Then, we go right and merge all overlapping intervals into the current (cur) one. All this time, we carefully track the newly painted area.
class Solution {
public:
    vector<int> amountPainted(vector<vector<int>>& paint) {
        map<int, int> m;
        vector<int> res;
        for (auto& p : paint) {
            int l = p[0], r = p[1];
            auto next = m.upper_bound(l), cur = next;
            // extend left
            if (cur != m.begin() && prev(cur)->second >= l) {
                cur = prev(cur);
                l = cur->second;
            }
            // new insert
            else {
                cur = m.insert({l, r}).first;
            }
            int pt = r-l;
            while (next != m.end() && next->first < r) {
                pt -= min(next->second, r) - next->first;
                r = max(next->second, r);
                m.erase(next++);
            }
            cur->second = max(r, cur->second);
            res.push_back(max(0, pt));
        }
        return res;
    }
};
```

### Greedy

Actually, interval merge problems don't need segment tree or map in Leetcode, it is so easy!

[1024. Video Stitching](https://leetcode.com/problems/video-stitching/)

```c++
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        sort(clips.begin(), clips.end());
        int res = 0;
        for (int i = 0, st = 0, end = 0; st < time; st = end, ++res) {
            for (; i < clips.size() && clips[i][0] <= st; i++) {
                end = max(end, clips[i][1]);
            }
            if (st == end) return -1;
        }
        return res;
    }
};
```

[1326. Minimum Number of Taps to Open to Water a Garden](https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/)
