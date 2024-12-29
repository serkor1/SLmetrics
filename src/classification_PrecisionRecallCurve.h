#include "classification_ROCHelpers.h"
#include <Rcpp.h>
#include <algorithm>
#include <vector>
#include <numeric>

class PRCalculator : public MetricsCalculator {
public:
    using MetricsCalculator::MetricsCalculator;

    Rcpp::DataFrame calculate() override {
        int total_points = (n_ + 1) * num_classes_;
        Rcpp::NumericVector precision_all(total_points);
        Rcpp::NumericVector recall_all(total_points);
        Rcpp::NumericVector thresholds_all(total_points);
        Rcpp::CharacterVector labels_all(total_points);
        Rcpp::IntegerVector levels_all(total_points);

        int idx = 0;

        for (int c = 0; c < num_classes_; ++c) {
            const int class_label = c + 1;
            double positives = 0.0;

            
            for (int i = 0; i < n_; ++i) {
                if (actual_[indices_[i]] == class_label) {
                    positives += weights_[indices_[i]];
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

                precision_all[idx] = (tp + fp > 0) ? (tp / (tp + fp)) : 0.0;
                recall_all[idx] = (positives > 0) ? (tp / positives) : 0.0;

                labels_all[idx] = levels_[c];
                levels_all[idx] = class_label;
                ++idx;
            }
        }

        return Rcpp::DataFrame::create(
            Rcpp::Named("threshold") = thresholds_all,
            Rcpp::Named("level") = levels_all,
            Rcpp::Named("label") = labels_all,
            Rcpp::Named("precision") = precision_all,
            Rcpp::Named("recall") = recall_all
        );
    }
};