#ifndef REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H
#define REGRESSION_SYMMETRICMEANABSOLUTEPERCENTAGEERROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class SMAPE {
public:
    // Unweighted SMAPE
    static double compute(const double* actual, const double* predicted, std::size_t n)
    {
        double sum_smape = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_smape) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double numerator   = std::fabs(actual[i] - predicted[i]);
            double denominator = (std::fabs(actual[i]) + std::fabs(predicted[i])) / 2.0;
            double value       = numerator / denominator;
            sum_smape += value;
        }

        return sum_smape / static_cast<double>(n);
    }

    // Weighted SMAPE
    static double compute(const double* actual, const double* predicted, 
                          const double* weights, std::size_t n)
    {
        double sum_smape = 0.0;
        double sum_w     = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_smape, sum_w) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double numerator   = std::fabs(actual[i] - predicted[i]);
            double denominator = (std::fabs(actual[i]) + std::fabs(predicted[i])) / 2.0;
            double w           = weights[i];
            double value       = numerator / denominator;

            sum_smape += w * value;
            sum_w     += w;
        }

        return sum_smape / sum_w;
    }
};

#endif
