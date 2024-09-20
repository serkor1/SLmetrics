#include <Rcpp.h>
#include <cmath>

//' Mean Absolute Percentage Error (MAPE)
//'
//' Calculate the MAPE using the [mape()]-function for the simple mean, or [wmape()]-function for the weighted mean.
//'
//' @usage
//' # simple MAPE
//' mape(
//'   actual,
//'   predicted
//' )
//'
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
 return (output / n) * 100.0;
}

//' @rdname mape
//'
//' @usage
//' # weighted MAPE
//' wmape(
//'   actual,
//'   predicted,
//'   w
//' )
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
 return (numerator / denominator) * 100.0;
}
