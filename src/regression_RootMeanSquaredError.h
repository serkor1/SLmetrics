#ifndef REGRESSION_ROOTMEANSQUAREDEROR_H
#define REGRESSION_ROOTMEANSQUAREDEROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class RMSE {
    public:
        // Unweighted RMSE
        static double compute(const double* actual, const double* predicted, std::size_t n)
        {
            double squared_sum = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:squared_sum) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double difference = actual[i] - predicted[i];
                squared_sum += difference * difference;
            }

            double mse = squared_sum / static_cast<double>(n);

            return std::sqrt(mse);
        }

        // Weighted RMSE
        static double compute(const double* actual, const double* predicted, const double* weights, std::size_t n)
        {
            double squared_sum = 0.0;
            double weighted_sum  = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:squared_sum, weighted_sum) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double difference = actual[i] - predicted[i];
                double w    = weights[i];
                squared_sum += w * difference * difference;
                weighted_sum  += w;
            }

            double mse = squared_sum / weighted_sum;
            
            return std::sqrt(mse);
        }

    private:
        // Prevents the compiler from doing
        // bad stuff.
        RMSE()  = delete;
        ~RMSE() = delete;
};

#endif
