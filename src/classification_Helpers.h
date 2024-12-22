#include <RcppEigen.h>
#include <Rcpp.h>
#include "classification_Utils.h"
#include <Eigen/Dense>
#include <cmath>
#include <algorithm>
#include <vector>
#include <numeric>
#include <optional>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW

using namespace Rcpp;

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

template <typename EigenType>
inline __attribute__((always_inline)) EigenType micro(
    const EigenType& numerator,
    const EigenType& denominator,
    bool na_rm)
{
    double result = numerator.sum() / denominator.sum();
    return EigenType::Constant(1, result); // Use EigenType to determine both argument and return type
}

template <typename EigenType>
inline __attribute__((always_inline)) EigenType macro(
    const EigenType& numerator,
    const EigenType& denominator,
    bool na_rm)
{
    EigenType z = numerator / denominator;
    double result = na_rm
                        ? z.isNaN().select(0, z).sum() / (z.isNaN() == false).count()
                        : z.isNaN().select(0, z).sum() / z.size();

    return EigenType::Constant(1, result); // Use EigenType to determine both argument and return type
}
*/





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


/*
Confusion Matrix:

    ***ARGS***
    `actual`: IntegerVector 
    `predicted`: IntegerVector
    `k`: int (NOTE: has to be passed as k + 1)
    `weights`: Nullable NumericVector

    1. This template returns a Eigen::MatrixX<T> in weighted or unweighted form
    depending on the argument `weight`

    The tests shows that for 1e7 observations it is still faster than the original implementation
    up to v0.1-1; it runs 5.77 ms on average, while the original are 5.89 ms on average. This might be a chance
    finding, but it seems they are equivalent in terms of speed, efficiency and memory handling.

    For lower values this function is not faster. In fact its 8 times slower than the original implementation
    this is due to the overhead cost of the if-statements in relation to weighted
    and unweighted version.

    It does not handle missing values, and will not handle missing values as this is inefficient. More on this
    will come later.

*/
template <typename MatrixType>
inline __attribute__((always_inline)) MatrixType confusionMatrix(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const int& k, 
    const Rcpp::Nullable<Rcpp::NumericVector>& weights = R_NilValue) {

        // 1) general setup of the function
        // 1.1) initialize a k x k placeholder matrix
        MatrixType placeholder = MatrixType::Zero(k, k).eval();

        // 1.2) determine the size of
        // the actual vector - used for the loop
        const int n = actual.size();

        // 1.3) initialize the pointers
        // for efficient loops
        const int* actual_ptr = actual.begin();
        const int* predicted_ptr = predicted.begin();
        const double* weights_ptr = weights.isNotNull() ? Rcpp::NumericVector(weights).begin() : nullptr;
        auto matrix_ptr = placeholder.data();
        
        // 2) populate the matrix
        // according to location conditional
        // on wether weights are passed
        int i = 0;
        if (weights_ptr) {

            for (; i <= n - 6; i += 6) {
                matrix_ptr[predicted_ptr[i] * k + actual_ptr[i]] += weights_ptr[i];
                matrix_ptr[predicted_ptr[i + 1] * k + actual_ptr[i + 1]] += weights_ptr[i + 1];
                matrix_ptr[predicted_ptr[i + 2] * k + actual_ptr[i + 2]] += weights_ptr[i + 2];
                matrix_ptr[predicted_ptr[i + 3] * k + actual_ptr[i + 3]] += weights_ptr[i + 3];
                matrix_ptr[predicted_ptr[i + 4] * k + actual_ptr[i + 4]] += weights_ptr[i + 4];
                matrix_ptr[predicted_ptr[i + 5] * k + actual_ptr[i + 5]] += weights_ptr[i + 5];
            }

            for (; i < n; ++i) {
                matrix_ptr[predicted_ptr[i] * k + actual_ptr[i]] += weights_ptr[i];
            }

        } else {

            for (; i <= n - 6; i += 6) {
                ++matrix_ptr[predicted_ptr[i] * k + actual_ptr[i]];
                ++matrix_ptr[predicted_ptr[i + 1] * k + actual_ptr[i + 1]];
                ++matrix_ptr[predicted_ptr[i + 2] * k + actual_ptr[i + 2]];
                ++matrix_ptr[predicted_ptr[i + 3] * k + actual_ptr[i + 3]];
                ++matrix_ptr[predicted_ptr[i + 4] * k + actual_ptr[i + 4]];
                ++matrix_ptr[predicted_ptr[i + 5] * k + actual_ptr[i + 5]];
            }

            for (; i < n; ++i) {
                ++matrix_ptr[predicted_ptr[i] * k + actual_ptr[i]];
            }
        }
        

        // 3) return the matrix
        // but leave index 
        // (NOTE: Cpp is 0-indexed, and <factor> can't include zero)
        return placeholder.block(1, 1, k - 1, k - 1);
}




