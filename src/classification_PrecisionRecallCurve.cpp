#include "classification_PrecisionRecallCurve.h"
#include <Rcpp.h>
using namespace Rcpp;


//' @rdname prROC
//' @method prROC factor
//' @export
// [[Rcpp::export(prROC.factor)]]
Rcpp::DataFrame prROC(const Rcpp::IntegerVector &actual,
                      const Rcpp::NumericVector &response,
                      Nullable<bool> micro = R_NilValue,
                      Rcpp::Nullable<Rcpp::NumericVector> thresholds = R_NilValue,
                      const bool& na_rm = true) {

  /*
   *  Calculate ROC based
   * on micro values and
   * thresholds if passed
   */

  // 1) default return
  // value
  if (micro.isNull()) {

    return _metric_(actual, response, thresholds);

  }

  std::vector<double> empty_numeric;
  std::vector<int> empty_integer;
  CharacterVector empty_character;

  Rcpp::DataFrame empty_df = Rcpp::DataFrame::create(
    Named("threshold") = empty_numeric,
    Named("level") = empty_integer,
    Named("label") = empty_character,
    Named("precision") = empty_numeric,
    Named("recall") = empty_numeric
  );

  return empty_df;
}
