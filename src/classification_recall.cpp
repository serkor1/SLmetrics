// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_recall.h"
using namespace Rcpp;

//' @rdname recall
//' @method recall factor
//'
//' @export
//[[Rcpp::export(recall.factor)]]
Rcpp::NumericVector recall(
    const IntegerVector& actual,
    const IntegerVector& predicted,
    Nullable<bool> micro = R_NilValue) {

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

  return _metric_(actual, predicted,  Rcpp::as<bool>(micro));

}

//' @rdname recall
//'
//' @method recall cmatrix
//' @export
// [[Rcpp::export(recall.cmatrix)]]
Rcpp::NumericVector recall_cmatrix(const IntegerMatrix& x, Nullable<bool> micro = R_NilValue)
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
  return _metric_(Rcpp::as<Eigen::MatrixXi>(x), Rcpp::as<bool>(micro));

}

//' @rdname recall
//' @method sensitivity factor
//'
//' @export
// [[Rcpp::export(sensitivity.factor)]]
Rcpp::NumericVector sensitivity(
   const IntegerVector& actual,
   const IntegerVector& predicted,
   Nullable<bool> micro = R_NilValue) {

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

  return _metric_(actual, predicted,  Rcpp::as<bool>(micro));


}

//' @rdname recall
//'
//' @method sensitivity cmatrix
//' @export
// [[Rcpp::export(sensitivity.cmatrix)]]
Rcpp::NumericVector sensitivity_cmatrix(const IntegerMatrix& x,  Nullable<bool> micro = R_NilValue)
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
  return _metric_(Rcpp::as<Eigen::MatrixXi>(x), Rcpp::as<bool>(micro));

}


//' @rdname recall
//'
//' @method tpr factor
//' @export
// [[Rcpp::export(tpr.factor)]]
Rcpp::NumericVector tpr(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue) {

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

  return _metric_(actual, predicted,  Rcpp::as<bool>(micro));


}

//' @rdname recall
//'
//' @method tpr cmatrix
//' @export
// [[Rcpp::export(tpr.cmatrix)]]
Rcpp::NumericVector tpr_cmatrix(const IntegerMatrix& x,  Nullable<bool> micro = R_NilValue)
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
  return _metric_(Rcpp::as<Eigen::MatrixXi>(x), Rcpp::as<bool>(micro));

}


