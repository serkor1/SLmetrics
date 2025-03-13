#ifndef COUNT_POISSONLOGLOSS_H
#define COUNT_POISSONLOGLOSS_H

#include "utilities_Package.h"
#include <Rcpp.h>
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class PoissonLogLoss {
    public:
        static double compute(
            const int* actual_ptr,
            const double* response_ptr,
            std::size_t n,
            bool normalize)
        {

            const double eps = 1e-15;
            double loss = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:loss) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                const double pred = std::max(response_ptr[i], eps);
                const int obs = actual_ptr[i];
                
                loss += std::lgamma(obs + 1.0) + pred - obs * std::log(pred);
            }

            if (normalize && n > 0) {
                loss /= static_cast<double>(n);
            }

            return loss;
        }

        static double compute(
            const int* actual_ptr,
            const double* response_ptr,
            const double* w_ptr,
            std::size_t n,
            bool normalize)
        {
            const double eps = 1e-15;
            double loss = 0.0;
            double wsum = 0.0;

            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:loss, wsum) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                const double wval = w_ptr[i];
                const double pred = std::max(response_ptr[i], eps);
                const int obs     = actual_ptr[i];

                loss += wval * (std::lgamma(obs + 1.0) + pred - obs * std::log(pred));
                wsum += wval;
            }

            if (normalize && wsum > 0.0) {
                loss /= wsum;
            }

            return loss;
        }

    private:
        PoissonLogLoss()  = delete;
        ~PoissonLogLoss() = delete;
};

#endif
