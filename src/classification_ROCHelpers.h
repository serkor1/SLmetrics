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

#include <RcppEigen.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <numeric>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

using namespace Rcpp;

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

//' Placeholder
//'
//'
//' @description
//'
//'
//' @returns
//' A [list] with stuff.
inline __attribute__((always_inline)) Rcpp::List _temporary_(const Rcpp::IntegerVector &actual, const Rcpp::NumericVector &response, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue)
{
 /*
  * This function calculates true positives and false positives
  * across multiple thresholds for receiver operating characteristic
  * curve calculations.
  */

 size_t n = actual.size();

 // Extract the levels and their labels from the actual factor vector
 Rcpp::CharacterVector level_labels = actual.attr("levels");
 Rcpp::IntegerVector levels = Rcpp::seq(1, level_labels.size());
 size_t num_levels = levels.size();

 // Prepare to sort by response in descending order and keep the indices
 std::vector<size_t> order(n);
 std::iota(order.begin(), order.end(), 0);
 std::sort(order.begin(), order.end(), [&](size_t i, size_t j) { return response[i] > response[j]; });

 // Reorder actual and response based on the sorted indices
 Rcpp::IntegerVector sorted_actual(n);
 Rcpp::NumericVector sorted_response(n);

 int* sorted_actual_ptr = sorted_actual.begin();
 double* sorted_response_ptr = sorted_response.begin();

 for (size_t i = 0; i < n; ++i) {
   size_t idx = order[i];
   sorted_actual_ptr[i] = actual[idx];
   sorted_response_ptr[i] = response[idx];
 }

 // Handle the provided thresholds or find unique thresholds from the sorted responses
 Rcpp::NumericVector custom_thresholds;

 if (thresholds.isNotNull()) {
   // Use provided thresholds and sort them in descending order
   custom_thresholds = Rcpp::NumericVector(thresholds);
   std::sort(custom_thresholds.begin(), custom_thresholds.end(), std::greater<double>());
 } else {
   // Identify unique thresholds from the sorted responses
   std::vector<double> unique_thresholds;
   unique_thresholds.push_back(sorted_response_ptr[0]);
   for (size_t i = 1; i < n; ++i) {
     if (sorted_response_ptr[i] != sorted_response_ptr[i - 1]) {
       unique_thresholds.push_back(sorted_response_ptr[i]);
     }
   }
   custom_thresholds = Rcpp::wrap(unique_thresholds);
 }

 size_t num_thresholds = custom_thresholds.size();

 // Create a list to store results for each unique level-label combination
 Rcpp::List result(num_levels);

 // Loop through each level and pre-allocate vectors based on the number of thresholds
 for (size_t lvl = 0; lvl < num_levels; ++lvl) {
   int current_level = levels[lvl];
   double cumulative_tp = 0.0;
   double cumulative_fp = 0.0;

   // Pre-allocate vectors for tp, fp, and combined_threshold based on num_thresholds
   Rcpp::NumericVector tp(num_thresholds);
   Rcpp::NumericVector fp(num_thresholds);
   Rcpp::NumericVector combined_threshold(num_thresholds);
   Rcpp::CharacterVector combined_label(num_thresholds, level_labels[lvl]);

   double* tp_ptr = tp.begin();
   double* fp_ptr = fp.begin();
   double* combined_threshold_ptr = combined_threshold.begin();
   const double* custom_thresholds_ptr = custom_thresholds.begin();

   size_t i = 0;
   size_t j = 0;

   // Loop through sorted responses to calculate TP and FP for each threshold
   while (j < num_thresholds) {
     while (i < n && sorted_response_ptr[i] >= custom_thresholds_ptr[j]) {
       if (sorted_actual_ptr[i] == current_level) {
         cumulative_tp += 1.0;
       } else {
         cumulative_fp += 1.0;
       }
       ++i;
     }

     // Store cumulative TP and FP at the current threshold
     tp_ptr[j] = cumulative_tp;
     fp_ptr[j] = cumulative_fp;
     combined_threshold_ptr[j] = custom_thresholds_ptr[j];
     ++j;
   }

   // Create a nested list for this level-label pair
   Rcpp::List level_list = Rcpp::List::create(
     Rcpp::Named("threshold") = combined_threshold,
     Rcpp::Named("tp") = tp,
     Rcpp::Named("fp") = fp,
     Rcpp::Named("level") = current_level,
     Rcpp::Named("label") = Rcpp::as<std::string>(level_labels[lvl])
   );

   result[lvl] = level_list;
 }

 return result;
}

#endif