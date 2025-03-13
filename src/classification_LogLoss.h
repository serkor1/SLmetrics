#ifndef CLASSIFICATION_CROSS_ENTROPY_LOSS_H
#define CLASSIFICATION_CROSS_ENTROPY_LOSS_H

#include "utilities_Package.h"
#include <Rcpp.h>
#include <cmath>
#include <cstddef>

#ifdef _OPENMP
    #include <omp.h>
#endif

class LogLoss {
    public:
        static double compute(
            const int* actual_ptr,
            const double* response_ptr,
            std::size_t n,
            std::size_t nrows,
            bool normalize) {

            double loss = 0.0;
            #ifdef _OPENMP
                #pragma omp parallel for reduction(+:loss) if(getUseOpenMP())
            #endif
            for (std::size_t i = 0; i < n; ++i) {
                const int c = actual_ptr[i] - 1;
                const double p = response_ptr[i + static_cast<std::size_t>(c) * nrows];
                loss -= std::log(p);
            }

            if (normalize) {
                loss /= static_cast<double>(n);
            }

            return loss;
        }

        static double compute(
            const int* actual_ptr,
            const double* response_ptr,
            const double* w_ptr,
            std::size_t   n,
            std::size_t   nrows,
            bool          normalize) {

                double loss = 0.0;
                double wsum = 0.0;

                #ifdef _OPENMP
                    #pragma omp parallel for reduction(+:loss, wsum) if(getUseOpenMP())
                #endif
                for (std::size_t i = 0; i < n; ++i) {
                    const int c       = actual_ptr[i] - 1;
                    const double p    = response_ptr[i + static_cast<std::size_t>(c) * nrows];
                    const double wval = w_ptr[i];

                    loss -= wval * std::log(p);
                    wsum += wval;
                }

                // Normalize if requested
                if (normalize) {
                    loss /= wsum;
                }

                return loss;
            }

    private:
        LogLoss()  = delete;
        ~LogLoss() = delete;
};

#endif
