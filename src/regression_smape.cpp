#include <Rcpp.h>
#include <cmath>

//' Symmetric Mean Absolute Percentage Error (SMAPE)
//'
//' Calculate the SMAPE using the [smape()]-function for the simple mean, or [wsmape()]-function for the weighted mean.
//'
//' @usage
//' # simple SMAPE
//' smape(
//'   actual,
//'   predicted
//' )
//'
//' @inherit huberloss
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
//' # weighted SMAPE
//' wsmape(
//'   actual,
//'   predicted,
//'   w
//' )
//'
//' @family regression
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
