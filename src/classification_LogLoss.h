#ifndef CLASSIFICATION_CROSS_ENTROPY_LOSS_H
#define CLASSIFICATION_CROSS_ENTROPY_LOSS_H

#include <Rcpp.h>
#include <cmath> 

/*
    NOTE: The positive class is irrelevant
    as long as the probility matrix is correctly specified.
*/

class LogLossClass {
    private:
        bool normalize_;

    public:
        LogLossClass(bool normalize) : normalize_(normalize) {}


        double compute(const Rcpp::IntegerVector &actual, const Rcpp::NumericMatrix &response) const {
            const int n = actual.size();
            double loss = 0.0;

            
            const int *actual_ptr     = &actual[0];
            const double *response_ptr = &response(0, 0);
            const int nrows = response.nrow();

            for (int i = 0; i < n; ++i) {

                const int c = actual_ptr[i] - 1;
                const double p = response_ptr[i + c * nrows];
                loss -= std::log(p);

            }

            // If requested, average the loss
            if (normalize_) {
                loss /= n;
            }

            return loss;
        }

        // Weighted cross-entropy
        double compute(const Rcpp::IntegerVector &actual, const Rcpp::NumericMatrix &response, const Rcpp::NumericVector &w) const {
            const int n = actual.size();
            double loss = 0.0;
            double wsum = 0.0;

            const int *actual_ptr      = &actual[0];
            const double *response_ptr = &response(0, 0);
            const double *w_ptr        = &w[0];

            const int nrows = response.nrow();

            for (int i = 0; i < n; ++i) {
                const int c = actual_ptr[i] - 1;
                const double p = response_ptr[i + c * nrows];
                const double weight = w_ptr[i];

                wsum += weight;
                loss -= weight * std::log(p);
            }

            if (normalize_) {
                loss /= wsum;
            }

            return loss;
        }
};

#endif 
