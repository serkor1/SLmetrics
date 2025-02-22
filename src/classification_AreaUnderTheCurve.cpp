#include "classification_AreaUnderTheCurve.h"
#include <Rcpp.h>

using namespace Rcpp;

//' @rdname auc
//' @method auc numeric
//' @export
// [[Rcpp::export(auc.numeric)]]
double auc(
    const Rcpp::NumericVector& y, 
    const Rcpp::NumericVector& x, 
    const int& method = 0,
    const bool& ordered = true) {

    // 1) Extract pointers and
    // lengths
    const double* ptr_y = y.begin();
    const double* ptr_x = x.begin();
    const std::size_t n = y.size();

    // 2) Calculate and return
    // Area Under the Curve
    return AUC::calculate(ptr_y, ptr_x, n, method, ordered);

}
