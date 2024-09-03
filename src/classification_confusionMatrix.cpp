#include <Rcpp.h>
using namespace Rcpp;

//' @export
// [[Rcpp::export]]
NumericMatrix confusion_matrix(
    const IntegerVector& actual,
    const IntegerVector& predicted) {

  /*
   * This function generates a confusion matrix
   * by incrementing locations based on the actual
   * vector. If it includes NA values it will
   * crash, so this function should check for missing
   * values in both vectors. This is for later
   */

  // 1) get levels of the for the
  // naming of the matrix
  const CharacterVector& levels = actual.attr("levels");

  const int numClasses = levels.size();

  // 2) create the k x k matrix
  // for all available factors
  NumericMatrix confusionMatrix(numClasses, numClasses);

  // 3) calculata the size of the
  // vector
  const int n = actual.size();

  // 3) populate the confusion
  // matrix.
  //
  // NOTE: factor variables starts at 1, and
  // C++ is 0 indexed, so we subtract 1!
  for (int i = 0; i < n; ++i) {
    const int actualVal = actual[i] - 1;
    const int predictedVal = predicted[i] - 1;
    ++confusionMatrix(actualVal, predictedVal);
  }

  // 4) set the dimnames of
  // the confusion matrix
  confusionMatrix.attr("dimnames") = List::create(levels, levels);

  return confusionMatrix;
}
