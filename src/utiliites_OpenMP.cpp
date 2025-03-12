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
    /**
     * @brief set the number of used threads
     * for the parallel process
     */
    inline void set_threads(int threads) {
        #ifdef _OPENMP
            ::omp_set_num_threads(threads);
        #else
            // pretend to do something cool
        #endif
    }

    /**
     * @brief get the number of max available
     * threads. If OpenMP is **not** available
     * it will return -1.
     *
     * NOTE: It is not possible to do this inline
     * so the function here is correct. See commit 
     * 7f1ba7b44a994c75a2c3d106a0e51cb23692bc3b if in doubt
     */
    inline int get_threads() {
        #ifdef _OPENMP
            return ::omp_get_max_threads();
        #else
            return -1;
        #endif
    }
    
    /**
     * @brief this function enables the use of 
     * OpenMP throughout the package. It will return the value
     * TRUE if it is successful; ie. if OpenMP is available.
     */
    inline bool enable() {
        bool value;
        #ifdef _OPENMP
            use_openmp_flag = true;
            value = true;
        #else
            use_openmp_flag = false;
            value = false;
        #endif
        return value;
    }
    
    /**
     * @brief this function disables the use of 
     * OpenMP throughout the package. It will return the value
     * TRUE if it is successful; ie. if OpenMP is available.
     */
    inline bool disable() {
        use_openmp_flag = false;
        bool value;
        #ifdef _OPENMP
            value = true;
        #else
            value = false;
        #endif
        return value;
        
    }

    /**
     * @brief check OpenMP
     * availability on the system.
     *
     * @returns true, if its available. false otherwise.
     *
     * NOTE: It is not possible to do this inline
     * so the function here is correct. See commit 
     * 7f1ba7b44a994c75a2c3d106a0e51cb23692bc3b if in doubt
     */
    inline bool available() {
        bool value;
        #ifdef _OPENMP
            value = true;
        #else
            value = false;
        #endif
        return value;
    }

}

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
