#include <Rcpp.h>
#include "regression_RootMeanSquaredError.h"
using namespace Rcpp;

//' @rdname rmse
//' @method rmse numeric
//' @export
// [[Rcpp::export(rmse.numeric)]]
double rmse(
    const Rcpp::NumericVector& actual,
    const Rcpp::NumericVector& predicted,
    Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue
    ) {

    if (w.isNull()) {

        return _metric_(actual, predicted);

    }

    return _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w));
}

