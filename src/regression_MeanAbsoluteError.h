#ifndef REGRESSION_MEANABSOLUTEERROR_H
#define REGRESSION_MEANABSOLUTEERROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class MAE {
public:
    // Unweighted MAE
    static double compute(const double* actual, const double* predicted, std::size_t n)
    {
        double sum_abs_diff = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_abs_diff) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double diff = actual[i] - predicted[i];
            sum_abs_diff += std::fabs(diff);
        }

        return sum_abs_diff / static_cast<double>(n);
    }

    // Weighted MAE
    static double compute(const double* actual, const double* predicted, 
                          const double* weights, std::size_t n)
    {
        double sum_abs_diff = 0.0;
        double sum_w        = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_abs_diff, sum_w) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double w    = weights[i];
            double diff = actual[i] - predicted[i];
            sum_abs_diff += w * std::fabs(diff);
            sum_w        += w;
        }

        return sum_abs_diff / sum_w;
    }
};

#endif
