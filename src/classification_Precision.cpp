// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Precision.h"
using namespace Rcpp;



//' @rdname precision
//' @method precision factor
//'
//' @export
// [[Rcpp::export(precision.factor)]]
Rcpp::NumericVector precision(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    Nullable<bool> micro = R_NilValue,
    const bool& na_rm = true) {

  /*
   * NOTE:
   *
   * There are two solutions on passing the dimnames:
   *
   * 1. VECTOR_ELT(x.attr("dimnames"), 1)
   * 2. Creating a list, extracting the dimnames and assign it as dimnames[1]
   *
   * Both are too fast to be properly measured via
   * benchmark. It appears that both solution are
   * fast enough. The added overhead of this solution
   * and not directly using NumericVectors is offset by
   * the speed gain in cmatrix that was gained during
   * optimization, and that Eigen is faster than Rcpp NumericVector
   *
   *
   */

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(actual, predicted);

    // 1.2) retrieve the names
    // and assign it to the output
    // vector and stop the function early
    output.attr("names") = actual.attr("levels");

    // 1.3) stop the function
    // and return the output.
    return output;
  }

  return _metric_(actual, predicted,  Rcpp::as<bool>(micro), na_rm);

}

//' @rdname precision
//' @method precision cmatrix
//'
//' @export
// [[Rcpp::export(precision.cmatrix)]]
Rcpp::NumericVector precision_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{

  /*
   * NOTE:
   *
   * There are two solutions on passing the dimnames:
   *
   * 1. VECTOR_ELT(x.attr("dimnames"), 1)
   * 2. Creating a list, extracting the dimnames and assign it as dimnames[1]
   *
   * Both are too fast to be properly measured via
   * benchmark. It appears that both solution are
   * fast enough. The added overhead of this solution
   * and not directly using NumericVectors is offset by
   * the speed gain in cmatrix that was gained during
   * optimization, and that Eigen is faster than Rcpp NumericVector
   *
   *
   */

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

  // 2) return the metric directly
  // if the value is NULL
  // NOTE: It might be more efficient to just
  // pass the null value directly instead via
  // micro
  return _metric_(Rcpp::as<Eigen::MatrixXi>(x), Rcpp::as<bool>(micro), na_rm);

}

//' @rdname precision
//' @method ppv factor
//'
//' @export
// [[Rcpp::export(ppv.factor)]]
Rcpp::NumericVector ppv(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    Nullable<bool> micro = R_NilValue,
    const bool& na_rm = true) {

  /*
   * NOTE:
   *
   * There are two solutions on passing the dimnames:
   *
   * 1. VECTOR_ELT(x.attr("dimnames"), 1)
   * 2. Creating a list, extracting the dimnames and assign it as dimnames[1]
   *
   * Both are too fast to be properly measured via
   * benchmark. It appears that both solution are
   * fast enough. The added overhead of this solution
   * and not directly using NumericVectors is offset by
   * the speed gain in cmatrix that was gained during
   * optimization, and that Eigen is faster than Rcpp NumericVector
   *
   *
   */

  // 1) if micro is Null
  // the retured value are equal
  // to the amount dimensions
  if (micro.isNull()) {

    // 1.1) create the output
    // vector
    Rcpp::NumericVector output = _metric_(actual, predicted);

    // 1.2) retrieve the names
    // and assign it to the output
    // vector and stop the function early
    output.attr("names") = actual.attr("levels");

    // 1.3) stop the function
    // and return the output.
    return output;
  }

  return _metric_(actual, predicted,  Rcpp::as<bool>(micro), na_rm);

}



//' @rdname precision
//' @method ppv cmatrix
//'
//' @export
// [[Rcpp::export(ppv.cmatrix)]]
   Rcpp::NumericVector ppv_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
   {

     /*
      * NOTE:
      *
      * There are two solutions on passing the dimnames:
      *
      * 1. VECTOR_ELT(x.attr("dimnames"), 1)
      * 2. Creating a list, extracting the dimnames and assign it as dimnames[1]
      *
      * Both are too fast to be properly measured via
      * benchmark. It appears that both solution are
      * fast enough. The added overhead of this solution
      * and not directly using NumericVectors is offset by
      * the speed gain in cmatrix that was gained during
      * optimization, and that Eigen is faster than Rcpp NumericVector
      *
      *
      */

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

     // 2) return the metric directly
     // if the value is NULL
     // NOTE: It might be more efficient to just
     // pass the null value directly instead via
     // micro
     return _metric_(Rcpp::as<Eigen::MatrixXi>(x), Rcpp::as<bool>(micro), na_rm);

   }
