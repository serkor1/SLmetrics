#include <Rcpp.h>
#include "classification_fbeta.h"
using namespace Rcpp;

//' @rdname fbeta
//' @method fbeta factor
//'
//' @export
// [[Rcpp::export(fbeta.factor)]]
NumericVector fbeta(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    const double& beta = 1.0,
    Nullable<bool> micro = R_NilValue) {


  // 1) Calculate
  // cmatrix
  const Eigen::MatrixXi& x = confmat(actual, predicted);

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(x, beta);

    // 1.2) retrieve the names
    // and assign it to the output
    // vector and stop the function early
    output.attr("names") = actual.attr("levels");

    // 1.3) stop the function
    // and return the output.
    return output;
  }

  return _metric_(x, beta,  Rcpp::as<bool>(micro));

}

//' @rdname fbeta
//' @method fbeta cmatrix
//'
//' @export
// [[Rcpp::export(fbeta.cmatrix)]]
NumericVector fbeta_cmatrix(const IntegerMatrix& x, const double& beta = 1.0,  Nullable<bool> micro = R_NilValue)
{

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(Rcpp::as<Eigen::MatrixXi>(x), beta);

    // 1.2) retrieve the dimnames
    // and assign it to the output
    // vector and stop the function early
    Rcpp::List dimnames = x.attr("dimnames");
    output.attr("names") = dimnames[1];  // Directly assign the column names

    // 1.3) stop the function
    // and return the output.
    return output;

  }

  return _metric_(Rcpp::as<Eigen::MatrixXi>(x), beta,  Rcpp::as<bool>(micro));

}
