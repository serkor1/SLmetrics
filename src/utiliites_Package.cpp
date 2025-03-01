// [[Rcpp::plugins(cpp23)]]
// [[Rcpp::plugins(openmp)]]
#include "utilities_Package.h"
#include <Rcpp.h>
#include <algorithm>
#include <execution>
#include <functional>

#ifdef _OPENMP
    #include <omp.h>
    #include <thread>
    #include <chrono>
#endif

using namespace Rcpp;

static bool use_openmp_flag = false;
static int number_threads   = -1;


bool getUseOpenMP() {
    return use_openmp_flag;
}

// [[Rcpp::export(.enable_openmp)]]
bool enable_openmp()
{
    #ifdef _OPENMP // 1) If OpenMP is available
        // 1.1) set OpenMP flag
        // accordingly
        use_openmp_flag = true;

        // 1.2) return the
        // value to R
        return true;
    #else // 2) If OpenMP is unavailable

        // 2.1) set OpenMP flag
        // accordingly
        // NOTE: Has to be false
        use_openmp_flag = false;

        // 2.2) return the value
        // to R
        return R_NilValue;
    #endif
}

// [[Rcpp::export(.disable_openmp)]]
bool disable_openmp()
{
    #ifdef _OPENMP // 1) If OpenMP is available
        // 1.1) set OpenMP flag
        // accordingly
        use_openmp_flag = false;
        return false;
    #else // 2) If OpenMP is unavailable

        // 2.1) set OpenMP flag
        // accordingly
        // NOTE: Has to be false
        use_openmp_flag = false;
        return R_NilValue;
    #endif
}

// [[Rcpp::export(.available_threads)]]
int available_threads() {
    #ifdef _OPENMP
        return omp_get_num_procs();
    #else
        return 1;
    #endif
}

// [[Rcpp::export(.use_threads)]]
int use_threads(int value = -1) {
    #ifdef _OPENMP
        if (value == -1) {
            // Retrieve the number of available processors (cores)
            number_threads = omp_get_num_procs();
            // Set the number of threads to the total available cores
            omp_set_num_threads(number_threads);

            return number_threads;
        } else {
            // Set the number of threads to the specified value
            number_threads = value;
            omp_set_num_threads(number_threads);

            return value;
        }
    #else
        return 0;
    #endif
}

/**
 * @brief This function assumes that the matrix columns
 * are independent, and sorts each column independently of
 * of eachother
 */
//' @export
// [[Rcpp::export(sort.matrix)]]
Rcpp::NumericMatrix sort_matrix(
  Rcpp::NumericMatrix x, 
  bool decreasing = false) {

    // 0) extract matrix
    // dimensions for the
    // sorting    
    const int n_rows = x.nrow();
    const int n_cols = x.ncol();
    
    // 1) extract pointer
    // to matrix and loop
    double* data = x.begin();
    if (decreasing) {
      for (int col = 0; col < n_cols; ++col) {
          double* col_begin = data + col * n_rows;
          double* col_end   = col_begin + n_rows;

          std::sort(std::execution::par_unseq, col_begin, col_end, std::greater<>());
      }
    } else {
        for (int col = 0; col < n_cols; ++col) {
            double* col_begin = data + col * n_rows;
            double* col_end   = col_begin + n_rows;

            std::sort(std::execution::par_unseq, col_begin, col_end);
        }
    }

    return x;
}