#include <Rcpp.h>
#include "regression_PinballLoss.h"
using namespace Rcpp;

//' @rdname pinball
//' @method pinball numeric
//' @export
// [[Rcpp::export(pinball.numeric)]]
double pinball(const Rcpp::NumericVector& actual, const Rcpp::NumericVector& predicted, const double& alpha = 0.5, const bool& deviance = false, Rcpp::Nullable<Rcpp::NumericVector> w = R_NilValue)
{

   /*
    * This function calculates the pinball score. If deviance
    * is TRUE it returns the Pinball score relative to
    * the baseline model.
    *
    * NOTE: As the input is constant, and the quantile
    * function modifies the vector it needs to be cloned.
    */

   // 0) variable declarations
   double output = 0.0;
   double quantile = 0.0;
   Rcpp::NumericVector quantiles;

   // 1) Calculate dsq
   if (deviance) {

      // 1.1) copy the
      // actual vector and
      // calculate the quantiles
      Rcpp::NumericVector actualCopy = Rcpp::clone(actual);
      quantiles = _quantile_(actualCopy, alpha);

      // 1.2) unweighted deviance
      // with early return
      if (w.isNull()) {

         quantile = _metric_(actual, quantiles, alpha);
         output   = _metric_(actual, predicted, alpha);


         return 1.0 - output/quantile;

      }

      // 1.3) weighted deviance
      // with ealy return
      quantile = _metric_(actual, quantiles, Rcpp::as<Rcpp::NumericVector>(w), alpha);
      output   = _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w), alpha);

      return 1.0 - output/quantile;

   }

   // 2) unweighted
   // mean pinball score
   if (w.isNull()) {

      output = _metric_(actual, predicted, alpha);

      return output;

   }

   // 3) weighted
   // mean pinball score
   output = _metric_(actual, predicted, Rcpp::as<Rcpp::NumericVector>(w), alpha);

   return output;

}
