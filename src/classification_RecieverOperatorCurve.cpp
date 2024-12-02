#include "classification_RecieverOperatorCurve.h"
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double auc(const Rcpp::NumericVector y, const Rcpp::NumericVector x, const int& method = 0)
{

  return calcArea(y, x, method);

}

//' @rdname ROC
//' @method ROC factor
//' @export
// [[Rcpp::export(ROC.factor)]]
Rcpp::DataFrame ROC(const Rcpp::IntegerVector &actual,
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
    Named("fpr") = empty_numeric,
    Named("tpr") = empty_numeric,
    Named("class") = CharacterVector::create("ROC", "data.frame")
  );

  return empty_df;

}


