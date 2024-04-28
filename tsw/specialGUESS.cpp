#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// ��ȡ��������
void readInput(const string& file_path, vector<vector<int>>& elimination_rows, vector<vector<int>>& eliminated_rows, int num_columns) {
    ifstream file(file_path);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("��Ԫ��") != string::npos) {
                elimination_rows.push_back(parseSparseVector(line, num_columns));
            } else if (line.find("����Ԫ��") != string::npos) {
                eliminated_rows.push_back(parseSparseVector(line, num_columns));
            }
        }
        file.close();
    } else {
        cerr << "�޷����ļ���" << file_path << endl;
        exit(EXIT_FAILURE);
    }
}

// ����ϡ������
vector<int> parseSparseVector(const string& line, int num_columns) {
    vector<int> sparse_vector(num_columns, 0);
    stringstream ss(line);
    string token;
    while (ss >> token) {
        if (token != "����Ԫ��" && token != "��Ԫ��") {
            int idx = stoi(token);
            sparse_vector[idx] = 1;
        }
    }
    return sparse_vector;
}

// ִ����Ԫ����
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

// д�������ļ�
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
        cerr << "�޷�д���ļ���" << file_path << endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    // �����ļ�·��������
    string input_file = "input.txt";
    int num_columns = 10; // ��������Ϊ10��

    // ��ȡ��������
    vector<vector<int>> elimination_rows;
    vector<vector<int>> eliminated_rows;
    readInput(input_file, elimination_rows, eliminated_rows, num_columns);

    // ִ����Ԫ����
    for (auto& eliminated_row : eliminated_rows) {
        eliminate(eliminated_row, elimination_rows);
    }

    // д�������ļ�
    string output_file = "output.txt";
    writeOutput(output_file, eliminated_rows);

    cout << "��Ԫ��������ɣ��������д���ļ���" << output_file << endl;

    return 0;
}
