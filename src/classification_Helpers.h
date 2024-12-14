#include <Rcpp.h>
#include <Eigen/Dense>
#include "classification_Utils.h"
#include "src_Helpers.h"

Rcpp::NumericVector classification_base(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const classification& foo,
    const bool& na_rm = true)
{
    // 0) Extract the number of classes
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length();

    // 1) Construct the confusion matrix
    Eigen::MatrixXd matrix = confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1); 


    Rcpp::NumericVector output(1);
    output = foo.compute(matrix, na_rm);
    return output;
}

Rcpp::NumericVector classification_base(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const Rcpp::NumericVector& w,
    const classification& foo,
    const bool& na_rm = true)
{
    // 0) Extract the number of classes
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length();

    // 1) Construct the confusion matrix
    Eigen::MatrixXd matrix = confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1, w); 

    Rcpp::NumericVector output(1);
    output = foo.compute(matrix, na_rm);
    return output;
}

Rcpp::NumericVector classification_base(
    const Rcpp::IntegerMatrix& matrix,
    const classification& foo,
    const bool& na_rm = true)
{

    // 1) Convert matrix to Eigen format
    const Eigen::MatrixXd eigen_matrix = Rcpp::as<Eigen::MatrixXd>(matrix);


    Rcpp::NumericVector output(1);
    output = foo.compute(eigen_matrix, na_rm);
    return output;
}



Rcpp::NumericVector classification_base(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const classification& foo,
    Rcpp::Nullable<bool> micro = R_NilValue,
    const bool& na_rm = true)
{
    // 0) Extract the number of classes
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length();

    // 1) Construct the confusion matrix
    Eigen::MatrixXd matrix = confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1); 

    // 2) Handle micro or macro aggregation
    if (micro.isNull()) {
        Rcpp::NumericVector output(k);
        output = foo.compute(matrix, na_rm);
        output.attr("names") = levels; // Assign levels as names
        return output;
    }

    Rcpp::NumericVector output(1);
    output = foo.compute(matrix, na_rm, Rcpp::as<bool>(micro));
    return output;
}

Rcpp::NumericVector classification_base(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const Rcpp::NumericVector& w,
    const classification& foo,
    Rcpp::Nullable<bool> micro = R_NilValue,
    const bool& na_rm = true)
{
    // 0) Extract the number of classes
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length();

    // 1) Construct the confusion matrix
    Eigen::MatrixXd matrix = confusionMatrix<Eigen::MatrixXd>(actual, predicted, k + 1, w); 

    // 2) Handle micro or macro aggregation
    if (micro.isNull()) {
        Rcpp::NumericVector output(k);
        output = foo.compute(matrix, na_rm);
        output.attr("names") = levels; // Assign levels as names
        return output;
    }

    Rcpp::NumericVector output(1);
    output = foo.compute(matrix, na_rm, Rcpp::as<bool>(micro));
    return output;
}


Rcpp::NumericVector classification_base(
    const Rcpp::IntegerMatrix& matrix,
    const classification& foo,
    Rcpp::Nullable<bool> micro = R_NilValue,
    const bool& na_rm = true)
{
    // 0) Extract dimension names
    const Rcpp::List& dimnames = matrix.attr("dimnames");
    const Rcpp::CharacterVector& names = dimnames[1];
    const int k = names.size();

    // 1) Convert matrix to Eigen format
    const Eigen::MatrixXd eigen_matrix = Rcpp::as<Eigen::MatrixXd>(matrix);

    // 2) Handle micro or macro aggregation
    if (micro.isNull()) {
        Rcpp::NumericVector output(k);
        output = foo.compute(eigen_matrix, na_rm);
        output.attr("names") = names; // Assign column names as names
        return output; // Return by value
    }

    Rcpp::NumericVector output(1);
    output = foo.compute(eigen_matrix, na_rm, Rcpp::as<bool>(micro));
    return output;
}

