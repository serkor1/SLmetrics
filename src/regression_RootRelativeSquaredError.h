#ifndef REGRESSION_ROOTRELATIVESQUAREERROR_H
#define REGRESSION_ROOTRELATIVESQUAREERROR_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class RRSE {
    public:
        /**
        * Unweighted RRSE
        *
        * @param actual Pointer to actual values
        * @param predicted Pointer to predicted values
        * @param n Number of elements
        *
        * @return Root Relative Squared Error (unweighted)
        */
        static double compute(const double* actual, const double* predicted, std::size_t n)
        {
            // 1) Calculate mean of 'actual'
            double sum_actual = 0.0;
            for (std::size_t i = 0; i < n; ++i) {
                sum_actual += actual[i];
            }
            double mean_actual = sum_actual / static_cast<double>(n);

            // 2) Calculate numerator and denominator
            double numerator   = 0.0;
            double denominator = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:numerator, denominator) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double diff_pred = actual[i] - predicted[i];
                double diff_mean = actual[i] - mean_actual;

                numerator   += diff_pred * diff_pred;
                denominator += diff_mean * diff_mean;
            }

            // No check for zero denominator, as requested
            return std::sqrt(numerator / denominator);
        }

        /**
        * Weighted RRSE
        *
        * @param actual Pointer to actual values
        * @param predicted Pointer to predicted values
        * @param weights Pointer to observation weights
        * @param n Number of elements
        *
        * @return Weighted Root Relative Squared Error
        */
        static double compute(const double* actual, const double* predicted, const double* weights, std::size_t n)
        {
            // 1) Calculate weighted mean of 'actual'
            double weighted_sum = 0.0;
            double weight_sum   = 0.0;
            for (std::size_t i = 0; i < n; ++i) {
                weighted_sum += weights[i] * actual[i];
                weight_sum   += weights[i];
            }
            double mean_w_actual = weighted_sum / weight_sum;

            // 2) Calculate numerator and denominator
            double numerator   = 0.0;
            double denominator = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:numerator, denominator) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double w         = weights[i];
                double diff_pred = actual[i] - predicted[i];
                double diff_mean = actual[i] - mean_w_actual;

                numerator   += w * (diff_pred * diff_pred);
                denominator += w * (diff_mean * diff_mean);
            }

            // 3) Return RRSE
            return std::sqrt(numerator / denominator);
        }

    private:
        // Prevents the compiler from doing
        // bad stuff.
        RRSE()  = delete;
        ~RRSE() = delete;
};

#endif
