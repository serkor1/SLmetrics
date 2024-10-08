/*
 * This header file is for calculating
 * accucracy and balanced accuracy
 */
#include "src_Helpers.h"
#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW



/*
 * Zero One Loss; factors
 */
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted)
{



  const int n = actual.size();

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int incorrect_count = 0;
  int i = 0;
  int limit = n - (n % 4);

  // Unroll loop with quad
  // whatever it's called
  for (; i < limit; i += 4) {
    incorrect_count += (*(actual_ptr++) != *(predicted_ptr++));
    incorrect_count += (*(actual_ptr++) != *(predicted_ptr++));
    incorrect_count += (*(actual_ptr++) != *(predicted_ptr++));
    incorrect_count += (*(actual_ptr++) != *(predicted_ptr++));
  }

  for (; i < n; ++i) {
    incorrect_count += (*(actual_ptr++) != *(predicted_ptr++));
  }

  return static_cast<double> (incorrect_count) / n;


}


/*
 * Zero One Loss; cmatrix
 */
inline __attribute__((always_inline)) double _metric_(const Eigen::MatrixXi& x)
{

  // 1) extract total
  // N and True Positives Sum
  int N = x.sum();
  int TP = x.diagonal().sum();

  // 2) return value
  return static_cast<double>(N - TP) / N;

}
