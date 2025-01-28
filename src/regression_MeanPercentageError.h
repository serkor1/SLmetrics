#ifndef REGRESSION_MEANPERCENTAGEERROR_H
#define REGRESSION_MEANPERCENTAGEERROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class MPE {
public:
    // Unweighted MPE
    static double compute(const double* actual, const double* predicted, std::size_t n)
    {
        double sum_perc = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_perc) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double diff  = actual[i] - predicted[i];
            double ratio = diff / actual[i];
            sum_perc += ratio;
        }

        return sum_perc / static_cast<double>(n);
    }

    // Weighted MPE
    static double compute(const double* actual, const double* predicted, 
                          const double* weights, std::size_t n)
    {
        double sum_perc = 0.0;
        double sum_w    = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sum_perc, sum_w) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double w     = weights[i];
            double diff  = actual[i] - predicted[i];
            double ratio = diff / actual[i];
            sum_perc += w * ratio;
            sum_w    += w;
        }

        return sum_perc / sum_w;
    }
};

#endif
