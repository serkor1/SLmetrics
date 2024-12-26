// [[Rcpp::depends(RcppEigen)]]
#include <RcppEigen.h>
#include "classification_Recall.h" // RecallClass definition

// Namespace for cleaner usage
using namespace Rcpp;

//' @rdname recall
//' @method recall factor
//' @export
// [[Rcpp::export(recall.factor)]]
Rcpp::NumericVector Recall(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    RecallClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname recall
//' @method weighted.recall factor
//' @export
// [[Rcpp::export(weighted.recall.factor)]]
Rcpp::NumericVector weighted_Recall(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    RecallClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname recall
//'
//' @method recall cmatrix
//' @export
// [[Rcpp::export(recall.cmatrix)]]
Rcpp::NumericVector cmatrix_Recall(const NumericMatrix& x, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{

  RecallClass cook(na_rm);
  return recipe(cook, x, micro);

}

//' @rdname recall
//' @method sensitivity factor
//'
//' @export
// [[Rcpp::export(sensitivity.factor)]]
Rcpp::NumericVector Sensitivity(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true) 
{
    RecallClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);

}

//' @rdname recall
//' @method weighted.sensitivity factor
//' @export
// [[Rcpp::export(weighted.sensitivity.factor)]]
Rcpp::NumericVector weighted_Sensitivity(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    RecallClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname recall
//'
//' @method sensitivity cmatrix
//' @export
// [[Rcpp::export(sensitivity.cmatrix)]]
Rcpp::NumericVector cmatrix_Sensitivity(const NumericMatrix& x,  Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{
    RecallClass cook(na_rm);
    return recipe(cook, x, micro);
}


//' @rdname recall
//'
//' @method tpr factor
//' @export
// [[Rcpp::export(tpr.factor)]]
Rcpp::NumericVector TruePositiveRate(const IntegerVector& actual, const IntegerVector& predicted, Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{
    RecallClass cook(na_rm);
    return recipe(cook, actual, predicted, std::nullopt, micro);
}

//' @rdname recall
//' @method weighted.tpr factor
//' @export
// [[Rcpp::export(weighted.tpr.factor)]]
Rcpp::NumericVector weighted_TruePositiveRate(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted, const Rcpp::NumericVector& w, Rcpp::Nullable<bool> micro = R_NilValue, bool na_rm = true) 
{
    RecallClass cook(na_rm);
    return recipe(cook, actual, predicted, w, micro);
}

//' @rdname recall
//'
//' @method tpr cmatrix
//' @export
// [[Rcpp::export(tpr.cmatrix)]]
Rcpp::NumericVector cmatrix_TruePositiveRate(const NumericMatrix& x,  Nullable<bool> micro = R_NilValue, const bool& na_rm = true)
{
    RecallClass cook(na_rm);
    return recipe(cook, x, micro);
}