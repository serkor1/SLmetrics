/*
 * This header file includes the declarations
 * of the functions that are exported and serves as
 * helper functions in some cases.
 *
 * NOTE to self: It can be used in helper.h as well, but
 * this clutters the file.
 *
 * REMEMBER! It has to be declared exactly as is, otherwise
 * the package will explode in colorful error messages nobody (I think)
 * understands.
 *
 * Thank you Stackoverflow! <3
 */

Rcpp::NumericVector recall_cmatrix(const NumericMatrix& x, Nullable<bool> micro = R_NilValue);
Rcpp::NumericVector precision_cmatrix(const NumericMatrix& x, Nullable<bool> micro = R_NilValue);
// Rcpp::NumericVector specificity(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const bool& aggregate);
