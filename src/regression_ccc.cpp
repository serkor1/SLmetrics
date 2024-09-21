#include <Rcpp.h>
#include <cmath>


//' Concordance Correlation Coefficient (CCC)
//'
//' Calculate the CCC using the [ccc()]-function for comparing actual and predicted values.
//'
//' @usage
//' # simple;
//' ccc(
//'   actual,
//'   predicted,
//'   correction = FALSE
//' )
//'
//' @inherit huberloss
//' @param correction A <[logical]> vector of [length] 1. [FALSE] by default. If [TRUE] the variance and covariance
//' will be adjusted with \eqn{\frac{1-n}{n}}
//'
//' @example man/examples/scr_ccc.R
//'
//' @family regression
//' @export
// [[Rcpp::export]]
double ccc(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    bool correction = false) {

  // This function calculates the Concordance Correlation Coefficient (CCC)
  const std::size_t n = actual.size();
  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();

  // Calculate means
  double mean_actual = 0.0;
  double mean_predicted = 0.0;
  for (std::size_t i = 0; i < n; ++i) {
    mean_actual += actual_ptr[i];
    mean_predicted += predicted_ptr[i];
  }
  mean_actual /= n;
  mean_predicted /= n;

  // Calculate variances and covariance
  double var_actual = 0.0;
  double var_predicted = 0.0;
  double covariance = 0.0;

  for (std::size_t i = 0; i < n; ++i) {
    var_actual += (actual_ptr[i] - mean_actual) * (actual_ptr[i] - mean_actual);
    var_predicted += (predicted_ptr[i] - mean_predicted) * (predicted_ptr[i] - mean_predicted);
    covariance += (actual_ptr[i] - mean_actual) * (predicted_ptr[i] - mean_predicted);
  }

  var_actual /= n;
  var_predicted /= n;
  covariance /= n;

  // Apply bias correction if requested
  if (correction) {
    var_actual *= (n - 1.0) / n;
    var_predicted *= (n - 1.0) / n;
    covariance *= (n - 1.0) / n;
  }

  // Calculate the Concordance Correlation Coefficient
  double ccc_value = (2 * covariance) / (var_actual + var_predicted + std::pow(mean_actual - mean_predicted, 2));

  return ccc_value;
}

//' @rdname ccc
//'
//' @usage
//' # weighted;
//' wccc(
//'   actual,
//'   predicted,
//'   w,
//'   correction = FALSE
//' )
//'
//' @family regression
//' @export
// [[Rcpp::export]]
double wccc(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    const Rcpp::NumericVector& w,
    bool correction = false) {

  // This function calculates the Weighted Concordance Correlation Coefficient (CCC)
  const std::size_t n = actual.size();
  const double* actual_ptr = actual.begin();
  const double* predicted_ptr = predicted.begin();
  const double* w_ptr = w.begin();

  // Initialize variables for weighted means, variances, and covariance
  double weighted_mean_actual = 0.0;
  double weighted_mean_predicted = 0.0;
  double sum_weights = 0.0;

  // Calculate the weighted means
  for (std::size_t i = 0; i < n; ++i) {
    weighted_mean_actual += actual_ptr[i] * w_ptr[i];
    weighted_mean_predicted += predicted_ptr[i] * w_ptr[i];
    sum_weights += w_ptr[i];
  }

  weighted_mean_actual /= sum_weights;
  weighted_mean_predicted /= sum_weights;

  // Initialize variables for weighted variances and covariance
  double weighted_var_actual = 0.0;
  double weighted_var_predicted = 0.0;
  double weighted_covariance = 0.0;

  // Calculate the weighted variances and covariance
  for (std::size_t i = 0; i < n; ++i) {
    double diff_actual = actual_ptr[i] - weighted_mean_actual;
    double diff_predicted = predicted_ptr[i] - weighted_mean_predicted;

    weighted_var_actual += w_ptr[i] * diff_actual * diff_actual;
    weighted_var_predicted += w_ptr[i] * diff_predicted * diff_predicted;
    weighted_covariance += w_ptr[i] * diff_actual * diff_predicted;
  }

  weighted_var_actual /= sum_weights;
  weighted_var_predicted /= sum_weights;
  weighted_covariance /= sum_weights;

  // Apply bias correction if requested
  if (correction) {
    weighted_var_actual *= (sum_weights - 1.0) / sum_weights;
    weighted_var_predicted *= (sum_weights - 1.0) / sum_weights;
    weighted_covariance *= (sum_weights - 1.0) / sum_weights;
  }

  // Calculate the Weighted Concordance Correlation Coefficient
  double weighted_ccc_value = (2 * weighted_covariance) /
    (weighted_var_actual + weighted_var_predicted + std::pow(weighted_mean_actual - weighted_mean_predicted, 2));

  return weighted_ccc_value;
}
