#ifndef OVERALL_HELPERS_H
#define OVERALL_HELPERS_H
/*
 * A bunch of helpers for calculating
 * various metrics, and simplifying
 * operations where deemed necessary.
 *
 *
 * NOTE: Be aware of implicit casting of vectors vs matrices
 * ie. VectorXi col_sum = matrix.sum() does not have the same
 * dimensions as matrix.sum() which by definition is a matrix!
 *
 * R Studio crashes if the dimensions doesn't align with matrix-algebra! :-(
 */

#include <Rcpp.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace Rcpp;

class MetricsCalculator {
    protected:
        const Rcpp::IntegerVector& actual_;
        const Rcpp::NumericVector& response_;
        const Rcpp::NumericVector weights_; // Weights for instances
        const Rcpp::CharacterVector levels_;
        const int num_classes_;
        const int n_;
        std::vector<int> indices_;
        Rcpp::NumericVector thresholds_;

    public:
        MetricsCalculator(const Rcpp::IntegerVector& actual, const Rcpp::NumericVector& response, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue)
            : actual_(actual),
            response_(response),
            weights_(Rcpp::NumericVector(actual.size(), 1.0)), // Default weights as 1.0
            levels_(actual.attr("levels")),
            num_classes_(levels_.size()),
            n_(actual.size()) {
            initialize(thresholds);
        }

        MetricsCalculator(const Rcpp::IntegerVector& actual, const Rcpp::NumericVector& response, const Rcpp::NumericVector& weights, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue)
            : actual_(actual),
            response_(response),
            weights_(weights),
            levels_(actual.attr("levels")),
            num_classes_(levels_.size()),
            n_(actual.size()) {
            initialize(thresholds);
        }

        virtual Rcpp::DataFrame calculate() = 0;

    protected:
        void initialize(Rcpp::Nullable<Rcpp::NumericVector> thresholds) {
            indices_.resize(n_);
            std::iota(indices_.begin(), indices_.end(), 0);
            std::sort(indices_.begin(), indices_.end(), [&](const int& i, const int& j) {
                return response_[i] > response_[j];
            });

            if (thresholds.isNotNull()) {
                thresholds_ = Rcpp::NumericVector(thresholds);
                thresholds_.push_front(R_PosInf);
            } else {
                thresholds_ = Rcpp::NumericVector(n_ + 1);
                thresholds_[0] = R_PosInf;
                for (int i = 0; i < n_; ++i) {
                    thresholds_[i + 1] = response_[indices_[i]];
                }
            }
        }
};


inline __attribute__((always_inline)) double calcArea(const Rcpp::NumericVector& y, const Rcpp::NumericVector& x, const int& method = 1) {

  double output = 0.0;
  std::size_t N = y.size();

  if (N < 2) {
    Rcpp::stop("Vectors y and x must have at least two elements.");
  }

  std::vector<std::size_t> idx(N);
  std::size_t i = 0;

  for (; i + 3 < N; i += 4) {
    idx[i]     = i;
    idx[i + 1] = i + 1;
    idx[i + 2] = i + 2;
    idx[i + 3] = i + 3;
  }

  for (; i < N; ++i) {
    idx[i] = i;
  }

  std::sort(idx.begin(), idx.end(), [&x](std::size_t i1, std::size_t i2) {
    return x[i1] < x[i2];
  });

  switch (method) {

  // Default: Trapezoid
  default:

    const double* x_ptr = &x[0];
    const double* y_ptr = &y[0];

    i = 1;
    for (; i + 3 < N; i += 4) {
      // First trapezoid
      double width1  = x_ptr[idx[i]] - x_ptr[idx[i - 1]];
      double height1 = (y_ptr[idx[i]] + y_ptr[idx[i - 1]]) * 0.5;
      output += width1 * height1;

      // Second trapezoid
      double width2  = x_ptr[idx[i + 1]] - x_ptr[idx[i]];
      double height2 = (y_ptr[idx[i + 1]] + y_ptr[idx[i]]) * 0.5;
      output += width2 * height2;

      // Third trapezoid
      double width3  = x_ptr[idx[i + 2]] - x_ptr[idx[i + 1]];
      double height3 = (y_ptr[idx[i + 2]] + y_ptr[idx[i + 1]]) * 0.5;
      output += width3 * height3;

      // Fourth trapezoid
      double width4  = x_ptr[idx[i + 3]] - x_ptr[idx[i + 2]];
      double height4 = (y_ptr[idx[i + 3]] + y_ptr[idx[i + 2]]) * 0.5;
      output += width4 * height4;
    }

    // Handle any remaining elements if N is not a multiple of 4
    for (; i < N; ++i) {
      double width  = x_ptr[idx[i]] - x_ptr[idx[i - 1]];
      double height = (y_ptr[idx[i]] + y_ptr[idx[i - 1]]) * 0.5;
      output += width * height;
    }

    break;
  }

  return output;
}

#endif