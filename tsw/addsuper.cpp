#include <iostream>
#include <vector>
#include <windows.h>
#include <cmath>
using namespace std;

// ƽ���㷨������ۼӣ��˴�δʹ�ã�
long long trivialSum(const vector<int>& nums) {
    long long sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum;
}

// �Ż��㷨���ǵݹ��㷨���������ֱ�����ս��
long long optimizedSum(const vector<int>& nums) {
    long long sum1 = 0, sum2 = 0;
    int len = nums.size();
    for (int i = 0; i < len; i += 2) {
        sum1 += nums[i];
        if (i + 1 < len) { // ȷ����Խ��
            sum2 += nums[i + 1];
        }
    }
    return sum1 + sum2;
}

int main() {
    const int n = pow(2, 16); // ������131,072����
    const int s = pow(2, 21); // �ظ�����
    const int measurements = 100; // ��������

    // ���ɲ�������
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = i + 1;
    }

    // �����Ż��㷨����
    double optimizedSumElapsedTimeTotal = 0.0;
    LARGE_INTEGER freq, head, tail;
    QueryPerformanceFrequency(&freq); // ��ȡ���ܼ�������Ƶ��

    for (int j = 0; j < measurements; ++j) {
        QueryPerformanceCounter(&head); // ��ȡ��ʼʱ��
        for (int i = 0; i < s; i++) {
            optimizedSum(nums);
        }
        QueryPerformanceCounter(&tail); // ��ȡ����ʱ��
        double elapsedTime = static_cast<double>(tail.QuadPart - head.QuadPart) / static_cast<double>(freq.QuadPart);
        optimizedSumElapsedTimeTotal += elapsedTime; // �ۼ�ÿ�β�����ʱ��
    }

    double optimizedSumElapsedTimeAverage = optimizedSumElapsedTimeTotal / measurements; // ����ƽ��ʱ��
    cout << "�Ż��㷨��ƽ��ʱ��Ϊ��" << optimizedSumElapsedTimeAverage << endl;

    return 0;
}
