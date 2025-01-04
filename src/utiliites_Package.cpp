/*
    {pkg} uilities:
        setUseOpenMP: OpenMP flag (Default: FALSE)
        setNumberThreads: Number of threads to use (Default: -1). If -1 it uses all available threads
*/
// [[Rcpp::plugins(cpp23)]]
// [[Rcpp::plugins(openmp)]]

#include "utilities_Package.h"
#include <Rcpp.h>
#ifdef _OPENMP
#include <omp.h>
#include <thread>
#include <chrono>
#endif

static bool use_openmp_flag = false;
static int number_threads   = -1;

//' Enable or Disable OpenMP Parallelization
//'
//' This function allows you to enable or disable the use of OpenMP for parallelizing computations.
//'
//' @param value A <[logical]> value of [length] 1 (Default: [FALSE]). If [length], OpenMP will be used to parallelize computations.
//'
//' @family Utils
//'
//' @examples
//' \dontrun{
//' setUseOpenMP(TRUE)
//' }
//'
//' @export
// [[Rcpp::export]]
void setUseOpenMP(bool value = false) {
    #ifdef _OPENMP
        use_openmp_flag = value;
        Rcpp::Rcout << "OpenMP usage set to: " << (use_openmp_flag ? "enabled" : "disabled") << std::endl;
    #else
        use_openmp_flag = false; 
        Rcpp::Rcout << "OpenMP not available!" << std::endl;
    #endif
}

bool getUseOpenMP() {
    return use_openmp_flag;
}

//' Set the Number of Threads for Parallel Computations
//'
//' This function sets the number of threads to be used for parallel computations. If set to `-1`, all available threads will be utilized.
//'
//' @param value An <[integer]> specifying the number of threads to use (Default: -1). Default is `-1`, which uses all available threads.
//'
//' @family Utils
//'
//' @examples
//' \dontrun{
//' setNumberThreads(4)
//' }
//'
//' @export
// [[Rcpp::export]]
void setNumberThreads(int value = -1) {
    #ifdef _OPENMP
        if (value == -1) {
            // Retrieve the number of available processors (cores)
            number_threads = omp_get_num_procs();
            // Set the number of threads to the total available cores
            omp_set_num_threads(number_threads);
            Rcpp::Rcout << "Number of threads set to: All (" << number_threads << " threads)" << std::endl;
        } else {
            // Set the number of threads to the specified value
            number_threads = value;
            omp_set_num_threads(number_threads);
            Rcpp::Rcout << "Number of threads set to: " << number_threads << std::endl;
        }
    #else
        Rcpp::Rcout << "OpenMP is not available. Number of threads not set." << std::endl;
    #endif
}