// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_nlr.h"".h"
using namespace Rcpp;

//' @rdname nlr
//'
//' @method nlr factor
//' @export
// [[Rcpp::export(nlr.factor)]]
NumericVector nlr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{

  // 0)
  const Eigen::MatrixXi& matrix = confmat(actual, predicted);

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(matrix);

    // 1.2) retrieve the dimnames
    // and assign it to the output
    // vector and stop the function early
    output.attr("names") = actual.attr("levels");

    // 1.3) stop the function
    // and return the output.
    return output;

  }

  return _metric_(matrix,  Rcpp::as<bool>(micro), na_rm);


}


//' @rdname nlr
//'
//' @method nlr cmatrix
//' @export
// [[Rcpp::export(nlr.cmatrix)]]
Rcpp::NumericVector nlr_cmatrix(const Rcpp::IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(Rcpp::as<Eigen::MatrixXi>(x));

    // 1.2) retrieve the dimnames
    // and assign it to the output
    // vector and stop the function early
    Rcpp::List dimnames = x.attr("dimnames");
    output.attr("names") = dimnames[1];  // Directly assign the column names

    // 1.3) stop the function
    // and return the output.
    return output;

  }

  return _metric_(Rcpp::as<Eigen::MatrixXi>(x),  Rcpp::as<bool>(micro), na_rm);

}
