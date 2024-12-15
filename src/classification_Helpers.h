#include <Rcpp.h>
#include <Eigen/Dense>
#include "classification_Utils.h"
#include "src_Helpers.h"

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
    const Rcpp::IntegerMatrix& matrix,
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
    const Rcpp::IntegerMatrix& matrix,
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


