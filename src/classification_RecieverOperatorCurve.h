#include "classification_ROCHelpers.h"

class ROCCalculator : public MetricsCalculator {
public:
    using MetricsCalculator::MetricsCalculator;

    Rcpp::DataFrame calculate() override {
        int total_points = (n_ + 1) * num_classes_;
        Rcpp::NumericVector tpr_all(total_points);
        Rcpp::NumericVector fpr_all(total_points);
        Rcpp::NumericVector thresholds_all(total_points);
        Rcpp::CharacterVector labels_all(total_points);
        Rcpp::IntegerVector levels_all(total_points);

        int idx = 0;

        for (int c = 0; c < num_classes_; ++c) {
            const int class_label = c + 1;
            double positives = 0.0, negatives = 0.0;

            
            for (int i = 0; i < n_; ++i) {
                if (actual_[indices_[i]] == class_label) {
                    positives += weights_[indices_[i]];
                } else {
                    negatives += weights_[indices_[i]];
                }
            }

            double tp = 0.0, fp = 0.0;
            for (int i = 0; i <= n_; ++i) {
                thresholds_all[idx] = (i == 0) ? R_PosInf : response_[indices_[i - 1]];
                if (i > 0) {
                    if (actual_[indices_[i - 1]] == class_label) {
                        tp += weights_[indices_[i - 1]];
                    } else {
                        fp += weights_[indices_[i - 1]];
                    }
                }

                tpr_all[idx] = (positives > 0) ? (tp / positives) : 0.0;
                fpr_all[idx] = (negatives > 0) ? (fp / negatives) : 0.0;
                labels_all[idx] = levels_[c];
                levels_all[idx] = class_label;
                ++idx;
            }
        }

        Rcpp::DataFrame output = Rcpp::DataFrame::create(
            Rcpp::Named("threshold") = thresholds_all,
            Rcpp::Named("level") = levels_all,
            Rcpp::Named("label") = labels_all,
            Rcpp::Named("fpr") = fpr_all,
            Rcpp::Named("tpr") = tpr_all
        );

        // Add "prROC" class to the DataFrame
        output.attr("class") = Rcpp::CharacterVector::create("ROC", "data.frame");

        return output;
    }
};