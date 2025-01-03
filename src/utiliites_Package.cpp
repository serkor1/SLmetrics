#include "utilities_Package.h"
#include <Rcpp.h>


static bool use_openmp_flag = false;

//' Use OpenMP
//'
//' @param value A <[logical]> value of [length] 1 (Default: [FALSE]). If [TRUE] OpenMP will be used to parallelize computations.
//'
//' @family Utils
//'
//' @export
// [[Rcpp::export]]
void setUseOpenMP(bool value = false) {
    use_openmp_flag = value;
    Rcpp::Rcout << "OpenMP usage set to: " << (use_openmp_flag ? "enabled" : "disabled") << std::endl;
}

bool getUseOpenMP() {
    return use_openmp_flag;
}