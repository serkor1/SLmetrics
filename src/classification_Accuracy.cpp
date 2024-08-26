#include <Rcpp.h>
using namespace Rcpp;

//' Accuracy
//'
//'
//' @export
// [[Rcpp::export]]
double accuracy(
    const NumericVector& actual,
    const NumericVector& predicted) {

  const int n = actual.size();

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int correct_count = 0;

  for (int i = 0; i < n; ++i) {

    correct_count += (*(actual_ptr++) == *(predicted_ptr++));

  }

  return static_cast<double> (correct_count) / n;
}
