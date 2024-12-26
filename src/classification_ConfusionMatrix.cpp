// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_ConfusionMatrix.h"
#include <Rcpp.h>
using namespace Rcpp;

//' @rdname cmatrix
//' @method cmatrix factor
//' @export
// [[Rcpp::export(cmatrix.factor)]]
Rcpp::NumericMatrix ConfusionMatrix(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::Nullable<Rcpp::NumericVector>& w = R_NilValue) 
{

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
        
        output = Rcpp::wrap(confusionMatrix<Eigen::MatrixXd>(actual, predicted, k));

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
