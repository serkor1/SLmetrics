#ifndef REGRESSION_CONCORDANCE_CORRELATION_COEFFICIENT_H
#define REGRESSION_CONCORDANCE_CORRELATION_COEFFICIENT_H

#include "SLmetrics.h"
#include "utilities_COV.h" 
#include <cstddef>
#include <cmath>

namespace metric {

  template <typename T>
  class CCC : public regression::task<T> {
  private:
      bool correction_;
      
  public:
      CCC(const vctr_t<T>& actual, const vctr_t<T>& predicted, bool correction)
          : regression::task<T>(actual, predicted), correction_(correction) {}

      inline T compute() const override {
          arma::uword n = this -> actual_.n_elem;
          if(n < 2) return 0;

          const T* ptr_actual = this -> actual_.memptr();
          const T* ptr_predicted = this -> predicted_.memptr();

          T sum_x  = 0, sum_y  = 0;
          T sum_xx = 0, sum_yy = 0, sum_xy = 0;
          for(arma::uword i = 0; i < n; ++i) {
              T x = ptr_actual[i], y = ptr_predicted[i];
              sum_x  += x;
              sum_y  += y;
              sum_xx += x * x;
              sum_yy += y * y;
              sum_xy += x * y;
          }

          T mean_x = sum_x / n;
          T mean_y = sum_y / n;

          T sxx = (sum_xx - n * mean_x * mean_x) / (n - 1);
          T syy = (sum_yy - n * mean_y * mean_y) / (n - 1);
          T sxy = (sum_xy - n * mean_x * mean_y) / (n - 1);

          if(correction_) {
              T factor = static_cast<T>(n - 1) / static_cast<T>(n);
              sxx *= factor;
              syy *= factor;
              sxy *= factor;
          }

          T diff = mean_x - mean_y;
          return (2 * sxy) / (sxx + syy + diff * diff);
      }
  };

  template <typename T>
  class weighted_CCC : public regression::task<T> {
  private:
      bool correction_;
      
  public:
      weighted_CCC(const vctr_t<T>& actual,
                   const vctr_t<T>& predicted,
                   const vctr_t<T>& weights,
                   bool correction)
          : regression::task<T>(actual, predicted, weights), correction_(correction) {}

      inline T compute() const override {
          arma::uword n = this -> actual_.n_elem;

          const T* ptr_actual = this -> actual_.memptr();
          const T* ptr_predicted = this -> predicted_.memptr();
          const T* ptrW = this -> weights_.memptr();

          // Accumulate weighted sums in one pass.
          T sum_w   = 0, sum_wx  = 0, sum_wy  = 0;
          T sum_wxx = 0, sum_wyy = 0, sum_wxy = 0, sum_w2 = 0;
          for(arma::uword i = 0; i < n; ++i) {
              T w = ptrW[i];
              T x = ptr_actual[i];
              T y = ptr_predicted[i];
              sum_w   += w;
              sum_wx  += w * x;
              sum_wy  += w * y;
              sum_wxx += w * x * x;
              sum_wyy += w * y * y;
              sum_wxy += w * x * y;
              sum_w2  += w * w;
          }

          T mean_x = sum_wx / sum_w;
          T mean_y = sum_wy / sum_w;

          T D = sum_w - (sum_w2 / sum_w);
          T sxx = (sum_wxx - sum_w * mean_x * mean_x) / D;
          T syy = (sum_wyy - sum_w * mean_y * mean_y) / D;
          T sxy = (sum_wxy - sum_w * mean_x * mean_y) / D;


          if(correction_) {
              T factor = (sum_w - 1) / sum_w;
              sxx *= factor;
              syy *= factor;
              sxy *= factor;
          }

          T diff = mean_x - mean_y;
          return (2 * sxy) / (sxx + syy + diff * diff);
      }
  };

} // namespace metric

#endif
