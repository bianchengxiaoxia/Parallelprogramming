#include <iostream>
#include <vector>
#include <windows.h>
#include <cmath>
using namespace std;

// 平凡算法：逐个累加
long long trivialSum(const vector<int>& nums) {
    long long sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum;
}

// 优化算法：非递归算法，两两相加直至最终结果
long long optimizedSum(const vector<int>& nums) {
    long long sum1 = 0; long long sum2 = 0;
    int len = nums.size();
    for (int i = 0; i < len; i += 2) {
        sum1 += nums[i];
        if (i + 1 < len) {
            sum2 += nums[i + 1];
        }
    }
    return sum1 + sum2;
}

int main() {
    const int n = pow(2, 19); // 假设有131,072个数
    const int s = pow(2, 18); // 重复次数
    const int measurements = 100; // 测量次数

    // 生成测试数据
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }

    // 测试平凡算法性能
    LARGE_INTEGER freq, head, tail;
    QueryPerformanceFrequency(&freq); // 获取性能计数器的频率

    double trivialSumElapsedTime = 0.0;
    for (int j = 0; j < measurements; ++j) {
        QueryPerformanceCounter(&head); // 获取开始时间
        for (int i = 0; i < s; i++) {
            trivialSum(nums);
        }
        QueryPerformanceCounter(&tail); // 获取结束时间
        trivialSumElapsedTime += static_cast<double>(tail.QuadPart - head.QuadPart) / static_cast<double>(freq.QuadPart);
    }
    trivialSumElapsedTime /= measurements; // 计算平均时间
    cout << "平凡算法的平均时间为：" << trivialSumElapsedTime << endl;


    return 0;
}
