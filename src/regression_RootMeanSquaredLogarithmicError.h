#ifndef REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H
#define REGRESSION_ROOTMEANSQUAREDLOGARITHMICERROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class RMSLE {
public:
    // Unweighted RMSLE
    static double compute(const double* actual, const double* predicted, std::size_t n)
    {
        double sum_log_diff_sq = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_log_diff_sq) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double log_a = std::log(actual[i] + 1.0);
            double log_p = std::log(predicted[i] + 1.0);
            double diff  = log_a - log_p;
            sum_log_diff_sq += diff * diff;
        }

        double mean_log_diff_sq = sum_log_diff_sq / static_cast<double>(n);
        return std::sqrt(mean_log_diff_sq);
    }

    // Weighted RMSLE
    static double compute(const double* actual, const double* predicted, 
                          const double* weights, std::size_t n)
    {
        double sum_log_diff_sq = 0.0;
        double sum_w           = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_log_diff_sq, sum_w) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double w     = weights[i];
            double log_a = std::log(actual[i] + 1.0);
            double log_p = std::log(predicted[i] + 1.0);
            double diff  = log_a - log_p;
            sum_log_diff_sq += w * diff * diff;
            sum_w           += w;
        }

        double mean_log_diff_sq = sum_log_diff_sq / sum_w;
        return std::sqrt(mean_log_diff_sq);
    }
};

#endif
