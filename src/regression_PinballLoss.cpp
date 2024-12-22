#include "regression_PinballLoss.h"
#include <Rcpp.h>
using namespace Rcpp;

//' @rdname pinball
//' @method pinball numeric
//' @export
// [[Rcpp::export(pinball.numeric)]]
double pinball(const std::vector<double>& actual, const std::vector<double>& predicted, double alpha = 0.5, bool deviance = false) 
{
    PinballLoss pinballMetric(alpha); // Instantiate Pinball Loss class

    if (deviance) {

        double quantile_value = pinballMetric.quantile(actual.begin(), actual.end());
        std::vector<double> quantiles(actual.size(), quantile_value);

        double quantile_loss = pinballMetric.compute(actual, quantiles);
        double pinball_loss = pinballMetric.compute(actual, predicted);

        return 1.0 - pinball_loss / quantile_loss;
    }

    // Unweighted pinball loss
    return pinballMetric.compute(actual, predicted);
}


//' @rdname pinball
//' @method weighted.pinball numeric
//' @export
// [[Rcpp::export(weighted.pinball.numeric)]]
double weighted_pinball(const std::vector<double>& actual, const std::vector<double>& predicted, const std::vector<double>& w, double alpha = 0.5, bool deviance = false) 
{
    PinballLoss pinballMetric(alpha); // Instantiate Pinball Loss class

    if (deviance) {
        // Compute quantiles directly using the input vectors
        std::vector<double> quantiles = pinballMetric.quantile(actual, w);

        double quantile_loss = pinballMetric.compute(actual, quantiles, w);
        double pinball_loss = pinballMetric.compute(actual, predicted, w);

        return 1.0 - pinball_loss / quantile_loss;
    }

    // Weighted pinball loss
    return pinballMetric.compute(actual, predicted, w);
}