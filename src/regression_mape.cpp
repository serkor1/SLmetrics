#include <Rcpp.h>
#include <cmath>

//' Compute the \eqn{\text{mean absolute percentage error}}
//'
//' The [mape()]- and [wmape()]-function computes the simple and weighted [mean absolute percentage error](https://en.wikipedia.org/wiki/Mean_absolute_percentage_error) between
//' the observed and predicted <[numeric]> vectors. If `w` is not [NULL] the function returns the weighted mean absolute error.
//' @usage
//' # `mape()`-function
//' mape(
//'   actual,
//'   predicted
//' )
//'
//' @inherit huberloss
//'
//' @example man/examples/scr_mape.R
//'
//' @section Calculation:
//'
//' The metric is calculated as,
//'
//' \deqn{
//'   \frac{1}{n} \sum_i^n \frac{|y_i - \upsilon_i|}{|y_i|}
//' }
//'
//' If \eqn{\text{w}} is not [NULL], the weighted version is calculated.
//'
//' @family regression
//' @export
// [[Rcpp::export]]
double mape(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted) {

 // This function calculates the MAPE
 const std::size_t n = actual.size();
 const double* actual_ptr = actual.begin();
 const double* predicted_ptr = predicted.begin();

 double output = 0.0;

 for (std::size_t i = 0; i < n; ++i) {

   double difference = std::abs((actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i]);
   output += difference;

 }

 return (output / n);

}

//' @rdname mape
//'
//' @usage
//' # `wmape()`-function
//' wmape(
//'   actual,
//'   predicted,
//'   w
//' )
//'
//' @family regression
//'
//' @export
// [[Rcpp::export]]
double wmape(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted,
   const Rcpp::NumericVector& w) {

 // This function calculates the weighted MAPE
 const std::size_t n = actual.size();
 const double* actual_ptr = actual.begin();
 const double* predicted_ptr = predicted.begin();
 const double* w_ptr = w.begin();

 double numerator = 0.0;
 double denominator = 0.0;

 for (std::size_t i = 0; i < n; ++i) {

   numerator += std::abs((actual_ptr[i] - predicted_ptr[i]) / actual_ptr[i]) * w_ptr[i];
   denominator += w_ptr[i];

 }

 return (numerator / denominator);

}
