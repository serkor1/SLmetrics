/** 
 * @file classification_task.hpp
 * @brief Declaration for classification tasks and
 * their base class `task`
 *
 */
#ifndef __classification__
#define __classification__

/// @include
#include <RcppArmadillo.h>
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

         // Default constructor for use with precomputed confusion matrices.
        task() : actual_(), predicted_(), weights_() {}

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

        confusion_matrix(const Rcpp::NumericMatrix& x)
            : task<T>() {
                // Extract levels from the dimnames attribute (assumes row names represent levels).
                Rcpp::List dn = x.attr("dimnames");
                if(dn.size() > 0) {
                    levels_ = Rcpp::as<Rcpp::CharacterVector>(dn[0]);
                }

                // Get dimensions (assumes x is k x k).
                int nrows = x.nrow();
                int ncols = x.ncol();
                k_ = nrows; 

                confusion_matrix_.set_size(nrows, ncols);

                const double* x_ptr = x.begin();
                double* cm_ptr = confusion_matrix_.memptr();
                int total = nrows * ncols;
                for (int i = 0; i < total; ++i) {
                    cm_ptr[i] = x_ptr[i];
                }
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

/**
* @namespace classification::metric_tools
* @brief This nested namespace class is meant for
* for confusion matrix based metrics.
* 
*/
namespace classification {
    namespace metric_tools {
        // Enumeration for aggregation modes
        enum class aggregation_level {
            CLASS_WISE = 0,
            MICRO = 1,
            MACRO = 2
        };

        /**
         * @class base_metric
         * This class handles the returned values
         * from individual header files. Currently supports
         * 0: Class-wise
         * 1: Micro-averages
         * 2: Macro-averages
         */
        template <typename T>
        class base_metric : public classification::confusion_matrix<T> {
        protected:
            aggregation_level mode_;
            arma::Col<double> tp_;
            arma::Col<double> fp_;
            arma::Col<double> fn_;
            arma::Col<double> tn_;
            bool na_rm_;

            virtual arma::Col<double> calculate_class_values() const = 0;
            
            // Micro-averaging: aggregate numerator and denominator
            template<typename F>
            double calculate_micro(F metric_func) const {
                // For micro averaging we sum all TP, FP, FN, TN first
                double sum_tp = arma::accu(tp_);
                double sum_fp = arma::accu(fp_);
                double sum_fn = arma::accu(fn_);
                double sum_tn = arma::accu(tn_);
                
                return metric_func(sum_tp, sum_fp, sum_fn, sum_tn);
            }
            
            // // Macro-averaging: calculate metric for each class then average
            // double calculate_macro() const {
            //     arma::Col<double> class_values = calculate_class_values();
                
            //     // Replace NaN values with 0 for averaging
            //     for (arma::uword i = 0; i < class_values.n_elem; ++i) {
            //         if (!std::isfinite(class_values[i])) {
            //             class_values[i] = 0.0;
            //         }
            //     }
                
            //     return arma::mean(class_values);
            // }

            // Macro-averaging: calculate metric for each class then average.
            double calculate_macro() const {
                arma::Col<double> class_values = calculate_class_values();
                if (na_rm_) {
                    double sum = 0.0;
                    int count  = 0;

                    for (arma::uword i = 0; i < class_values.n_elem; ++i) {
                        if (std::isfinite(class_values[i])) {
                            sum += class_values[i];
                            count++;
                        }
                    }

                    return count > 0 ? sum / count : NAN;
                } else {

                    for (arma::uword i = 0; i < class_values.n_elem; ++i) {
                        if (!std::isfinite(class_values[i])) {
                            class_values[i] = 0.0;
                        }
                    }

                    return arma::mean(class_values);
                }
            }
            
        public:
            // Unweighted constructor
            base_metric(const vctr_t<T>& actual, const vctr_t<T>& predicted, aggregation_level mode, bool na_rm = true)
                : classification::confusion_matrix<T>(actual, predicted), mode_(mode), na_rm_(na_rm) {
                    tp_ = this -> TP();
                    fp_ = this -> FP();
                    fn_ = this -> FN();
                    tn_ = this -> TN();
            }
            
            // Weighted constructor
            base_metric(const vctr_t<T>& actual, const vctr_t<T>& predicted, 
                        const vctr_t<double>& weights, aggregation_level mode, bool na_rm = true)
                : classification::confusion_matrix<T>(actual, predicted, weights), mode_(mode), na_rm_(na_rm) {
                    tp_ = this -> TP();
                    fp_ = this -> FP();
                    fn_ = this -> FN();
                    tn_ = this -> TN();
            }

            // Matrix constructor (Numeric Matrix)
            base_metric(const Rcpp::NumericMatrix& x, aggregation_level mode, bool na_rm = true)
                : classification::confusion_matrix<T>(x), mode_(mode), na_rm_(na_rm) {
                    tp_ = this -> TP();
                    fp_ = this -> FP();
                    fn_ = this -> FN();
                    tn_ = this -> TN();
            }
            
            // This is where the action 
            // happens
            Rcpp::NumericVector compute() const {
                switch (mode_) {
                    case aggregation_level::MICRO: {
                        return Rcpp::NumericVector::create(calculate_micro_value());
                    }
                    case aggregation_level::MACRO: {
                        return Rcpp::NumericVector::create(calculate_macro());
                    }
                    case aggregation_level::CLASS_WISE:
                    default: {
                        arma::Col<double> class_values = calculate_class_values();
                        Rcpp::NumericVector result(class_values.n_elem);
                        
                        for (arma::uword i = 0; i < class_values.n_elem; ++i) {
                            result[i] = class_values[i];
                        }

                        result.names() = this->get_levels();
                        
                        return result;
                    }
                }
            }

            virtual double calculate_micro_value() const = 0;
        };
    }
}

#endif