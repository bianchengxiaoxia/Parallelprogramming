#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// 读取输入数据
void readInput(const string& file_path, vector<vector<int>>& elimination_rows, vector<vector<int>>& eliminated_rows, int num_columns) {
    ifstream file(file_path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("消元子") != string::npos) {
                elimination_rows.push_back(parseSparseVector(line, num_columns));
            } else if (line.find("被消元行") != string::npos) {
                eliminated_rows.push_back(parseSparseVector(line, num_columns));
            }
        }
        file.close();
    } else {
        cerr << "无法打开文件：" << file_path << endl;
        exit(EXIT_FAILURE);
    }
}

// 解析稀疏向量
vector<int> parseSparseVector(const string& line, int num_columns) {
    vector<int> sparse_vector(num_columns, 0);
    stringstream ss(line);
    string token;
    while (ss >> token) {
        if (token != "被消元行" && token != "消元子") {
            int idx = stoi(token);
            sparse_vector[idx] = 1;
        }
    }
    return sparse_vector;
}

// 执行消元计算
void eliminate(vector<int>& eliminated_row, const vector<vector<int>>& elimination_rows) {
    for (const auto& elimination_row : elimination_rows) {
        if (any_of(elimination_row.begin(), elimination_row.end(), [&](int val) { return val == 1; })) {
            for (size_t i = 0; i < elimination_row.size(); ++i) {
                if (elimination_row[i] == 1) {
                    eliminated_row[i] ^= 1;
                }
            }
        }
    }
}

// 写入结果到文件
void writeOutput(const string& file_path, const vector<vector<int>>& eliminated_rows) {
    ofstream file(file_path);
    if (file.is_open()) {
        for (const auto& row : eliminated_rows) {
            for (int val : row) {
                file << val << " ";
            }
            file << endl;
        }
        file.close();
    } else {
        cerr << "无法写入文件：" << file_path << endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    // 输入文件路径和列数
    string input_file = "input.txt";
    int num_columns = 10; // 假设列数为10列

    // 读取输入数据
    vector<vector<int>> elimination_rows;
    vector<vector<int>> eliminated_rows;
    readInput(input_file, elimination_rows, eliminated_rows, num_columns);

    // 执行消元计算
    for (auto& eliminated_row : eliminated_rows) {
        eliminate(eliminated_row, elimination_rows);
    }

    // 写入结果到文件
    string output_file = "output.txt";
    writeOutput(output_file, eliminated_rows);

    cout << "消元计算已完成，并将结果写入文件：" << output_file << endl;

    return 0;
}
