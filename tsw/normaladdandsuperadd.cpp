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
    long long sum1 ,sum2 ,sum3 ,sum4= 0;
    int len = nums.size();
    for (int i=0;i<len;i+=4){
        sum1 += nums[i];
        sum2+= nums[i+1];
        sum3+= nums[i+2];
        sum4+= nums[i+3];
    }
    return sum1+sum2+sum3+sum4;
}

int main() {
    const int n = pow(2, 23); // 假设有131,072个数
    const int s = pow(2, 13); // 重复次数
    const int measurements = 2000; // 测量次数
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

     // 测试优化算法性能
    double optimizedSumElapsedTimeTotal = 0.0;
    LARGE_INTEGER freq1, head1, tail1;
    QueryPerformanceFrequency(&freq1); // 获取性能计数器的频率

    for (int j = 0; j < measurements; ++j) {
        QueryPerformanceCounter(&head1); // 获取开始时间
        for (int i = 0; i < s; i++) {
            optimizedSum(nums);
        }
        QueryPerformanceCounter(&tail1); // 获取结束时间
        double elapsedTime = static_cast<double>(tail1.QuadPart - head1.QuadPart) / static_cast<double>(freq1.QuadPart);
        optimizedSumElapsedTimeTotal += elapsedTime; // 累加每次测量的时间
    }

    double optimizedSumElapsedTimeAverage = optimizedSumElapsedTimeTotal / measurements; // 计算平均时间
    cout << "优化算法的平均时间为：" << optimizedSumElapsedTimeAverage << endl;

    return 0;
}

