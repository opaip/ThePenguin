#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "Types.h"
#include <cmath>
#include <algorithm>

class MathUtils {
public:
    
    
    static Matrix transpose(const Matrix& A) {
        if (A.empty()) return {};
        int rows = A.size();
        int cols = A[0].size();
        Matrix A_T(cols, Vector(rows, 0.0));
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                A_T[j][i] = A[i][j];
            }
        }
        return A_T;
    }

    
    static Matrix multiply(const Matrix& A, const Matrix& B) {
        if (A.empty() || B.empty()) return {};
        int m = A.size();
        int n = A[0].size();
        int p = B[0].size();
        
        Matrix C(m, Vector(p, 0.0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < n; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

   
    static Vector multiply(const Matrix& A, const Vector& v) {
        if (A.empty() || v.empty()) return {};
        int m = A.size();
        int n = A[0].size();
        
        Vector result(m, 0.0);
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < n; k++) {
                result[i] += A[i][k] * v[k];
            }
        }
        return result;
    }

  
    static Vector add(const Vector& a, const Vector& b) {
        if (a.size() != b.size()) return {};
        
        Vector result(a.size(), 0.0);
        for (size_t i = 0; i < a.size(); i++) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    
    static Vector solve_linear_system(Matrix A, Vector b) {
        int n = A.size();

        for (int i = 0; i < n; i++) {
            int max_row = i;
            for (int k = i + 1; k < n; k++) {
                if (std::abs(A[k][i]) > std::abs(A[max_row][i])) max_row = k;
            }
            std::swap(A[i], A[max_row]);
            std::swap(b[i], b[max_row]);

            for (int k = i + 1; k < n; k++) {
                Scalar factor = A[k][i] / A[i][i];
                b[k] -= factor * b[i];
                for (int j = i; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }

        Vector x(n, 0.0);
        for (int i = n - 1; i >= 0; i--) {
            Scalar sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            if (std::abs(A[i][i]) < 1e-12) return x;
            x[i] = (b[i] - sum) / A[i][i];
        }
        return x;
    }
};

#endif