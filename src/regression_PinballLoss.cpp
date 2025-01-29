#include <Rcpp.h>
#include "regression_PinballLoss.h"
using namespace Rcpp;

//' @rdname pinball
//' @method pinball numeric
//' @export
// [[Rcpp::export(pinball.numeric)]]
double pinball(const Rcpp::NumericVector& actual,
               const Rcpp::NumericVector& predicted,
               double alpha = 0.5,
               bool deviance = false)
{
    // 1) Extract pointers
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    std::size_t n = actual.size();

    // 2) If not deviance, compute plain pinball loss (unweighted)
    if (!deviance) {
        return PinballLoss::compute(ptr_actual, ptr_predicted, n, alpha);
    }

    // 3) deviance = 1 - (pinball_loss / quantile_loss)
    //    where quantile_loss is the pinball loss if we predicted
    //    the alpha-quantile of `actual`.
    double qValue = PinballLoss::quantile(ptr_actual, n, alpha);

    double qLoss  = PinballLoss::computeConstantPred(ptr_actual, n, alpha, qValue);
    double pLoss  = PinballLoss::compute(ptr_actual, ptr_predicted, n, alpha);

    return 1.0 - (pLoss / qLoss);
}

//' @rdname pinball
//' @method weighted.pinball numeric
//' @export
// [[Rcpp::export(weighted.pinball.numeric)]]
double weighted_pinball(const Rcpp::NumericVector& actual,
                        const Rcpp::NumericVector& predicted,
                        const Rcpp::NumericVector& w,
                        double alpha = 0.5,
                        bool deviance = false)
{
    // 1) Extract pointers
    const double* ptr_actual    = actual.begin();
    const double* ptr_predicted = predicted.begin();
    const double* ptr_w         = w.begin();
    std::size_t n = actual.size();

    // 2) If not deviance, compute plain pinball loss (weighted)
    if (!deviance) {
        return PinballLoss::compute(ptr_actual, ptr_predicted, ptr_w, n, alpha);
    }

    // 3) deviance
    //    quantile_loss = pinball loss using the weighted alpha-quantile
    double qValue = PinballLoss::quantile(ptr_actual, ptr_w, n, alpha);

    double qLoss  = PinballLoss::computeConstantPred(ptr_actual, ptr_w, n, alpha, qValue);
    double pLoss  = PinballLoss::compute(ptr_actual, ptr_predicted, ptr_w, n, alpha);

    return 1.0 - (pLoss / qLoss);
}
