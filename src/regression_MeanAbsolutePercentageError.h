#ifndef REGRESSION_MEANABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_MEANABSOLUTEPERCENTAGEERROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class MAPE {
public:
    // Unweighted MAPE
    static double compute(const double* actual, const double* predicted, std::size_t n)
    {
        double sum_ap = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_ap) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            // |(actual[i] - predicted[i]) / actual[i]|
            double diff_ratio = std::fabs(actual[i] - predicted[i]) / actual[i];
            sum_ap += diff_ratio;
        }

        // Return as a fraction (e.g. 0.10 = 10% MAPE).
        // If you want it as a percentage, multiply by 100.
        return sum_ap / static_cast<double>(n);
    }

    // Weighted MAPE
    static double compute(const double* actual, const double* predicted, 
                          const double* weights, std::size_t n)
    {
        double sum_ap_w = 0.0;
        double sum_w    = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_ap_w, sum_w) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double w          = weights[i];
            double diff_ratio = std::fabs(actual[i] - predicted[i]) / actual[i];
            sum_ap_w += w * diff_ratio;
            sum_w    += w;
        }

        return sum_ap_w / sum_w;
    }
};

#endif
