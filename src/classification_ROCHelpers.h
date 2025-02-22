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

#endif