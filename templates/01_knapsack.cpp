// dp processing steps:
// 1. set the meaning of dp array
// 2. determine the recursive formula of dp array
// 3. figure out how to initialize dp array
// 4. determine traversal order
// 5. example derivation dp array
// 
//1. 确定dp数组（dp table）以及下标的含义
//2. 确定递推公式
//3. dp数组如何初始化
//4. 确定遍历顺序
//5. 举例推导dp数组

// https://www.programmercarl.com/%E8%83%8C%E5%8C%85%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%8001%E8%83%8C%E5%8C%85-2.html#%E4%B8%80%E7%BB%B4dp%E6%95%B0%E7%BB%84-%E6%BB%9A%E5%8A%A8%E6%95%B0%E7%BB%84
void test_1_wei_bag_problem() {
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    // Initial
    vector<int> dp(bagWeight + 1, 0);
    for(int i = 0; i < weight.size(); i++) { // Iterate over items
        for(int j = bagWeight; j >= weight[i]; j--) { // Traverse backpack capacity
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    cout << dp[bagWeight] << endl;
}

int main() {
    test_1_wei_bag_problem();
}
