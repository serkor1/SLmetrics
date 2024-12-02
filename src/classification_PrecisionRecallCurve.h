#include "src_Helpers.h"
#include <Rcpp.h>
#include <algorithm>
#include <vector>
#include <numeric>


inline __attribute__((always_inline)) Rcpp::DataFrame _metric_(const Rcpp::IntegerVector &actual, const Rcpp::NumericVector &response, Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue)
{
  // 1) Get the nested list structure from the _temporary_ function
  Rcpp::List nested_data = _temporary_(actual, response, thresholds);

  // 2) Determine the number of thresholds based on input or response length
  R_xlen_t num_combinations = nested_data.size();
  R_xlen_t num_thresholds = thresholds.isNotNull()
    ? Rcpp::as<Rcpp::NumericVector>(thresholds).size()
      : response.size();

  // 3) Pre-allocate memory based on the expected size
  R_xlen_t total_size = num_combinations * num_thresholds;
  std::vector<double> final_thresholds(total_size);
  std::vector<int> final_levels(total_size);
  Rcpp::CharacterVector final_labels(total_size);
  std::vector<double> final_precision(total_size), final_recall(total_size);

  R_xlen_t insert_index = 0;

  // 4) Loop through nested data elements in chunks of 4 for optimized processing
  R_xlen_t combo_index = 0;
  for (; combo_index + 3 < num_combinations; combo_index += 4) {
    // 5) Process four groups at a time for better memory access and loop unrolling
    for (int group_offset = 0; group_offset < 4; ++group_offset) {
      const Rcpp::List &current_group = nested_data[combo_index + group_offset];

      // 6) Extract relevant vectors from the current group
      const Rcpp::NumericVector &thresholds = current_group["threshold"];
      const Rcpp::NumericVector &tp = current_group["tp"];
      const Rcpp::NumericVector &fp = current_group["fp"];
      int level = Rcpp::as<int>(current_group["level"]);
      std::string label = Rcpp::as<std::string>(current_group["label"]);

      // 7) Get pointers to tp, fp, and threshold vectors for efficient access
      const double *tp_ptr = tp.begin();
      const double *fp_ptr = fp.begin();
      const double *threshold_ptr = thresholds.begin();

      // 8) Determine group size and normalization factors
      R_xlen_t group_size = thresholds.size();
      double max_tp = tp_ptr[group_size - 1]; // Maximum true positives for recall calculation

      // 9) Process group elements in blocks of 4 for efficiency
      R_xlen_t i = 0;
      for (; i + 3 < group_size; i += 4) {
        for (int j = 0; j < 4; ++j) {
          double tp_val = tp_ptr[i + j];
          double fp_val = fp_ptr[i + j];

          // Compute precision and recall with safeguards against division by zero
          double precision = (tp_val + fp_val == 0) ? 0.0 : tp_val / (tp_val + fp_val);
          double recall = (max_tp == 0) ? 0.0 : tp_val / max_tp;

          // Directly assign to pre-allocated vectors
          final_thresholds[insert_index] = threshold_ptr[i + j];
          final_levels[insert_index] = level;
          final_labels[insert_index] = label;
          final_precision[insert_index] = precision;
          final_recall[insert_index] = recall;
          insert_index++;
        }
      }

      // 10) Process remaining elements if not divisible by 4
      for (; i < group_size; ++i) {
        double tp_val = tp_ptr[i];
        double fp_val = fp_ptr[i];

        double precision = (tp_val + fp_val == 0) ? 0.0 : tp_val / (tp_val + fp_val);
        double recall = (max_tp == 0) ? 0.0 : tp_val / max_tp;

        final_thresholds[insert_index] = threshold_ptr[i];
        final_levels[insert_index] = level;
        final_labels[insert_index] = label;
        final_precision[insert_index] = precision;
        final_recall[insert_index] = recall;
        insert_index++;
      }
    }
  }

  // 11) Process any remaining groups not divisible by 4
  for (R_xlen_t remaining_index = combo_index; remaining_index < num_combinations; ++remaining_index) {
    const Rcpp::List &current_group = nested_data[remaining_index];

    // 12) Extract relevant vectors from the current group
    const Rcpp::NumericVector &thresholds = current_group["threshold"];
    const Rcpp::NumericVector &tp = current_group["tp"];
    const Rcpp::NumericVector &fp = current_group["fp"];
    int level = Rcpp::as<int>(current_group["level"]);
    std::string label = Rcpp::as<std::string>(current_group["label"]);

    // 13) Get pointers to tp, fp, and threshold vectors for efficient access
    const double *tp_ptr = tp.begin();
    const double *fp_ptr = fp.begin();
    const double *threshold_ptr = thresholds.begin();

    // 14) Determine group size and normalization factors
    R_xlen_t group_size = thresholds.size();
    double max_tp = tp_ptr[group_size - 1]; // Maximum true positives for recall calculation

    // 15) Process all elements in this group
    for (R_xlen_t i = 0; i < group_size; ++i) {
      double tp_val = tp_ptr[i];
      double fp_val = fp_ptr[i];

      double precision = (tp_val + fp_val == 0) ? 0.0 : tp_val / (tp_val + fp_val);
      double recall = (max_tp == 0) ? 0.0 : tp_val / max_tp;

      final_thresholds[insert_index] = threshold_ptr[i];
      final_levels[insert_index] = level;
      final_labels[insert_index] = label;
      final_precision[insert_index] = precision;
      final_recall[insert_index] = recall;
      insert_index++;
    }
  }

  // 16) Adjust the size of final vectors based on actual data inserted
  final_thresholds.resize(insert_index);
  final_levels.resize(insert_index);
  final_labels = Rcpp::CharacterVector(final_labels.begin(), final_labels.begin() + insert_index);
  final_precision.resize(insert_index);
  final_recall.resize(insert_index);

  // Create and return the final result DataFrame
  Rcpp::DataFrame final_result = Rcpp::DataFrame::create(
    Rcpp::Named("threshold") = final_thresholds,
    Rcpp::Named("level") = final_levels,
    Rcpp::Named("label") = final_labels,
    Rcpp::Named("precision") = final_precision,
    Rcpp::Named("recall") = final_recall
  );


  // Add "prROC" class to the DataFrame
  final_result.attr("class") = Rcpp::CharacterVector::create("prROC", "data.frame");
  return final_result;

}
