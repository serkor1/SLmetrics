#ifndef UTILITIES_PACKAGE_H
#define UTILITIES_PACKAGE_H

#include <Rcpp.h>

// Enable OpenMP
#ifdef _OPENMP
    #include <omp.h>
#endif

bool enable_openmp();
bool disable_openmp();
bool getUseOpenMP();

#endif
