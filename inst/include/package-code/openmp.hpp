/**
 * @brief openmp.hpp
 * Implement OpenMP support across the entire library
 *
 */
#ifdef _OPENMP
    #include <omp.h>
    #include <thread>
    #include <chrono>
#endif

namespace omp {
    /**
     * Default parallel
     * execution value: false
     *
     * Keep one core available
     */
     static bool use_openmp = false;

     #ifdef _OPENMP
        static int number_threads = ::omp_get_max_threads() - 1;
     #else
        static int number_threads = -1;
     #endif
     
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
            use_openmp = true;
            value = true;
        #else
            use_openmp = false;
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
        use_openmp = false;
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
