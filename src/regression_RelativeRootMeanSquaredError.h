#ifndef REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H
#define REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H

#include "SLmetrics.h"
#include "regression_RootMeanSquaredError.h"
#include <Rcpp.h>
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>
#include <algorithm>
#include <vector>

#ifdef _OPENMP
  #include <omp.h>
#endif

namespace metric {

    // Unweighted RRMSE: derived from regression::task.
    // normalization_:
    //   0 -> normalize by mean of actual values.
    //   1 -> normalize by range of actual values.
    //   2 -> normalize by IQR of actual values.
    //   default -> no normalization (norm factor = 1.0)
    template <typename T>
    class RRMSE : public regression::task<T> {
        int normalization_;
    public:
        using regression::task<T>::task;
        
        RRMSE(const vctr_t<T>& actual,
              const vctr_t<T>& predicted,
              int normalization)
          : regression::task<T>(actual, predicted),
            normalization_(normalization) {}

        inline T compute() const override {
            const arma::uword n = this->actual_.n_elem;
            // Compute RMSE in one pass
            T rmse = std::sqrt(arma::accu(arma::square( this -> actual_ - this-> predicted_))/n);
            T normFactor = 1.0;
            switch(normalization_) {
                case 0: // Normalize by mean
                    normFactor = arma::accu(this->actual_) / n;
                    break;
                case 1: // Normalize by range
                    normFactor = statistic::range<T>::unweighted(this->actual_);
                    break;
                case 2: // Normalize by IQR
                    normFactor = statistic::IQR<T>::unweighted(this->actual_);
                    break;
                default:
                    normFactor = 1.0;
                    break;
            }
            return rmse / normFactor;
        }
    };

    // Weighted RRMSE: derived from regression::task.
    // normalization_:
    //   0 -> normalize by weighted mean.
    //   1 -> normalize by range (unweighted range).
    //   2 -> normalize by weighted IQR.
    //   default -> norm factor = 1.0.
    template <typename T>
    class weighted_RRMSE : public regression::task<T> {
        int normalization_;
    public:
        using regression::task<T>::task;
        
        weighted_RRMSE(const vctr_t<T>& actual,
                       const vctr_t<T>& predicted,
                       const vctr_t<T>& weights,
                       int normalization)
          : regression::task<T>(actual, predicted, weights),
            normalization_(normalization) {}

        inline T compute() const override {
            const arma::uword n    = this -> actual_.n_elem;
            const T* actual_ptr    = this -> actual_.memptr();
            const T* predicted_ptr = this -> predicted_.memptr();
            const T* weights_ptr   = this -> weights_.memptr();
            
            T weighted_sum = 0;
            T sum_weights  = 0;
            
            for (arma::uword i = 0; i < n; ++i) {
                T diff = actual_ptr[i] - predicted_ptr[i];
                weighted_sum += weights_ptr[i] * diff * diff;
                sum_weights  += weights_ptr[i];
            }
            
            T rmse = std::sqrt(weighted_sum / sum_weights);
            T normFactor = 1.0;
            switch(normalization_) {
                case 0: // Normalize by weighted mean
                    normFactor = arma::accu( this->weights_ % this->actual_ ) / sum_weights;
                    break;
                case 1: // Normalize by range (unweighted)
                    normFactor = statistic::range<T>::weighted(this->actual_, this -> weights_);
                    break;
                case 2: // Normalize by weighted IQR
                    normFactor = statistic::IQR<T>::weighted(this->actual_, this->weights_);
                    break;
                default:
                    normFactor = 1.0;
                    break;
            }
            return rmse / normFactor;
        }
    };

} // namespace metric


#endif
