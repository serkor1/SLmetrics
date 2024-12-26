// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include <cmath>
#include "classification_MatthewsCorrelationCoefficient.h"
using namespace Rcpp;


//' @rdname mcc
//' @method mcc factor
//' @export
// [[Rcpp::export(mcc.factor)]]
Rcpp::NumericVector MatthewsCorrelationCoefficient(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{
   MatthewsCorrelationCoefficientClass cook;
   return recipe(cook, actual, predicted);
}

//' @rdname mcc
//' @method weighted.mcc factor
//' @export
// [[Rcpp::export(weighted.mcc.factor)]]
Rcpp::NumericVector weigthed_MatthewsCorrelationCoefficient(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector w)
{
   MatthewsCorrelationCoefficientClass cook;
   return recipe(cook, actual, predicted, w);
}

//' @rdname mcc
//' @method mcc cmatrix
//' @export
// [[Rcpp::export(mcc.cmatrix)]]
Rcpp::NumericVector cmatrix_MatthewsCorrelationCoefficient(const Rcpp::NumericMatrix& x)
{
   MatthewsCorrelationCoefficientClass cook;
   return recipe(cook, x);

}

//' @rdname mcc
//' @method phi factor
//' @export
// [[Rcpp::export(phi.factor)]]
Rcpp::NumericVector PhiCoefficient(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{
   MatthewsCorrelationCoefficientClass cook;
   return recipe(cook, actual, predicted);

}

//' @rdname mcc
//' @method weighted.phi factor
//' @export
// [[Rcpp::export(weighted.phi.factor)]]
Rcpp::NumericVector weighted_PhiCoefficient(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector w)
{
   MatthewsCorrelationCoefficientClass cook;
   return recipe(cook, actual, predicted, w);

}


//' @rdname mcc
//' @method phi cmatrix
//' @export
// [[Rcpp::export(phi.cmatrix)]]
Rcpp::NumericVector cmatrix_PhiCoefficient(const Rcpp::NumericMatrix& x)
{
   MatthewsCorrelationCoefficientClass cook;
   return recipe(cook, x);

}

