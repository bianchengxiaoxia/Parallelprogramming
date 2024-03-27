#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
// 平凡算法：逐列访问元素的算法
/*
std::vector<int> dotProductNaive(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vector) {
    int n = matrix.size();
    std::vector<int> results(n, 0.0);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            results[j] += matrix[i][j] * vector[i];
        }
    }
    return results;
}*/

// Cache优化算法：按照行访问矩阵元素以优化缓存命中
std::vector<int> dotProductOptimized(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vector) {
    int n = matrix.size();
    std::vector<int> results(n, 0.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            results[j] += matrix[i][j] * vector[i];
        }
    }
    return results;
}

int main() {
    int n = 3000 ;// 矩阵大小
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    std::vector<int> vector(n);

    // 初始化矩阵和向量（为了简单起见，这里用随机值填充）
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = (i + j) ;
        }
        vector[i] = i ;
    }
/*
 LARGE_INTEGER freq, head, tail;
    QueryPerformanceFrequency(&freq); // 获取性能计数器的频率
    QueryPerformanceCounter(&head); // 获取开始时间
    for (int i=0;i<15;i++){
    dotProductNaive(matrix,vector);
    }
    QueryPerformanceCounter(&tail); // 获取结束时间
    double elapsedTime = static_cast<double>(tail.QuadPart - head.QuadPart) / static_cast<double>(freq.QuadPart);
    cout<< "平凡算法的时间为 ："<<elapsedTime<<endl;
    */
LARGE_INTEGER freq1, head1, tail1;
    QueryPerformanceFrequency(&freq1); // 获取性能计数器的频率
    QueryPerformanceCounter(&head1); // 获取开始时间
    for (int i=0;i<15;i++){
    dotProductOptimized(matrix,vector);
    }
    QueryPerformanceCounter(&tail1); // 获取结束时间
    double elapsedTime1 = static_cast<double>(tail1.QuadPart - head1.QuadPart) / static_cast<double>(freq1.QuadPart);
    cout<< "cache优化算法的时间为 ："<<elapsedTime1<<endl;

    return 0;
}