/*
    Note to future self:

        - This implementation relies on variadic templates (https://www.geeksforgeeks.org/variadic-function-templates-c/)
        it basically works like ellipsis (...) in R. 

            + Why? The main issue is that for a vast majority of the classification metric we would need additional arguments
            that extends beyond the micro, na_rm arguments. And a further benefit is that we can add additional aguments
            to the functions without having to recode the whole code-base.

        - The classification_base functions works as follows
            
            + (actual, predicted), (actual, predicted, micro), (actual, predicted, w), (actual, predicted, w, micro),  (matrix) and (matrix, micro)
                - So it's one overloaded function per function specification. 

            NOTE: Working OOP here might be a huge benefit. But this won't be implement before anytime soon. The base package has
            to be done first.

*/

// matrix templates //

// 1) matrix template
// without micro-agument
template <typename... Args>
Rcpp::NumericVector classification_base(
    const Rcpp::NumericMatrix& matrix,
    const classification& foo,
    Args&&... args)
{
    // 0) Convert matrix to Eigen format
    Eigen::MatrixXd eigen_matrix = Rcpp::as<Eigen::MatrixXd>(matrix);

    // 1) Forward the additional arguments to foo.compute
    return foo.compute(eigen_matrix, std::forward<Args>(args)...);
}

// 2) matrix template
// with micro argument
template <typename... Args>
Rcpp::NumericVector classification_base(
    const Rcpp::NumericMatrix& matrix,
    const classification& foo,
    Rcpp::Nullable<bool> micro,
    Args&&... args)
{
    // 0) Extract dimension names
    const Rcpp::List& dimnames = matrix.attr("dimnames");
    const Rcpp::CharacterVector& names = dimnames[1];
    const int k = names.size();

    // 1) Convert matrix to Eigen format
    Eigen::MatrixXd eigen_matrix = Rcpp::as<Eigen::MatrixXd>(matrix);

    // 2) Handle micro or macro aggregation
    if (micro.isNull()) {
        Rcpp::NumericVector output(k);
        output = foo.compute(eigen_matrix, std::forward<Args>(args)...);
        output.attr("names") = names; // Assign column names as names
        return output;
    }

    Rcpp::NumericVector output(1);
    output = foo.compute(eigen_matrix, Rcpp::as<bool>(micro), std::forward<Args>(args)...);
    return output;
}

// IntegerVectorr templates //

// 1) IntegerVector template without
// micro-argument
template <typename... Args>
Rcpp::NumericVector classification_base(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const classification& foo,
    Args&&... args)
{
    // 0) Extract the number of classes
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length();

    // 1) Construct the confusion matrix
    Eigen::MatrixXd matrix = confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1);

    // 2) Forward the additional arguments to foo.compute
    return foo.compute(matrix, std::forward<Args>(args)...);
}

// 2) IntegerVector template without
// micro-argument with weights
template <typename... Args>
Rcpp::NumericVector classification_base(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const Rcpp::NumericVector& w,
    const classification& foo,
    Args&&... args)
{
    // 0) Extract the number of classes
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length();

    // 1) Construct the confusion matrix with weights
    Eigen::MatrixXd matrix = confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1, w);

    // 2) Forward the additional arguments to foo.compute
    return foo.compute(matrix, std::forward<Args>(args)...);
}

// 3) IntegerVector template with
// micro-argument
template <typename... Args>
Rcpp::NumericVector classification_base(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const classification& foo,
    Rcpp::Nullable<bool> micro,
    Args&&... args)
{
    // 0) Extract the number of classes
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length();

    // 1) Construct the confusion matrix
    Eigen::MatrixXd matrix = confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1);

    // 2) Handle micro or macro aggregation
    if (micro.isNull()) {
        Rcpp::NumericVector output(k);
        output = foo.compute(matrix, std::forward<Args>(args)...);
        output.attr("names") = levels; // Assign levels as names
        return output;
    }

    Rcpp::NumericVector output(1);
    output = foo.compute(matrix, Rcpp::as<bool>(micro), std::forward<Args>(args)...);
    return output;
}

