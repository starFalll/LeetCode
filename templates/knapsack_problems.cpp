// https://www.programmercarl.com/%E8%83%8C%E5%8C%85%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%8001%E8%83%8C%E5%8C%85-1.html

// dp processing steps
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

// 01 knapsack
// 01 背包
// Each item can only be used once
void test_1_wei_bag_problem() {
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    // Initial
    vector<int> dp(bagWeight + 1, 0);
    for(int i = 0; i < weight.size(); i++) { // Iterate over items
        for(int j = bagWeight; j >= weight[i]; j--) { // Traverse backpack capacity
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]); // max value 求最大值用max选其中一个
            // dp[j] += dp[j - weight[i]] + value[i]  total sum, 求和则用这种
        }
    }
    cout << dp[bagWeight] << endl;
}

// Unbounded Knapsack Problem
// 完全背包
// Each item has unlimited (that is, it can be put into the backpack multiple times)
void test_2_wei_bag_problem() {
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    int bagWeight = 4;

    // Initial
    vector<int> dp(bagWeight + 1, 0);
    // If you want to find the number of combinations, the outer layer for loop traverses the items, and the inner layer for traverses the backpack.
    // If you want to find the number of permutations, the outer for loop traverses the backpack, and the inner loop traverses the items.
    // 如果求组合数就是外层for循环遍历物品，内层for遍历背包。
    // 如果求排列数就是外层for遍历背包，内层for循环遍历物品。
    for(int i = 0; i < weight.size(); i++) { // Iterate over items
        for(int j = weight[i]; j <= bagWeight; j++) { // ------this line is different. Traverse backpack capacity
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]); // max value 求最大值用max选其中一个
            // dp[j] += dp[j - weight[i]] + value[i]  total sum, 求和则用这种
        }
    }
    cout << dp[bagWeight] << endl;
}

// multiple choice knapsack problem
// 多重背包，为01背包的变种
// There are N items and a backpack with capacity V. There are at most Mi items available for the i-th item, the space consumed by each item is Ci, and the value is Wi. Finding which items to put into the backpack can make the sum of the space consumed by these items not exceed the capacity of the backpack, and the sum of the values is the largest.
// 有N种物品和一个容量为V 的背包。第i种物品最多有Mi件可用，每件耗费的空间是Ci ，价值是Wi 。求解将哪些物品装入背包可使这些物品的耗费的空间 总和不超过背包容量，且价值总和最大。
// There are at most Mi items available for each item, and spreading the Mi items is actually a 01 knapsack problem.
//每件物品最多有Mi件可用，把Mi件摊开，其实就是一个01背包问题了。
void test_3_wei_bag_problem() {
    vector<int> weight = {1, 3, 4};
    vector<int> value = {15, 20, 30};
    vector<int> nums = {2, 3, 2};
    int bagWeight = 10;
    vector<int> dp(bagWeight + 1, 0);


    // Initial
    vector<int> dp(bagWeight + 1, 0);
    for(int i = 0; i < weight.size(); i++) { // Iterate over items
        for(int j = bagWeight; j >= weight[i]; j--) { // Traverse backpack capacity
            // 以上为01背包，然后加一个遍历个数
            // The above is 01 backpack, and then add a traversal number
            for (int k = 1; k <= nums[i] && (j - k * weight[i]) >= 0; k++) { // number of traversal
                dp[j] = max(dp[j], dp[j - k * weight[i]] + k * value[i]);
            }
        }
    }
    cout << dp[bagWeight] << endl;
}
