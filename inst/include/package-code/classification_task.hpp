/** 
 * @file classification_task.hpp
 * @brief Declaration for classification tasks and
 * their base class `task`
 *
 */
#ifndef __classification__
#define __classification__

/// @include
#include <armadillo>
#include <Rcpp.h>
#include "templates.hpp"

/// Tasks
namespace classification {
    /**
     * @class task
     *
     * @brief Ther are three types of classes
     * 1. <factor> vs <factor>
     * 2. <factor> vs <matrix>
     * 3. <matrix> vs <matrix>
     */
     template <typename T>
     class task {
        protected:
        arma::Col<T> actual_;
        arma::Col<T> predicted_;
        arma::Col<T> weights_;
        bool micro;

        public:
        task(const vctr_t<T>& actual, const vctr_t<T> predicted, bool micro)
        : actual_(
              const_cast<T*>(actual.begin()),
              actual.size(),
              false,
              false
          )
        , predicted_(
              const_cast<T*>(predicted.begin()),
              predicted.size(),
              false,
              false
          )
        {}
     };



};

/**
 * NOTE: It may be a bad idea to have the Rcpp::NumericMatrix here
 * as it is ONLY used for returning the confusion matrrix to the R side.
 */
namespace classification {

    template<typename T>
    class confusion_matrix : public task<T> {
    private:
        // Only extract levels if available.
        Rcpp::CharacterVector levels_;
        int k_;          // k_ = number of classes + 1 (assuming 1-indexed levels)
        bool has_levels_;

    public:
        // Constructor for factor (vs factor) tasks.
        // The 'actual' and 'predicted' vectors are converted in the same minimal-overhead manner
        // as in classification::task.
        confusion_matrix(const vctr_t<T>& actual, const vctr_t<T>& predicted, bool micro = false)
        : task<T>(actual, predicted, micro), has_levels_(false) {
            // Try to extract factor levels from the original R vector.
            Rcpp::RObject levels_attr = Rcpp::as<Rcpp::RObject>(actual).attr("levels");
            if (!levels_attr.isNULL()) {
                levels_ = Rcpp::as<Rcpp::CharacterVector>(levels_attr);
                k_ = levels_.size() + 1; // extra row/col for 1-indexing
                has_levels_ = true;
            } else {
                // If no levels attribute, determine k_ as (max value + 1) assuming 1-indexing.
                T max_val = this->actual_[0];
                for (arma::uword i = 1; i < this->actual_.n_elem; i++) {
                    if (this->actual_[i] > max_val) max_val = this->actual_[i];
                }
                k_ = max_val + 1;
            }
        }

        // Compute the unweighted confusion matrix.
        // Returns an Armadillo matrix built in a single pass over the data.
        arma::Mat<double> compute_matrix() const {
            arma::Mat<double> mat(k_, k_, arma::fill::zeros);
            arma::uword n = this->actual_.n_elem;
            const T* actual_ptr    = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            for (arma::uword i = 0; i < n; ++i) {
                int row = actual_ptr[i];    // assuming 1-indexed
                int col = predicted_ptr[i];
                mat(row, col) += 1.0;
            }
            if (has_levels_) {
                // Return only the submatrix corresponding to the levels.
                return mat.submat(1, 1, k_ - 1, k_ - 1);
            } else {
                return mat;
            }
        }

        // Compute the weighted confusion matrix.
        arma::Mat<double> compute_matrix(const Rcpp::NumericVector& weights) const {
            arma::Mat<double> mat(k_, k_, arma::fill::zeros);
            arma::uword n = this->actual_.n_elem;
            const T* actual_ptr    = this->actual_.memptr();
            const T* predicted_ptr = this->predicted_.memptr();
            const double* weights_ptr = weights.begin();
            for (arma::uword i = 0; i < n; ++i) {
                int row = actual_ptr[i];
                int col = predicted_ptr[i];
                mat(row, col) += weights_ptr[i];
            }
            if (has_levels_) {
                return mat.submat(1, 1, k_ - 1, k_ - 1);
            } else {
                return mat;
            }
        }

        // Wrap the Armadillo matrix as an Rcpp::NumericMatrix with dimnames (if levels exist)
        Rcpp::NumericMatrix construct_matrix() const {
            arma::Mat<double> armaMat = compute_matrix();
            Rcpp::NumericMatrix rMat(armaMat.n_rows, armaMat.n_cols);
            for (arma::uword i = 0; i < armaMat.n_rows; ++i) {
                for (arma::uword j = 0; j < armaMat.n_cols; ++j) {
                    rMat(i, j) = armaMat(i, j);
                }
            }
            if (has_levels_) {
                rMat.attr("dimnames") = Rcpp::List::create(levels_, levels_);
                rMat.attr("class") = "cmatrix";
            }
            return rMat;
        }

        // Weighted version.
        Rcpp::NumericMatrix construct_matrix(const Rcpp::NumericVector& weights) const {
            arma::Mat<double> armaMat = compute_matrix(weights);
            Rcpp::NumericMatrix rMat(armaMat.n_rows, armaMat.n_cols);
            for (arma::uword i = 0; i < armaMat.n_rows; ++i) {
                for (arma::uword j = 0; j < armaMat.n_cols; ++j) {
                    rMat(i, j) = armaMat(i, j);
                }
            }
            if (has_levels_) {
                rMat.attr("dimnames") = Rcpp::List::create(levels_, levels_);
                rMat.attr("class") = "cmatrix";
            }
            return rMat;
        }
    };

}



#endif