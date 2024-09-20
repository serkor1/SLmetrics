#include <Rcpp.h>
#include <cmath>

//' Mean Percentage Error (MPE)
//'
//' Calculate the MPE using the [mpe()]-function for the simple mean, or [wmpe()]-function for the weighted mean.
//'
//' @usage
//' # simple MPE
//' mpe(
//'   actual,
//'   predicted
//' )
//'
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
 return (output / n) * 100.0;
}

//' @rdname mpe
//'
//' @usage
//' # weighted MPE
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
 return (numerator / denominator) * 100.0;
}
