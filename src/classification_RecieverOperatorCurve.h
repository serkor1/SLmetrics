#include "classification_ROCHelpers.h"
#include <Rcpp.h>
#include <algorithm>
#include <vector>
#include <numeric>


inline __attribute__((always_inline)) Rcpp::DataFrame _metric_(const Rcpp::IntegerVector &actual, const Rcpp::NumericVector &response, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue)
{

  // Get the nested list structure from the _temporary_ function
  Rcpp::List nested_data = _temporary_(actual, response, thresholds);

  // Determine the number of thresholds
  R_xlen_t num_combinations = nested_data.size();
  R_xlen_t num_thresholds = 0;

  if (thresholds.isNotNull()) {
    num_thresholds = Rcpp::as<Rcpp::NumericVector>(thresholds).size();
  } else {
    num_thresholds = response.size();
  }

  // Pre-allocate memory based on known size
  R_xlen_t total_size = num_combinations * num_thresholds;
  std::vector<double> final_thresholds(total_size);
  std::vector<int> final_levels(total_size);
  Rcpp::CharacterVector final_labels(total_size);
  std::vector<double> final_fpr(total_size), final_tpr(total_size);

  R_xlen_t list_index = 0, insert_index = 0;

  // Loop through elements of the nested list in chunks of 4
  for (; list_index + 3 < num_combinations; list_index += 4) {
    for (int group_index = 0; group_index < 4; ++group_index) {
      const Rcpp::List &current_group = nested_data[list_index + group_index];

      // Extract relevant vectors from the current group
      const Rcpp::NumericVector &thresholds = current_group["threshold"];
      const Rcpp::NumericVector &tp = current_group["tp"];
      const Rcpp::NumericVector &fp = current_group["fp"];
      int level = Rcpp::as<int>(current_group["level"]);
      std::string label = Rcpp::as<std::string>(current_group["label"]);

      // Get pointers to tp, fp, and threshold vectors for efficient access
      const double *tp_ptr = tp.begin();
      const double *fp_ptr = fp.begin();
      const double *threshold_ptr = thresholds.begin();

      R_xlen_t group_size = thresholds.size();

      // Compute the maximum TP and FP for normalization
      double max_tp = *std::max_element(tp.begin(), tp.end());
      double max_fp = *std::max_element(fp.begin(), fp.end());

      // Process elements in the group
      R_xlen_t j = 0;
      for (; j + 3 < group_size; j += 4) {
        // Unroll the loop to process 4 elements at a time
        for (int k = 0; k < 4; ++k) {
          double tp_val = tp_ptr[j + k];
          double fp_val = fp_ptr[j + k];

          // Compute TPR and FPR (use safeguards to prevent division by zero)
          double tpr = (max_tp == 0) ? 0.0 : tp_val / max_tp;
          double fpr = (max_fp == 0) ? 0.0 : fp_val / max_fp;

          // Directly assign to pre-allocated vectors
          final_thresholds[insert_index] = threshold_ptr[j + k];
          final_levels[insert_index] = level;
          final_labels[insert_index] = label;
          final_fpr[insert_index] = fpr;
          final_tpr[insert_index] = tpr;
          insert_index++;
        }
      }

      // Process remaining elements if not divisible by 4
      for (; j < group_size; ++j) {
        double tp_val = tp_ptr[j];
        double fp_val = fp_ptr[j];

        // Compute TPR and FPR (use safeguards to prevent division by zero)
        double tpr = (max_tp == 0) ? 0.0 : tp_val / max_tp;
        double fpr = (max_fp == 0) ? 0.0 : fp_val / max_fp;

        // Directly assign to pre-allocated vectors
        final_thresholds[insert_index] = threshold_ptr[j];
        final_levels[insert_index] = level;
        final_labels[insert_index] = label;
        final_fpr[insert_index] = fpr;
        final_tpr[insert_index] = tpr;
        insert_index++;
      }
    }
  }

  // Process any remaining elements in nested_data not divisible by 4
  for (; list_index < num_combinations; ++list_index) {
    const Rcpp::List &current_group = nested_data[list_index];

    // Extract relevant vectors from the current group
    const Rcpp::NumericVector &thresholds = current_group["threshold"];
    const Rcpp::NumericVector &tp = current_group["tp"];
    const Rcpp::NumericVector &fp = current_group["fp"];
    int level = Rcpp::as<int>(current_group["level"]);
    std::string label = Rcpp::as<std::string>(current_group["label"]);

    // Get pointers to tp, fp, and threshold vectors for efficient access
    const double *tp_ptr = tp.begin();
    const double *fp_ptr = fp.begin();
    const double *threshold_ptr = thresholds.begin();

    R_xlen_t group_size = thresholds.size();

    // Compute the maximum TP and FP for normalization
    double max_tp = *std::max_element(tp.begin(), tp.end());
    double max_fp = *std::max_element(fp.begin(), fp.end());

    // Process elements in the group
    for (R_xlen_t j = 0; j < group_size; ++j) {
      double tp_val = tp_ptr[j];
      double fp_val = fp_ptr[j];

      // Compute TPR and FPR (use safeguards to prevent division by zero)
      double tpr = (max_tp == 0) ? 0.0 : tp_val / max_tp;
      double fpr = (max_fp == 0) ? 0.0 : fp_val / max_fp;

      // Directly assign to pre-allocated vectors
      final_thresholds[insert_index] = threshold_ptr[j];
      final_levels[insert_index] = level;
      final_labels[insert_index] = label;
      final_fpr[insert_index] = fpr;
      final_tpr[insert_index] = tpr;
      insert_index++;
    }
  }

  // Adjust the final vector size if fewer entries were inserted than initially allocated
  final_thresholds.resize(insert_index);
  final_levels.resize(insert_index);
  final_labels = Rcpp::CharacterVector(final_labels.begin(), final_labels.begin() + insert_index);
  final_fpr.resize(insert_index);
  final_tpr.resize(insert_index);

  // Create and return the final result DataFrame
  Rcpp::DataFrame final_result = Rcpp::DataFrame::create(
    Rcpp::Named("threshold") = final_thresholds,
    Rcpp::Named("level") = final_levels,
    Rcpp::Named("label") = final_labels,
    Rcpp::Named("fpr") = final_fpr,
    Rcpp::Named("tpr") = final_tpr
  );

  // Add "ROC" class to the DataFrame
  final_result.attr("class") = Rcpp::CharacterVector::create("ROC", "data.frame");

  return final_result;

}
