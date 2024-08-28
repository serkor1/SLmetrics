#include <Rcpp.h>
using namespace Rcpp;

//' Zero One Loss
//'
//' @param actual placeholder
//' @param predicted placeholder
//'
//' @export
// [[Rcpp::export]]
double zerooneloss(
    const NumericVector& actual,
    const NumericVector& predicted) {

  const int n = actual.size();

  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  int incorrect_count = 0;

  for (int i = 0; i < n; ++i) {

    incorrect_count += (*(actual_ptr++) != *(predicted_ptr++));

  }

  return static_cast<double> (incorrect_count) / n;
}
