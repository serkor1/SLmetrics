#ifndef CLASSIFICATION_CONFUSION_MATRIX_H
#define CLASSIFICATION_CONFUSION_MATRIX_H

#include "utilities_Package.h"
#include <RcppEigen.h>
#include <cmath>
#include <span>

#ifdef _OPENMP
    #include <omp.h>
    #pragma omp declare reduction(matrixPlus : Eigen::MatrixXd : omp_out = omp_out + omp_in) \
                        initializer(omp_priv = Eigen::MatrixXd::Zero(omp_orig.rows(), omp_orig.cols()))
#endif

/**
 * @brief A class for constructing confusion matrices.
 * 
 * This class computes confusion matrices from actual and predicted labels.
 * It supports both unweighted and weighted counts and leverages OpenMP for parallel
 * computation when enabled.
 */
class ConfusionMatrixClass {
    private:
        Rcpp::IntegerVector actual_;
        Rcpp::IntegerVector predicted_;
        Rcpp::CharacterVector levels_;
        int k_;

    protected:
        /**
        * @brief Prepares the factor levels based on the attribute "levels" from the actual vector.
        */
        void prepare_levels() {
            levels_ = actual_.attr("levels");
            k_ = levels_.length() + 1;
        }

        /**
        * @brief Wraps an Eigen matrix in an Rcpp NumericMatrix and attaches proper row and column names.
        * 
        * @param matrix The Eigen matrix representing the confusion matrix.
        * @return Rcpp::NumericMatrix The wrapped confusion matrix with labels.
        */
        Rcpp::NumericMatrix finalize_matrix(const Eigen::MatrixXd& matrix) const {
    
            Rcpp::NumericMatrix output = Rcpp::wrap(matrix);
            Rcpp::rownames(output) = levels_;
            Rcpp::colnames(output) = levels_;
            output.attr("class") = "cmatrix";

            return output;
        }

        /**
        * @brief Computes the unweighted confusion matrix in a single-threaded manner.
        * 
        * @tparam MatrixType The Eigen matrix type to use (e.g. Eigen::MatrixXd).
        * @return MatrixType The computed confusion matrix block (excluding the first row and column).
        */
        template <typename MatrixType>
        [[nodiscard]] MatrixType construct_matrix_single_thread() const {
            MatrixType placeholder = MatrixType::Zero(k_, k_);
            const int n = actual_.size();
            for (int i = 0; i < n; ++i) {
                // Increment the corresponding cell (using predicted as row, actual as column)
                placeholder(predicted_[i], actual_[i]) += 1.0;
            }
            return placeholder.block(1, 1, k_ - 1, k_ - 1);
        }

        /**
        * @brief Computes the weighted confusion matrix in a single-threaded manner.
        * 
        * @tparam MatrixType The Eigen matrix type to use.
        * @param weights The vector of weights corresponding to each observation.
        * @return MatrixType The computed weighted confusion matrix block.
        */
        template <typename MatrixType>
        [[nodiscard]] MatrixType construct_matrix_single_thread(const Rcpp::NumericVector& weights) const {
            MatrixType placeholder = MatrixType::Zero(k_, k_);
            const int n = actual_.size();
            for (int i = 0; i < n; ++i) {
                placeholder(predicted_[i], actual_[i]) += weights[i];
            }
            return placeholder.block(1, 1, k_ - 1, k_ - 1);
        }

        /**
        * @brief Computes the unweighted confusion matrix using OpenMP parallelization.
        * 
        * @tparam MatrixType The Eigen matrix type to use.
        * @return MatrixType The computed confusion matrix block.
        */
        template <typename MatrixType>
        [[nodiscard]] MatrixType construct_matrix_multiple_threads() const {
            const int n = actual_.size();
            MatrixType global_matrix = MatrixType::Zero(k_, k_);
            #ifdef _OPENMP
                    #pragma omp parallel for reduction(matrixPlus:global_matrix) schedule(static)
                    for (int i = 0; i < n; ++i) {
                        global_matrix(predicted_[i], actual_[i]) += 1.0;
                    }
            #else
                    for (int i = 0; i < n; ++i) {
                        global_matrix(predicted_[i], actual_[i]) += 1.0;
                    }
            #endif
                    return global_matrix.block(1, 1, k_ - 1, k_ - 1);
        }

