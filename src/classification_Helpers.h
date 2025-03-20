#ifndef CLASSIFICATION_HELPERS_H
#define CLASSIFICATION_HELPERS_H

#include <RcppEigen.h>
#include <Rcpp.h>
#include <Eigen/Dense>
#include <cmath>
#include <optional>
#include <algorithm>
#include <vector>
#include <numeric>
#include "classification_ConfusionMatrix.h"

#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

using namespace Rcpp;

class classification {
    public:

        /*
            Note to future self:
                
                1.) These are just signatures. So in essence it doesn't matter
                what you call them. The imporant thing is that they are distinguishable

                2.) All functions have the same signature
                    2.1) A Matrix (passed via helpers)
                    2.2) Booleans to determine behaviour inside
                    the respective functions. For example:
                        + boolean 1: Controls missing values
                        + boolean 2: Controls wether  micro/macro values are
                        to be rerrturned
                        + boolean k: Other behaviour that I can't think of as of now.

                It seems somewhat redundant and excessive to do it like this, but until a better
                solution is found, this is what we do.

                Warning: ALL signatures has to be used (I think)
        */

        virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix) const {
            return Rcpp::NumericVector();
        };
        
        virtual Rcpp::NumericVector compute(const Eigen::MatrixXd& matrix, bool na_rm) const {
            return Rcpp::NumericVector();
        };

        virtual ~classification() = default;
};



/*
    Micro and Macro averages with missing value handling.
    If na_rm is TRUE it divides with the available number
    of classes.

    Otherwise it divides by the original number of classes. 
    This is consistent with {Scikit}-learn.

    NOTE: This should warn or give a message when there is missing values

*/
#include <Eigen/Dense>
#include <Rcpp.h>


template <typename ReturnType = Rcpp::NumericVector>
inline __attribute__((always_inline)) ReturnType micro(
    const Eigen::ArrayXd& numerator,
    const Eigen::ArrayXd& denominator,
    bool na_rm);

template <>
inline __attribute__((always_inline)) Eigen::ArrayXd micro<Eigen::ArrayXd>(
    const Eigen::ArrayXd& numerator,
    const Eigen::ArrayXd& denominator,
    bool na_rm)
{
    double result = numerator.sum() / denominator.sum();
    return Eigen::ArrayXd::Constant(1, result);
}

template <>
inline __attribute__((always_inline)) Rcpp::NumericVector micro<Rcpp::NumericVector>(
    const Eigen::ArrayXd& numerator,
    const Eigen::ArrayXd& denominator,
    bool na_rm)
{
    double result = numerator.sum() / denominator.sum();
    return Rcpp::wrap(result);
}

template <typename ReturnType = Rcpp::NumericVector>
inline __attribute__((always_inline)) ReturnType macro(
    const Eigen::ArrayXd& numerator,
    const Eigen::ArrayXd& denominator,
    bool na_rm);


template <>
inline __attribute__((always_inline)) Eigen::ArrayXd macro<Eigen::ArrayXd>(
    const Eigen::ArrayXd& numerator,
    const Eigen::ArrayXd& denominator,
    bool na_rm)
{
    Eigen::ArrayXd z = numerator / denominator;
    double result = na_rm
                        ? z.isNaN().select(0, z).sum() / (z.isNaN() == false).count()
                        : z.isNaN().select(0, z).sum() / z.size();
    return Eigen::ArrayXd::Constant(1, result);
}

template <>
inline __attribute__((always_inline)) Rcpp::NumericVector macro<Rcpp::NumericVector>(
    const Eigen::ArrayXd& numerator,
    const Eigen::ArrayXd& denominator,
    bool na_rm)
{
    Eigen::ArrayXd z = numerator / denominator;
    double result = na_rm
                        ? z.isNaN().select(0, z).sum() / (z.isNaN() == false).count()
                        : z.isNaN().select(0, z).sum() / z.size();
    return Rcpp::wrap(result);
}


/*
  Calculating TP, FP, TN and FN from matrices.

  NOTE: The template is redundant, and will be removed at a later point.
*/

