// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include <cmath>
#include "classification_MatthewsCorrelationCoefficient.h"
using namespace Rcpp;


//' @rdname mcc
//' @method mcc factor
//' @export
// [[Rcpp::export(mcc.factor)]]
Rcpp::NumericVector mcc(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{
   MCCMetric foo; // Instantiate MCCMetric
   return classification_base(actual, predicted, foo);
}

//' @rdname mcc
//' @method weighted.mcc factor
//' @export
// [[Rcpp::export(weighted.mcc.factor)]]
Rcpp::NumericVector weigthed_mcc(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector w)
{
   MCCMetric foo; // Instantiate MCCMetric
   return classification_base(actual, predicted, w, foo);
}

//' @rdname mcc
//' @method mcc cmatrix
//' @export
// [[Rcpp::export(mcc.cmatrix)]]
Rcpp::NumericVector mcc_cmatrix(const Rcpp::NumericMatrix& x)
{
   MCCMetric foo; // Instantiate MCCMetric
   return classification_base(x, foo);

}

//' @rdname mcc
//' @method phi factor
//' @export
// [[Rcpp::export(phi.factor)]]
Rcpp::NumericVector phi(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{
   MCCMetric foo; // Instantiate MCCMetric
   return classification_base(actual, predicted, foo);

}

//' @rdname mcc
//' @method weighted.phi factor
//' @export
// [[Rcpp::export(weighted.phi.factor)]]
Rcpp::NumericVector weighted_phi(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector w)
{
   MCCMetric foo; // Instantiate MCCMetric
   return classification_base(actual, predicted, w, foo);

}


//' @rdname mcc
//' @method phi cmatrix
//' @export
// [[Rcpp::export(phi.cmatrix)]]
Rcpp::NumericVector phi_cmatrix(const Rcpp::NumericMatrix& x)
{
   MCCMetric foo; // Instantiate MCCMetric
   return classification_base(x, foo);

}