// 4) IntegerVector template with
// micro-argument and w
template <typename... Args>
Rcpp::NumericVector classification_base(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const Rcpp::NumericVector& w,
    const classification& foo,
    Rcpp::Nullable<bool> micro,
    Args&&... args)
{
    // 0) Extract the number of classes
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length();

    // 1) Construct the confusion matrix
    Eigen::MatrixXd matrix = confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1, w);

    // 2) Handle micro or macro aggregation
    if (micro.isNull()) {
        Rcpp::NumericVector output(k);
        output = foo.compute(matrix, std::forward<Args>(args)...);
        output.attr("names") = levels; // Assign levels as names
        return output;
    }

    Rcpp::NumericVector output(1);
    output = foo.compute(matrix, Rcpp::as<bool>(micro), std::forward<Args>(args)...);
    return output;
}

/*
    Handling of classification applications:
    ----------------------------------------

    1) recipe:
        These templates handles the passed arguments, and passes the relevant args to be prepared. The baseic
        ingredients of the recipe are the following args in order:
            1. This what is passed down from the .cpp-files, and is then process by the class in
            "classification_Utils.H". 
            NOTE: This is ALWAYS the first argument in the .cpp-files. If done otherwise, it will NOT compile.
            2. The R method to process:
                1. It's either an IntegerVector pair (actual, predicted) or NumericMatrix. 
                    TODO: It should also handle NumericVectors for probability based methods.
            3. An (optional) NumericVector for weighted classification metrics.
            4. A Rcpp::Nullable<bool> micro-flag that determines if micro-aggregation should
            be done.
                TODO: Test if this can be optional too, and still appear as NULL in the exported function?
            5. Optional arguments to class.
                NOTE: With this is mostly kept for backwards, and forwards compatibility. If we want to add
                defensive measures this template doesn't need to be updated, as these can be passed into
                the class, and then define default behaviour in there.
    
    2) prepare:
        This template prepares the the arguments passed from the recipe-template, and processes them
        so they can be computed class. 
        NOTE: It doesn't matter what you call the functions on the .cpp-side, as long as it's instantiated
        as a function. This behaviour corresponds to FUN in lapply().
        The basic args passed into the preparation are the following args in order:
            1. The derived class, ie. the function that calculates the
            relevant metric.
            2. The matrix which are passed onto the class. This what the calculations
            are done on.
            3. Optional arguments to class.
                NOTE: With this is mostly kept for backwards, and forwards compatibility. If we want to add
                defensive measures this template doesn't need to be updated, as these can be passed into
                the class, and then define default behaviour in there.

    3) usage:

        Rcpp::NumericVector metric(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted) {
            DerivedClassMetric myFoo;
            return recipe(myFoo, actual, predicted);
            }
    
*/
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
        output.attr("names") = names; // Assign names as attribute
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
    const Rcpp::Nullable<bool>& micro = R_NilValue,
    Args&&... args) {

    const Eigen::MatrixXd eigen_matrix = Rcpp::as<Eigen::MatrixXd>(matrix);

    if (micro.isNull()) {
        return cook.compute(eigen_matrix, std::forward<Args>(args)...);
    }

    const Rcpp::List dimnames = matrix.attr("dimnames");
    const Rcpp::CharacterVector names = Rcpp::as<Rcpp::CharacterVector>(dimnames[1]);

    return prepare(cook, eigen_matrix, micro, names, std::forward<Args>(args)...);
}

template <typename... Args>
Rcpp::NumericVector recipe(
    const classification& cook,
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const std::optional<Rcpp::NumericVector>& w = std::nullopt,
    const Rcpp::Nullable<bool>& micro = R_NilValue,
    Args&&... args)
{
    const Rcpp::CharacterVector levels = actual.attr("levels");
    const int k = levels.size();
    Eigen::MatrixXd matrix(k + 1, k + 1);

    matrix = w.has_value()
        ? confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1, *w)
        : confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1);
    
    if (micro.isNull()) {
        return cook.compute(matrix, std::forward<Args>(args)...);
    }

    return prepare(cook, matrix, micro, levels, std::forward<Args>(args)...);
}


