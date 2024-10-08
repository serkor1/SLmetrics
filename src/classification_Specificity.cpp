// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Specificity.h"
using namespace Rcpp;

//' @rdname specificity
//' @method specificity factor
//'
//' @export
// [[Rcpp::export(specificity.factor)]]
NumericVector specificity(const IntegerVector& actual, const IntegerVector& predicted,Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{

  // 1) Calculate
  // cmatrix
  const Eigen::MatrixXi& x = confmat(actual, predicted);

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(x);

    // 1.2) retrieve the names
    // and assign it to the output
    // vector and stop the function early
    output.attr("names") = actual.attr("levels");

    // 1.3) stop the function
    // and return the output.
    return output;
  }

  return _metric_(x,  Rcpp::as<bool>(micro), na_rm);

}

//' @rdname specificity
//' @method specificity cmatrix
//'
//' @export
// [[Rcpp::export(specificity.cmatrix)]]
Rcpp::NumericVector specificity_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
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


//' @rdname specificity
//' @method tnr factor
//'
//' @export
// [[Rcpp::export(tnr.factor)]]
NumericVector tnr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{


  // 1) Calculate
  // cmatrix
  const Eigen::MatrixXi& x = confmat(actual, predicted);

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(x);

    // 1.2) retrieve the names
    // and assign it to the output
    // vector and stop the function early
    output.attr("names") = actual.attr("levels");

    // 1.3) stop the function
    // and return the output.
    return output;
  }

  return _metric_(x,  Rcpp::as<bool>(micro), na_rm);

}


//' @rdname specificity
//' @method tnr cmatrix
//'
//' @export
// [[Rcpp::export(tnr.cmatrix)]]
Rcpp::NumericVector tnr_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
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

//' @rdname specificity
//' @method selectivity factor
//'
//' @export
// [[Rcpp::export(selectivity.factor)]]
NumericVector selectivity(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{


  // 1) Calculate
  // cmatrix
  const Eigen::MatrixXi& x = confmat(actual, predicted);

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(x);

    // 1.2) retrieve the names
    // and assign it to the output
    // vector and stop the function early
    output.attr("names") = actual.attr("levels");

    // 1.3) stop the function
    // and return the output.
    return output;
  }

  return _metric_(x,  Rcpp::as<bool>(micro), na_rm);

}


//' @rdname specificity
//' @method selectivity cmatrix
//'
//' @export
// [[Rcpp::export(selectivity.cmatrix)]]
Rcpp::NumericVector selectivity_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
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
