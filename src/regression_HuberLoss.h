#ifndef REGRESSION_HUBERLOSS_H
#define REGRESSION_HUBERLOSS_H

#include "utilities_Package.h"
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class HuberLoss {
    public:
        /**
        * Compute the Huber Loss (unweighted).
        *
        * @param actual Pointer to ground-truth values
        * @param predicted Pointer to predicted values
        * @param n Number of elements
        * @param delta Threshold parameter of the Huber loss
        *
        * @return Average Huber loss (scalar)
        */

        static double compute(const double* actual, const double* predicted, std::size_t n, double delta)
        {
            double loss_sum = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:loss_sum) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double diff = actual[i] - predicted[i];
                double abs_diff = std::fabs(diff);

                if (abs_diff <= delta) {
                    // Quadratic region
                    loss_sum += 0.5 * diff * diff;
                } else {
                    // Linear region
                    loss_sum += delta * (abs_diff - 0.5 * delta);
                }
            }

            return loss_sum / static_cast<double>(n);
        }

        /**
        * Compute the Huber Loss (weighted).
        *
        * @param actual Pointer to ground-truth values
        * @param predicted Pointer to predicted values
        * @param weights Pointer to sample weights
        * @param n Number of elements
        * @param delta Threshold parameter of the Huber loss
        *
        * @return Weighted average Huber loss (scalar)
        */
        static double compute(const double* actual, const double* predicted, const double* weights, std::size_t n, double delta)
        {
            double loss_sum = 0.0;
            double weight_sum = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:loss_sum, weight_sum) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                double w = weights[i];
                double diff = actual[i] - predicted[i];
                double abs_diff = std::fabs(diff);

                if (abs_diff <= delta) {
                    // Quadratic region
                    loss_sum += w * (0.5 * diff * diff);
                } else {
                    // Linear region
                    loss_sum += w * (delta * (abs_diff - 0.5 * delta));
                }

                weight_sum += w;
            }

            return loss_sum / weight_sum;
        }

    private:
        // Prevents the compiler from doing
        // bad stuff.
        HuberLoss()  = delete;
        ~HuberLoss() = delete;
};

#endif
