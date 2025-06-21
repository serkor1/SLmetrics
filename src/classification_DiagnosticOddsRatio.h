#ifndef CLASSIFICATION_DIAGNOSTICODDSRATIO_H
#define CLASSIFICATION_DIAGNOSTICODDSRATIO_H

#include "SLmetrics.h"

namespace metric {
    template <typename T>
    class diagnostic_odds_ratio : public classification::confusion_matrix<T> {
        public:
        // Unweighted constructor
        diagnostic_odds_ratio(const vctr_t<T>& actual, const vctr_t<T>& predicted)
            : classification::confusion_matrix<T>(actual, predicted) {}

        // Weighted constructor
        diagnostic_odds_ratio(const vctr_t<T>& actual, const vctr_t<T>& predicted, const vctr_t<double>& weights)
            : classification::confusion_matrix<T>(actual, predicted, weights) {}

        // Rcpp::NumericMatrix constructor
        diagnostic_odds_ratio(const Rcpp::NumericMatrix& x)
            : classification::confusion_matrix<T>(x) {}

        // Calculate metric
        [[nodiscard]] inline double compute() const noexcept {
            double tp = arma::accu(this->TP());
            double fn = arma::accu(this->FN());
            double fp = arma::accu(this->FP());
            double tn = arma::accu(this->TN());

            return (tp * tn) / (fp * fn);
        }
    };
}

#endif
