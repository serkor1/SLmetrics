#ifndef CLASSIFICATION_CONFUSION_MATRIX_H
#define CLASSIFICATION_CONFUSION_MATRIX_H

#include "utilities_Package.h"
#include <RcppEigen.h>
#include <cmath>

#ifdef _OPENMP
    #include <omp.h>
#endif

#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

class ConfusionMatrixClass {
    private:
        Rcpp::IntegerVector actual_;
        Rcpp::IntegerVector predicted_;
        Rcpp::CharacterVector levels_;
        int k_;

    protected:
        void prepareLevels() {
            levels_ = actual_.attr("levels");
            k_ = levels_.length() + 1;
        }

        Rcpp::NumericMatrix finalizeMatrix(const Eigen::MatrixXd& matrix) const {
            Rcpp::NumericMatrix output = Rcpp::wrap(matrix);
            Rcpp::rownames(output) = levels_;
            Rcpp::colnames(output) = levels_;
            output.attr("class")   = "cmatrix";
            return output;
        }

        template <typename MatrixType>
        MatrixType computeMatrixSingleThreaded() const {
            MatrixType placeholder = MatrixType::Zero(k_, k_).eval();
            const int n = actual_.size();

            const int* actual_ptr = actual_.begin();
            const int* predicted_ptr = predicted_.begin();
            auto matrix_ptr = placeholder.data();

            // Unrolled loop for efficiency
            int i = 0;
            for (; i <= n - 6; i += 6) {
                ++matrix_ptr[predicted_ptr[i]     * k_ + actual_ptr[i]    ];
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
        MatrixType computeMatrixSingleThreaded(const Rcpp::NumericVector& weights) const {
            MatrixType placeholder = MatrixType::Zero(k_, k_).eval();
            const int n = actual_.size();

            const int* actual_ptr = actual_.begin();
            const int* predicted_ptr = predicted_.begin();
            const double* weights_ptr = weights.begin();
            auto matrix_ptr = placeholder.data();

            int i = 0;
            for (; i <= n - 6; i += 6) {
                matrix_ptr[predicted_ptr[i]     * k_ + actual_ptr[i]    ] += weights_ptr[i];
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

        template <typename MatrixType>
        MatrixType computeMatrixParallel() const {
            const int n = actual_.size();
            const int* actual_ptr = actual_.begin();
            const int* predicted_ptr = predicted_.begin();

            MatrixType globalMatrix = MatrixType::Zero(k_, k_);

            #ifdef _OPENMP
            #pragma omp parallel if(getUseOpenMP()) 
            {
                MatrixType localMatrix = MatrixType::Zero(k_, k_);
                auto local_ptr = localMatrix.data();

                #pragma omp for schedule(static)
                for (int i = 0; i < n; i++) {
                    ++local_ptr[predicted_ptr[i] * k_ + actual_ptr[i]];
                }

                // Reduction
                #pragma omp critical
                {
                    globalMatrix += localMatrix;
                }
            }
            #else
            
            globalMatrix = computeMatrixSingleThreaded<MatrixType>();
            #endif

            return globalMatrix.block(1, 1, k_ - 1, k_ - 1);
        }

        template <typename MatrixType>
        MatrixType computeMatrixParallel(const Rcpp::NumericVector& weights) const {
            const int n = actual_.size();
            const int* actual_ptr = actual_.begin();
            const int* predicted_ptr = predicted_.begin();
            const double* weights_ptr = weights.begin();

            MatrixType globalMatrix = MatrixType::Zero(k_, k_);

            #ifdef _OPENMP
            #pragma omp parallel if(getUseOpenMP())
            {
                MatrixType localMatrix = MatrixType::Zero(k_, k_);
                auto local_ptr = localMatrix.data();

                #pragma omp for schedule(static)
                for (int i = 0; i < n; i++) {
                    local_ptr[predicted_ptr[i] * k_ + actual_ptr[i]] += weights_ptr[i];
                }

                #pragma omp critical
                {
                    globalMatrix += localMatrix;
                }
            }
            #else
            globalMatrix = computeMatrixSingleThreaded<MatrixType>(weights);
            #endif

            return globalMatrix.block(1, 1, k_ - 1, k_ - 1);
        }

    public:

        ConfusionMatrixClass(const Rcpp::IntegerVector& actual,
                            const Rcpp::IntegerVector& predicted)
            : actual_(actual), predicted_(predicted)
        {
            prepareLevels();
        }

        Eigen::MatrixXd InputMatrix() const {
            if (getUseOpenMP()) {
            #ifdef _OPENMP
                return computeMatrixParallel<Eigen::MatrixXd>();
            #else
                return computeMatrixSingleThreaded<Eigen::MatrixXd>();
            #endif
            } else {
                return computeMatrixSingleThreaded<Eigen::MatrixXd>();
            }
        }

        Rcpp::NumericMatrix constructMatrix() const {
            Eigen::MatrixXd matrix = InputMatrix();
            return finalizeMatrix(matrix);
        }

        //------------------------------------------------------------------------------
        // Weighted
        //------------------------------------------------------------------------------
        Eigen::MatrixXd InputMatrix(const Rcpp::NumericVector& weights) const {
            if (getUseOpenMP()) {
            #ifdef _OPENMP
                return computeMatrixParallel<Eigen::MatrixXd>(weights);
            #else
                return computeMatrixSingleThreaded<Eigen::MatrixXd>(weights);
            #endif
            } else {
                return computeMatrixSingleThreaded<Eigen::MatrixXd>(weights);
            }
        }

        Rcpp::NumericMatrix constructMatrix(const Rcpp::NumericVector& weights) const {
            Eigen::MatrixXd matrix = InputMatrix(weights);
            return finalizeMatrix(matrix);
        }
};

#endif
