#include <Rcpp.h>
#include <cmath>

//' Compute the \eqn{\text{mean percentage error}}
//'
//' The [mpe()]-function computes the [mean percentage error](https://en.wikipedia.org/wiki/Mean_percentage_error) between
//' the observed and predicted <[numeric]> vectors. If `w` is not [NULL], the function returns the weighted mean percentage error.
//' @usage
//' # `mpe()`-function
//' mpe(
//'   actual,
//'   predicted
//' )
//'
//' @inherit huberloss
//'
//' @example man/examples/scr_mpe.R
//'
//' @section Calculation:
//'
//' The metric is calculated as,
//'
//' \deqn{
//'   \frac{1}{n} \sum_i^n \frac{y_i - \upsilon_i}{y_i}
//' }
//'
//' Where \eqn{y_i} and \eqn{\upsilon_i} are the `actual` and `predicted` values respectively. If \eqn{\text{w}} is not [NULL], the weighted version is calculated.
//'
//' @family regression
//' @export
// [[Rcpp::export]]
double mpe(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted) {

 // This function calculates the MPE
 const std::size_t n = actual.size();
 const double* actual_ptr = actual.begin();
 const double* predicted_ptr = predicted.begin();

 double output = 0.0;
 for (std::size_t i = 0; i < n; ++i) {
   double percentage_error = (actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i];
   output += percentage_error;
 }
 return (output / n);
}

//' @rdname mpe
//'
//' @usage
//' # `wmpe()`-function
//' wmpe(
//'   actual,
//'   predicted,
//'   w
//' )
//' @export
// [[Rcpp::export]]
double wmpe(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted,
   const Rcpp::NumericVector& w) {

 // This function calculates the weighted MPE
 const std::size_t n = actual.size();
 const double* actual_ptr = actual.begin();
 const double* predicted_ptr = predicted.begin();
 const double* w_ptr = w.begin();

 double numerator = 0.0;
 double denominator = 0.0;

 for (std::size_t i = 0; i < n; ++i) {
   numerator += ((actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i]) * w_ptr[i];
   denominator += w_ptr[i];
 }
 return (numerator / denominator);
}
