#ifndef REGRESSION_MEANSQUAREDERROR_H
#define REGRESSION_MEANSQUAREDERROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class MSE {
public:
    // Unweighted MSE
    static double compute(const double* actual, const double* predicted, std::size_t n)
    {
        double sum_sq_diff = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_sq_diff) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double diff = actual[i] - predicted[i];
            sum_sq_diff += diff * diff;
        }

        return sum_sq_diff / static_cast<double>(n);
    }

    // Weighted MSE
    static double compute(const double* actual, const double* predicted, 
                          const double* weights, std::size_t n)
    {
        double sum_sq_diff = 0.0;
        double sum_w       = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_sq_diff, sum_w) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double diff = actual[i] - predicted[i];
            double w    = weights[i];
            sum_sq_diff += w * diff * diff;
            sum_w       += w;
        }

        return sum_sq_diff / sum_w;
    }
};

#endif
