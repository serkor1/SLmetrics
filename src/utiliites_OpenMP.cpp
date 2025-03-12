// [[Rcpp::plugins(cpp23)]]
// [[Rcpp::plugins(openmp)]]
#include "utilities_Package.h"

#include <Rcpp.h>

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


/**
 * @brief This namespace contains the namespace 
 * of the functions needed to do basic parallelization
 * setup
 */
namespace omp 
{

    void set_threads(int threads) {
        #ifdef _OPENMP
            ::omp_set_num_threads(threads);
        #else
            // pretend to do something cool
        #endif
    }

    int get_threads() {
        #ifdef _OPENMP
            return ::omp_get_max_threads();
        #else
            return -1;
        #endif
    }

    void enable() {
        use_openmp_flag = true;
    }

    void disable() {
        use_openmp_flag = false;
    }

}



// [[Rcpp::export(.enable_openmp)]]
bool enable_openmp()
{
    #ifdef _OPENMP // 1) If OpenMP is available
        // 1.1) set OpenMP flag
        // accordingly
        omp::enable();

        // 1.2) return the
        // value to R
        return true;
    #else // 2) If OpenMP is unavailable

        // 2.1) set OpenMP flag
        // accordingly
        // NOTE: Has to be false
        omp::disable();

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
        omp::disable();

        return false;
    #else // 2) If OpenMP is unavailable

        // 2.1) set OpenMP flag
        // accordingly
        // NOTE: Has to be false
        omp::disable();

        return R_NilValue;
    #endif
}

// [[Rcpp::export(.available_threads)]]
int available_threads() {
    #ifdef _OPENMP
        return omp_get_num_procs();
    #else
        return -1;
    #endif
}

// [[Rcpp::export(.use_threads)]]
int use_threads(int value = -1) {
    #ifdef _OPENMP
        if (value == -1) {
            // Retrieve the number of available processors (cores)
            number_threads = omp::get_threads();
            // Set the number of threads to the total available cores
            omp::set_threads(number_threads);

            return number_threads;
        } else {
            // Set the number of threads to the specified value
            number_threads = value;
            omp::set_threads(number_threads);

            return value;
        }
    #else
        return -1;
    #endif
}
