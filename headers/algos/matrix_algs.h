#ifndef MATRIX_ALGS_HEADER
#define MATRIX_ALGS_HEADER
#pragma once

#include <vector>

using namespace std;

// #867.
class MatTransposeSolver {
public:
    vector<vector<int>> LaunchTranspose(vector<vector<int>> &A) {
        if (A.empty()) { return vector<vector<int>> {}; }
        int row = A.size();
        int col = A[0].size();
        vector<vector<int>> res(col, vector<int>(row, 0));

        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                // 核心逻辑：
                res[c][r] = A[r][c];
            }
        }
        return res;
    }
};

// #566. reshape matrix
class ReshapeSolver {
public:
    vector<vector<int>> LaunchReshape(vector<vector<int>> &mat, int r, int c) {
        if (mat.size() * mat[0].size() != r * c) { return mat; }
        vector<int> flattened = Flatten(mat);
        vector<vector<int>> res = Flatten2Mat(flattened, r, c);
        return res;
    }

private:
    vector<int> Flatten(vector<vector<int>> &mat) {
        int row = mat.size();
        int col = mat[0].size();
        vector<int> res(row * col, 0);
        int count = 0;
        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < col; ++c) {
                res[count++] = mat[r][c];
            }
        }
        return res;
    }
    vector<vector<int>> Flatten2Mat(vector<int> &flattened, int r, int c) {
        vector<vector<int>> res(r, vector<int>(c, 0));
        int count = 0;

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                res[i][j] = flattened[count++];
            }
        }
        return res;
    }
};

// mat mul
class MatmulSolver {
public:
    vector<vector<int>> LaunchSolver(
            vector<vector<int>> &mat_a, vector<vector<int>> &mat_b) {

        int res_row = mat_a.size();
        int res_col = mat_b[0].size();
        int dis = mat_b.size();
        vector<vector<int>> res(res_row, vector<int>(res_col, 0));

        for (int i = 0; i < res_row; ++i) {
            for (int j = 0; j < res_col; ++j) {
                for (int k = 0; k < dis; ++k) {
                    res[i][j] += mat_a[i][k] * mat_b[k][j];
                }
            }
        }
        return res;
    }
};

// #54. 
/*
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
*/
// insight：程序不管什么spiral，程序只管边界，只要边界对了，你指定的遍历顺序对了，那自然即对了
class SpiralMatrix {
public:
    vector<int> Launch(vector<vector<int>>& matrix){
        vector<int> res;
        if (matrix.empty()) return res;

        int left = 0, right = matrix[0].size() - 1;
        int top = 0, bottom = matrix.size() - 1;

        while(left <= right && top <= bottom) {
            // 遍历右边
            for (int i = left; i <= right; ++i) {
                res.push_back(matrix[top][i]);
            }
            top++;  // 遍历了top一行，更新top边界

            // 遍历下边
            for (int i = top; i <= bottom; ++i) {
                res.push_back(matrix[i][right]);
            }
            right--; // 遍历了right一列，更新right边界

            // 向左遍历
            if (top <= bottom) {
                for (int i = right; i >= left; --i) {
                    res.push_back(matrix[bottom][i]);
                }
                bottom--; // 遍历了bottom一行，更新bottom 边界
            }

            // 向上遍历
            if (left <= right) {
                for (int i = bottom; i >= top; --i){
                    res.push_back(matrix[i][left]);
                }
                left++; // 遍历了left一列后，更新left边界
            }
        }
        return res;
    }
};

#endif // MATRIX_ALGS_HEADER
