#include <Rcpp.h>
#include "regression_PinballLoss.h"
using namespace Rcpp;



//' @rdname pinball
//' @method pinball numeric
//' @export
// [[Rcpp::export(pinball.numeric)]]
double pinball(const std::vector<double>& actual, const std::vector<double>& predicted, double alpha = 0.5, const bool& deviance = false, Rcpp::Nullable<std::vector<double>> w = R_NilValue, bool na_rm = false)
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
   std::vector<double> quantiles;

   // 1) Calculate dsq
   if (deviance) {

      // 1.1) copy the
      // actual vector and
      // calculate the quantiles
      std::vector<double> actualCopy = actual;
      quantiles = _quantile_(actualCopy, alpha, na_rm);

      // 1.2) unweighted deviance
      // with early return
      if (w.isNull()) {

         quantile = _metric_(actual, quantiles, alpha, na_rm);
         output   = _metric_(actual, predicted, alpha, na_rm);


         return 1.0 - output/quantile;

      }

      // 1.3) weighted deviance
      // with ealy return
      quantile = _metric_(actual, quantiles, Rcpp::as<std::vector<double>>(w), alpha, na_rm);
      output   = _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), alpha, na_rm);

      return 1.0 - output/quantile;

   }

   // 2) unweighted
   // mean pinball score
   if (w.isNull()) {

      output = _metric_(actual, predicted, alpha, na_rm);

      return output;

   }

   // 3) weighted
   // mean pinball score
   output = _metric_(actual, predicted, Rcpp::as<std::vector<double>>(w), alpha, na_rm);

   return output;

}