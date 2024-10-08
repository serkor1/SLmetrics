#include <Rcpp.h>
#include <cmath>

//' Compute the \eqn{\text{symmetric mean absolute percentage error}}
//'
//' The [smape()]- and [wsmape()]-function computes the simple and weighted [symmetric mean absolute percentage error](https://en.wikipedia.org/wiki/Symmetric_mean_absolute_percentage_error).
//'
//' @usage
//' # `smape()`-function
//' smape(
//'   actual,
//'   predicted
//' )
//'
//' @inherit huberloss
//'
//' @example man/examples/scr_smape.R
//'
//' @section Calculation:
//'
//' The metric is calculated as follows,
//'
//' \deqn{
//'   \sum_i^n \frac{1}{n} \frac{|y_i - \upsilon_i|}{\frac{|y_i|+|\upsilon_i|}{2}}
//' }
//'
//' where \eqn{y_i} and \eqn{\upsilon_i} is the `actual` and `predicted` values respectively. If `w` is not [NULL], the metric is calculated
//' using weights.
//'
//' @family regression
//' @export
// [[Rcpp::export]]
double smape(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted) {

 // This function calculates the SMAPE
 const std::size_t n = actual.size();
 const double* actual_ptr = actual.begin();
 const double* predicted_ptr = predicted.begin();

 double output = 0.0;
 for (std::size_t i = 0; i < n; ++i) {
   double denominator = std::abs(actual_ptr[i]) + std::abs(predicted_ptr[i]);
   if (denominator != 0) {
     double difference = std::abs(actual_ptr[i] - predicted_ptr[i]) / (denominator / 2);
     output += difference;
   }
 }
 return (output / n );
}

//' @rdname smape
//'
//' @usage
//' # `wsmape()`-function
//' wsmape(
//'   actual,
//'   predicted,
//'   w
//' )
//'
//' @export
// [[Rcpp::export]]
double wsmape(
   const Rcpp::NumericVector& actual,
   const Rcpp::NumericVector& predicted,
   const Rcpp::NumericVector& w) {

 // This function calculates the weighted SMAPE
 const std::size_t n = actual.size();
 const double* actual_ptr = actual.begin();
 const double* predicted_ptr = predicted.begin();
 const double* w_ptr = w.begin();

 double numerator = 0.0;
 double denominator = 0.0;

 for (std::size_t i = 0; i < n; ++i) {
   double total_abs = std::abs(actual_ptr[i]) + std::abs(predicted_ptr[i]);
   if (total_abs != 0) {
     numerator += std::abs(actual_ptr[i] - predicted_ptr[i]) / (total_abs / 2) * w_ptr[i];
     denominator += w_ptr[i];
   }
 }
 return (numerator / denominator);
}