        /**
        * @brief Computes the weighted confusion matrix using OpenMP parallelization.
        * 
        * @tparam MatrixType The Eigen matrix type to use.
        * @param weights The vector of weights corresponding to each observation.
        * @return MatrixType The computed weighted confusion matrix block.
        */
        template <typename MatrixType>
        [[nodiscard]] MatrixType construct_matrix_multiple_threads(const Rcpp::NumericVector& weights) const {
            const int n = actual_.size();
            MatrixType global_matrix = MatrixType::Zero(k_, k_);
            #ifdef _OPENMP
                    #pragma omp parallel for reduction(matrixPlus:global_matrix) schedule(static)
                    for (int i = 0; i < n; ++i) {
                        global_matrix(predicted_[i], actual_[i]) += weights[i];
                    }
            #else
                    for (int i = 0; i < n; ++i) {
                        global_matrix(predicted_[i], actual_[i]) += weights[i];
                    }
            #endif
                    return global_matrix.block(1, 1, k_ - 1, k_ - 1);
                }

    public:
        /**
        * @brief Constructs a ConfusionMatrixClass object.
        * 
        * @param actual The vector of actual class labels.
        * @param predicted The vector of predicted class labels.
        */
        ConfusionMatrixClass(
            const Rcpp::IntegerVector& actual,
            const Rcpp::IntegerVector& predicted)
            : actual_(actual), predicted_(predicted) {
                prepare_levels();
        }

        /**
        * @brief Generates the unweighted confusion matrix.
        * 
        * @return Eigen::MatrixXd The computed confusion matrix.
        */
        [[nodiscard]] Eigen::MatrixXd input_matrix() const {
            if (getUseOpenMP()) {
                #ifdef _OPENMP
                    return construct_matrix_multiple_threads<Eigen::MatrixXd>();
                #else
                    return construct_matrix_single_thread<Eigen::MatrixXd>();
                #endif
                } else {
                    return construct_matrix_single_thread<Eigen::MatrixXd>();
                }
        }

        /**
        * @brief Constructs the unweighted confusion matrix and wraps it for R side.
        * 
        * @return Rcpp::NumericMatrix The R-compatible confusion matrix.
        */
        Rcpp::NumericMatrix construct_matrix() const {
            Eigen::MatrixXd matrix = input_matrix();
            return finalize_matrix(matrix);
        }

        /**
        * @brief Generates the weighted confusion matrix.
        * 
        * @param weights The vector of weights corresponding to each observation.
        * @return Eigen::MatrixXd The computed weighted confusion matrix.
        */
        [[nodiscard]] Eigen::MatrixXd input_matrix(const Rcpp::NumericVector& weights) const {
            if (getUseOpenMP()) {
                #ifdef _OPENMP
                    return construct_matrix_multiple_threads<Eigen::MatrixXd>(weights);
                #else
                    return construct_matrix_single_thread<Eigen::MatrixXd>(weights);
                #endif
                } else {
                    return construct_matrix_single_thread<Eigen::MatrixXd>(weights);
                }
        }

        /**
        * @brief Constructs the weighted confusion matrix and wraps it for R.
        * 
        * @param weights The vector of weights corresponding to each observation.
        * @return Rcpp::NumericMatrix The R-compatible weighted confusion matrix.
        */
        Rcpp::NumericMatrix construct_matrix(const Rcpp::NumericVector& weights) const {
            Eigen::MatrixXd matrix = input_matrix(weights);
            return finalize_matrix(matrix);
        }
};

#endif