template <typename MatrixType>
inline __attribute__((always_inline)) void TP(const MatrixType& matrix, Eigen::Array<typename MatrixType::Scalar, Eigen::Dynamic, 1>& tp) {
    tp = matrix.diagonal().array();
}

template <typename MatrixType>
inline __attribute__((always_inline)) void FP(const MatrixType& matrix, Eigen::Array<typename MatrixType::Scalar, Eigen::Dynamic, 1>& fp) {
    fp = matrix.colwise().sum().array() - matrix.diagonal().array().transpose();
}

template <typename MatrixType>
inline __attribute__((always_inline)) void TN(const MatrixType& matrix, Eigen::Array<typename MatrixType::Scalar, Eigen::Dynamic, 1>& tn) {
    using Scalar = typename MatrixType::Scalar;

    const Scalar total_sum = matrix.sum();
    Eigen::Array<Scalar, Eigen::Dynamic, 1> tp = matrix.diagonal().array();
    Eigen::Array<Scalar, Eigen::Dynamic, 1> row_sums = matrix.rowwise().sum().array();
    Eigen::Array<Scalar, Eigen::Dynamic, 1> col_sums = matrix.colwise().sum().array();

    tn = Eigen::Array<Scalar, Eigen::Dynamic, 1>::Constant(matrix.rows(), total_sum) - row_sums - col_sums + tp;
}

// Generic template function to compute False Negatives (FN)
template <typename MatrixType>
inline __attribute__((always_inline)) void FN(const MatrixType& matrix, Eigen::Array<typename MatrixType::Scalar, Eigen::Dynamic, 1>& fn) {
    fn = matrix.rowwise().sum().array() - matrix.diagonal().array();
}





template <typename Function, typename MatrixType, typename... Args>
Rcpp::NumericVector prepare(
    const Function& cook,
    const MatrixType& matrix,
    const Rcpp::Nullable<bool>& micro,
    const Rcpp::CharacterVector& names,
    Args&&... args) {

    if (micro.isNull()) {
        Rcpp::NumericVector output(names.size());
        output = cook.compute(matrix, std::forward<Args>(args)...);
        output.attr("names") = names;
        return output;
    }

    Rcpp::NumericVector output(1);
    output = cook.compute(matrix, Rcpp::as<bool>(micro), std::forward<Args>(args)...);
    return output;
    
}


template <typename... Args>
Rcpp::NumericVector recipe(
    const classification& cook,
    const Rcpp::NumericMatrix& matrix,
    const std::optional<Rcpp::Nullable<bool>>& micro = std::nullopt,
    Args&&... args) {

        const Rcpp::List dimnames = matrix.attr("dimnames");
        const Rcpp::CharacterVector names = Rcpp::as<Rcpp::CharacterVector>(dimnames[1]);
        const Eigen::MatrixXd eigen_matrix = Rcpp::as<Eigen::MatrixXd>(matrix);

        return micro.has_value()
            ? prepare(cook, eigen_matrix, *micro, names, std::forward<Args>(args)...)
            : cook.compute(eigen_matrix, std::forward<Args>(args)...);
    
}

template <typename... Args>
Rcpp::NumericVector recipe(
    const classification& cook,
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const std::optional<Rcpp::NumericVector>& w = std::nullopt,
    const std::optional<Rcpp::Nullable<bool>>& micro = std::nullopt,
    Args&&... args){

        /*
            TODO: Check if its faster to have an if-else statement instead
                - The names are only used if micro != NULL, so the calculations 
                are redundant.
        */

        const Rcpp::CharacterVector names = actual.attr("levels");
        const int k = names.size();
        Eigen::MatrixXd matrix(k + 1, k + 1);

        ConfusionMatrixClass matrixConstructor(actual, predicted);
        matrix = w.has_value()
            ? matrixConstructor.input_matrix(*w)  
            : matrixConstructor.input_matrix();

        return micro.has_value()
            ? prepare(cook, matrix, *micro, names, std::forward<Args>(args)...)
            : cook.compute(matrix, std::forward<Args>(args)...);
}

#endif