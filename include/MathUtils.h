#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "Types.h"

class MathUtils {
public:
    
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

        
        Vector x(n);
        for (int i = n - 1; i >= 0; i--) {
            Scalar sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        return x;
    }
};

#endif