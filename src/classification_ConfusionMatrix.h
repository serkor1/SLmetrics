#ifndef CLASSIFICATION_CONFUSION_MATRIX_H
#define CLASSIFICATION_CONFUSION_MATRIX_H

#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class ConfusionMatrixClass {
    protected:
        Rcpp::IntegerVector actual_;
        Rcpp::IntegerVector predicted_;
        Rcpp::CharacterVector levels_;
        int k_;

        void prepareLevels() {
            levels_ = actual_.attr("levels");
            k_      = levels_.length() + 1;
        }

        Rcpp::NumericMatrix finalizeMatrix(const Eigen::MatrixXd& matrix) const {
            Rcpp::NumericMatrix output = Rcpp::wrap(matrix);
            Rcpp::rownames(output) = levels_;
            Rcpp::colnames(output) = levels_;
            output.attr("class")   = "cmatrix";
            return output;
        }

        
        template <typename MatrixType>
        MatrixType computeMatrix() const {
            MatrixType placeholder = MatrixType::Zero(k_, k_).eval();
            const int n = actual_.size();

            const int* actual_ptr = actual_.begin();
            const int* predicted_ptr = predicted_.begin();
            auto matrix_ptr = placeholder.data();

            int i = 0;
            for (; i <= n - 6; i += 6) {
                ++matrix_ptr[predicted_ptr[i] * k_ + actual_ptr[i]];
                ++matrix_ptr[predicted_ptr[i + 1] * k_ + actual_ptr[i + 1]];
                ++matrix_ptr[predicted_ptr[i + 2] * k_ + actual_ptr[i + 2]];
                ++matrix_ptr[predicted_ptr[i + 3] * k_ + actual_ptr[i + 3]];
                ++matrix_ptr[predicted_ptr[i + 4] * k_ + actual_ptr[i + 4]];
                ++matrix_ptr[predicted_ptr[i + 5] * k_ + actual_ptr[i + 5]];
            }

            for (; i < n; ++i) {
                ++matrix_ptr[predicted_ptr[i] * k_ + actual_ptr[i]];
            }

            return placeholder.block(1, 1, k_ - 1, k_ - 1);
        }

        template <typename MatrixType>
        MatrixType computeMatrix(const Rcpp::NumericVector& weights) const {
            MatrixType placeholder = MatrixType::Zero(k_, k_).eval();
            const int n = actual_.size();

            const int* actual_ptr = actual_.begin();
            const int* predicted_ptr = predicted_.begin();
            const double* weights_ptr = weights.begin();
            auto matrix_ptr = placeholder.data();

            int i = 0;
            for (; i <= n - 6; i += 6) {
                matrix_ptr[predicted_ptr[i] * k_ + actual_ptr[i]] += weights_ptr[i];
                matrix_ptr[predicted_ptr[i + 1] * k_ + actual_ptr[i + 1]] += weights_ptr[i + 1];
                matrix_ptr[predicted_ptr[i + 2] * k_ + actual_ptr[i + 2]] += weights_ptr[i + 2];
                matrix_ptr[predicted_ptr[i + 3] * k_ + actual_ptr[i + 3]] += weights_ptr[i + 3];
                matrix_ptr[predicted_ptr[i + 4] * k_ + actual_ptr[i + 4]] += weights_ptr[i + 4];
                matrix_ptr[predicted_ptr[i + 5] * k_ + actual_ptr[i + 5]] += weights_ptr[i + 5];
            }

            for (; i < n; ++i) {
                matrix_ptr[predicted_ptr[i] * k_ + actual_ptr[i]] += weights_ptr[i];
            }

            return placeholder.block(1, 1, k_ - 1, k_ - 1);
        }

    public:

        ConfusionMatrixClass(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
            : actual_(actual), predicted_(predicted) {
            prepareLevels();}

        /*
            InputMatrix: An Eigen::MatrixXd passed internally to other classification functions
            constructMatrix: A Rcpp::NumericMatrix passed directly to R
        */

        // Unweighted Confusion Matrices
        Eigen::MatrixXd InputMatrix() const {
            return computeMatrix<Eigen::MatrixXd>();}

        Rcpp::NumericMatrix constructMatrix() const {
            Eigen::MatrixXd matrix = computeMatrix<Eigen::MatrixXd>();
            return finalizeMatrix(matrix);}

        // Weighted Confusion Matrices
        Eigen::MatrixXd InputMatrix(const Rcpp::NumericVector& weights) const {
            return computeMatrix<Eigen::MatrixXd>(weights);}
        
        Rcpp::NumericMatrix constructMatrix(const Rcpp::NumericVector& weights) const {
            Eigen::MatrixXd matrix = computeMatrix<Eigen::MatrixXd>(weights);
            return finalizeMatrix(matrix);}
};

#endif