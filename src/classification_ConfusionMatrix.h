#ifndef CLASSIFICATION_CONFUSIONMATRIX_H
#define CLASSIFICATION_CONFUSIONMATRIX_H

#include "SLmetrics.h"


namespace metric {
    template <typename T>
    class confusion_matrix {
    private:
        classification::confusion_matrix<T> internal_cm_;

    public:
        // Unweighted constructor
        confusion_matrix(const vctr_t<T>& actual, const vctr_t<T>& predicted)
            : internal_cm_(actual, predicted) {}

        // Weighted constructor
        confusion_matrix(const vctr_t<T>& actual, const vctr_t<T>& predicted, const vctr_t<double>& weights)
            : internal_cm_(actual, predicted, weights) {}

        // Convert Arma::Mat to
        // Rcpp::NumericMatrix
        Rcpp::NumericMatrix as_Rcpp() {

            arma::Mat<double> mat = internal_cm_.get_matrix();
            Rcpp::NumericMatrix Rcpp_matrix(mat.n_rows, mat.n_cols);

            const double* __restrict__ mat_ptr = mat.memptr();
            double* __restrict__ Rcpp_matrix_ptr = Rcpp_matrix.begin();
            
            const arma::uword total = mat.n_rows * mat.n_cols;
            

            for (arma::uword i = 0; i < total; ++i) {
                Rcpp_matrix_ptr[i] = mat_ptr[i];
            }
            
            const Rcpp::RObject& levels = internal_cm_.get_levels();
            Rcpp_matrix.attr("dimnames") = Rcpp::List::create(levels, levels);
            Rcpp_matrix.attr("class") = "cmatrix";

            return Rcpp_matrix;
        }
    };
} // Namespace end

#endif // CLASSIFICATION_CONFUSIONMATRIX_H