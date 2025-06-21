#include "tools_AreaUnderTheCurve.h"

//' @title Area under the curve
//'
//' @rdname tools_auc.xy.numeric
//' @method auc.xy numeric
//'
//' @param y,x A pair of <[double]> vectors of [length] \eqn{n}.
//' @param method A <[integer]> value (default: \eqn{0}). Defines the underlying method of calculating the area under the curve. If \eqn{0} it is calculated using the `trapezoid`-method, if \eqn{1} it is calculated using the `step`-method.
//' @param presorted A <[logical]>-value [length] 1 (default: [FALSE]). If [TRUE] the input will not be sorted by threshold.
//' @param ... Arguments passed into other methods.
//'
//' @export
// [[Rcpp::export(auc.xy.numeric)]]
double auc(
    const Rcpp::NumericVector& y, 
    const Rcpp::NumericVector& x, 
    const int& method = 0,
    const bool& presorted = true) {

    // 1) Extract pointers and
    // lengths
    const double* ptr_y = y.begin();
    const double* ptr_x = x.begin();
    const std::size_t n = y.size();

    // 2) Calculate and return
    // Area Under the Curve
    return AUC::calculate(ptr_y, ptr_x, n, method, presorted);

}
