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

/**
 * @class task
 *
 * @brief Ther are three types of classes
 * 1. <factor> vs <factor>
 * 2. <factor> vs <matrix>
 * 3. <matrix> vs <matrix>
 */
namespace classification {
    template <typename T>
    class task {
    protected:
        arma::Col<T> actual_;
        arma::Col<T> predicted_;
        arma::Col<double> weights_;

    public:
        task(const vctr_t<T>& actual, const vctr_t<T>& predicted) : 
            actual_(const_cast<T*>(actual.begin()), actual.size(), false, false),
            predicted_(const_cast<T*>(predicted.begin()), predicted.size(), false, false) {
                // Unweighted Logic
            }

        task(const vctr_t<T>& actual, const vctr_t<T>& predicted, const vctr_t<double>& weights) : 
            actual_(const_cast<T*>(actual.begin()), actual.size(), false, false),
            predicted_(const_cast<T*>(predicted.begin()), predicted.size(), false, false),
            weights_(const_cast<double*>(weights.begin()), weights.size(), false, false) {
                // Weighted Logic
            }
    };

};

namespace classification {
    template <typename T>
    class confusion_matrix : public task<T> {
    private:
        int k_;
        Rcpp::CharacterVector levels_;
        arma::Mat<double> confusion_matrix_;

    public:
        // Unweighted constructor
        confusion_matrix(const vctr_t<T>& actual, const vctr_t<T>& predicted)
            : task<T>(actual, predicted)
        {
            levels_ = Rcpp::as<Rcpp::RObject>(actual).attr("levels");
            k_ = levels_.size() + 1; // extra index 0 is unused

            arma::Mat<double> local_cm(k_, k_, arma::fill::zeros);
            arma::uword n = this->actual_.n_elem;
            const T* __restrict__ actual_ptr = this->actual_.memptr();
            const T* __restrict__ predicted_ptr = this->predicted_.memptr();

            #ifdef __GNUC__
                #pragma GCC ivdep
            #endif
            for (arma::uword i = 0; i < n; ++i) {
                int row = actual_ptr[i];    // 1-indexed
                int col = predicted_ptr[i];
                local_cm(row, col) += 1.0;
            }

            confusion_matrix_ = local_cm.submat(1, 1, k_ - 1, k_ - 1);
        }

        // Weighted constructor
        confusion_matrix(const vctr_t<T>& actual, const vctr_t<T>& predicted, const vctr_t<double>& weights)
            : task<T>(actual, predicted, weights)
        {
            levels_ = Rcpp::as<Rcpp::RObject>(actual).attr("levels");
            k_ = levels_.size() + 1;

            arma::Mat<double> local_cm(k_, k_, arma::fill::zeros);
            arma::uword n = this -> actual_.n_elem;
            const T* __restrict__ actual_ptr = this -> actual_.memptr();
            const T* __restrict__ predicted_ptr = this -> predicted_.memptr();
            const double* __restrict__ weights_ptr = weights.begin();

            #ifdef __GNUC__
                #pragma GCC ivdep
            #endif
            for (arma::uword i = 0; i < n; ++i) {
                int row = actual_ptr[i];
                int col = predicted_ptr[i];
                local_cm(row, col) += weights_ptr[i];
            }

            confusion_matrix_ = local_cm.submat(1, 1, k_ - 1, k_ - 1);
        }

        /* Exports:
         * The confusion matrix
         * The levels
         */
        [[nodiscard]] inline __attribute__((always_inline)) arma::Mat<double> get_matrix() const noexcept {
            return confusion_matrix_;
        }

        [[nodiscard]] inline __attribute__((always_inline)) Rcpp::CharacterVector get_levels() const noexcept {
            return levels_;
        }

        /*
         * Confusion Matrix Elements
         *
         */
        [[nodiscard]] inline __attribute__((always_inline)) arma::Col<double> TP() const noexcept {
            return confusion_matrix_.diag();
        }

        [[nodiscard]] inline __attribute__((always_inline)) arma::Col<double> FP() const noexcept {
            return arma::conv_to<arma::Col<double>>::from(arma::sum(confusion_matrix_, 0)) - confusion_matrix_.diag();
        }

        [[nodiscard]] inline __attribute__((always_inline)) arma::Col<double> FN() const noexcept {
            return arma::sum(confusion_matrix_, 1) - confusion_matrix_.diag();
        }

        [[nodiscard]] inline __attribute__((always_inline)) arma::Col<double> TN() const noexcept {
            double total_sum = arma::accu(confusion_matrix_);
            arma::Col<double> tp = confusion_matrix_.diag();
            arma::Col<double> row_sums = arma::sum(confusion_matrix_, 1);
            arma::Col<double> col_sums = arma::conv_to<arma::Col<double>>::from(arma::sum(confusion_matrix_, 0));
            return arma::Col<double>(confusion_matrix_.n_rows, arma::fill::value(total_sum)) - row_sums - col_sums + tp;
        }
    };
}

#endif