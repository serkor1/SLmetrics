#ifndef REGRESSION_RELATIVEABSOLUTEERROR_H
#define REGRESSION_RELATIVEABSOLUTEERROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class RAE {
    public:
        /**
        * Unweighted RAE:
        *
        * @param actual Pointer to actual values
        * @param predicted Pointer to predicted values
        * @param n Number of elements
        *
        * @return Relative Absolute Error (unweighted)
        */
        static double compute(const double* actual, const double* predicted, std::size_t n)
        {
            // 1) Compute mean of actual
            double sum_actual = 0.0;
            for (std::size_t i = 0; i < n; ++i) {
                sum_actual += actual[i];
            }
            double mean_actual = sum_actual / static_cast<double>(n);

            // 2) Compute numerator and denominator
            double numerator = 0.0;
            double denominator = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:numerator, denominator) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double diff_pred = std::fabs(actual[i] - predicted[i]);
                double diff_mean = std::fabs(actual[i] - mean_actual);

                numerator   += diff_pred;
                denominator += diff_mean;
            }

            // 3) Return RAE
            // No check for zero denominator, per your requirement
            return numerator / denominator;
        }

        /**
        * Weighted RAE:
        *
        * @param actual Pointer to actual values
        * @param predicted Pointer to predicted values
        * @param weights Pointer to sample weights
        * @param n Number of elements
        *
        * @return Weighted Relative Absolute Error
        */
        static double compute(const double* actual, const double* predicted, 
                            const double* weights, std::size_t n)
        {
            // 1) Compute weighted mean of actual
            double weighted_sum = 0.0;
            double weight_sum   = 0.0;
            for (std::size_t i = 0; i < n; ++i) {
                weighted_sum += weights[i] * actual[i];
                weight_sum   += weights[i];
            }
            double weighted_mean_actual = weighted_sum / weight_sum;

            // 2) Compute numerator and denominator
            double numerator   = 0.0;
            double denominator = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:numerator, denominator) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double w          = weights[i];
                double diff_pred  = std::fabs(actual[i] - predicted[i]);
                double diff_mean  = std::fabs(actual[i] - weighted_mean_actual);

                numerator   += w * diff_pred;
                denominator += w * diff_mean;
            }

            // 3) Return weighted RAE
            // No check for zero denominator, per your requirement
            return numerator / denominator;
        }

    private:
        // Prevents the compiler from doing
        // bad stuff.
        RAE()  = delete;
        ~RAE() = delete;
};

#endif
