#include "SLmetrics.h"

// [[Rcpp::export(.openmp_available)]]
bool openmp_available() {
    return omp::available();
}

// [[Rcpp::export(.enable_openmp)]]
bool enable_openmp()
{
    return omp::enable();
}

// [[Rcpp::export(.disable_openmp)]]
bool disable_openmp()
{
    return omp::disable();
}

// [[Rcpp::export(.available_threads)]]
int available_threads() {
    return omp::get_threads();
}

// [[Rcpp::export(.use_threads)]]
int use_threads(int value = -1) {
    #ifdef _OPENMP
        if (value == -1) {
            // Retrieve the number of available processors (cores)
            omp::number_threads = omp::get_threads();
            // Set the number of threads to the total available cores
            omp::set_threads(omp::number_threads);

            return omp::number_threads;
        } else {
            // Set the number of threads to the specified value
            omp::number_threads = value;
            omp::set_threads(omp::number_threads);

            return value;
        }
    #else
        return -1;
    #endif
}
