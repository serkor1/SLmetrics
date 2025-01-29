#ifndef REGRESSION_COEFFICIENTOFDETERMINATION_H
#define REGRESSION_COEFFICIENTOFDETERMINATION_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class CoefficientOfDetermination {
    public:
        /**
        * Compute unweighted R-squared.
        *
        * @param actual    Pointer to actual values
        * @param predicted Pointer to predicted values
        * @param n         Number of observations
        * @param k         Number of predictors (default=0 => plain R^2)
        * 
        * @return The R^2 or adjusted R^2.
        */
        static double compute(const double* actual,
                            const double* predicted,
                            std::size_t n,
                            double k)
        {
            // 1) Compute mean of actual
            double sumA = 0.0;
            for (std::size_t i = 0; i < n; ++i) {
                sumA += actual[i];
            }
            double meanA = sumA / static_cast<double>(n);

            // 2) Compute SSE and SST
            double SSE = 0.0;
            double SST = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:SSE, SST) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double diffAm = (actual[i] - meanA);
                double diffAp = (actual[i] - predicted[i]);

                SST += diffAm * diffAm;
                SSE += diffAp * diffAp;
            }

            // 3) Unadjusted R^2 = 1 - SSE/SST
            //    Adjusted => multiply (SSE/SST) by factor = ((n - 1) / (n - (k + 1))).
            //    So final = 1 - (SSE/SST) * factor
            double factor   = (static_cast<double>(n) - 1.0) / (static_cast<double>(n) - (k + 1.0));
            double r2_value = 1.0 - ((SSE / SST) * factor);

            return r2_value;
        }

        /**
        * Compute weighted R-squared.
        *
        * Weighted definitions:
        *   Weighted SSE = sum( w_i * (a_i - p_i)^2 )
        *   Weighted mean of actual = sum( w_i*a_i ) / sum( w_i )
        *   Weighted SST = sum( w_i * (a_i - wMean)^2 )
        *
        * Then apply the same adjustment factor for k.
        *
        * @param actual    Pointer to actual values
        * @param predicted Pointer to predicted values
        * @param weights   Pointer to weights
        * @param n         Number of observations
        * @param k         Number of predictors (default=0 => plain weighted R^2)
        *
        * @return The weighted R^2 or adjusted weighted R^2.
        */
        static double compute(const double* actual,
                            const double* predicted,
                            const double* weights,
                            std::size_t n,
                            double k)
        {
            // 1) Compute weighted sums, SSE
            double sumW   = 0.0;
            double sumWA  = 0.0;
            double SSE    = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:sumW, sumWA, SSE) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double w   = weights[i];
                double a   = actual[i];
                double p   = predicted[i];

                sumW   += w;
                sumWA  += (w * a);

                double resid = a - p;
                SSE    += w * resid * resid;
            }

            // Weighted mean of actual
            double wMean = sumWA / sumW;

            // 2) Weighted SST
            double SST = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:SST) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double w   = weights[i];
                double diff = actual[i] - wMean;
                SST += w * diff * diff;
            }

            // 3) Weighted R^2 or adjusted R^2
            double factor   = (static_cast<double>(n) - 1.0) / (static_cast<double>(n) - (k + 1.0));
            double r2_value = 1.0 - ((SSE / SST) * factor);

            return r2_value;
        }
};

#endif // REGRESSION_COEFFICIENTOFDETERMINATION_H
