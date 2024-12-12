// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "src_Helpers.h"
#include <Rcpp.h>
using namespace Rcpp;
//' Confusion Matrix
//'
//' @description
//'
//' The [cmatrix()]-function uses cross-classifying factors to build
//' a confusion matrix of the counts at each combination of the [factor] levels.
//' Each row of the [matrix] represents the actual [factor] levels, while each
//' column represents the predicted [factor] levels.
//'
//' @usage
//' cmatrix(
//'   actual,
//'   predicted,
//'   w
//' )
//'
//' @param actual A <[factor]>-vector of [length] \eqn{n}, and \eqn{k} levels.
//' @param predicted A <[factor]>-vector of [length] \eqn{n}, and \eqn{k} levels.
//' @param w A <[numeric]>--vector of [length] \eqn{n}. [NULL] by default. If passed it will return a weighted confusion matrix.
//'
//' @example man/examples/scr_confusionmatrix.R
//' @example man/examples/scr_wconfusionmatrix.R
//' @family classification
//'
//' @inherit specificity details
//'
//' @section Dimensions:
//'
//' There is no robust defensive measure against misspecififying
//' the confusion matrix. If the arguments are correctly specified, the resulting
//' confusion matrix is on the form:
//'
//' |            | A (Predicted) | B (Predicted) |
//' | :----------|:-------------:| -------------:|
//' | A (Actual) | Value         | Value         |
//' | B (Actual) | Value         | Value         |
//'
//'
//' @returns
//'
//' A named \eqn{k} x \eqn{k} <[matrix]> of [class] <cmatrix>
//'
//' @export
// [[Rcpp::export]]
Rcpp::NumericMatrix cmatrix(
    const Rcpp::IntegerVector& actual,
    const Rcpp::IntegerVector& predicted,
    const Rcpp::Nullable<Rcpp::NumericVector>& w = R_NilValue) {

    // 1) declare the output matrix
    // compiler doesn't recognize it in if-statements
    Rcpp::NumericMatrix output;

    // 1.1) extract levels (classes)
    // from the actual-vector and the length
    Rcpp::CharacterVector levels = actual.attr("levels");
    int k = levels.length() + 1;

    // 2) Determine the weights
    // these are what determines 
    // the content of the confusion matrix
     if (w.isNull()) {
        
        output = Rcpp::wrap(confusionMatrix<Eigen::MatrixXi>(actual, predicted, k));

    } else {
        
        output = Rcpp::wrap(confusionMatrix<Eigen::MatrixXd>(actual, predicted, k, w));

    }

    // 3) preare the matrix output
    // by adding column and rownames
    // and classes
    Rcpp::rownames(output) = levels;
    Rcpp::colnames(output) = levels;
    output.attr("class") = "cmatrix";

    return output;
}
