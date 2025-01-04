#ifndef UTILITIES_PACKAGE_H
#define UTILITIES_PACKAGE_H

// Enable OpenMP
#ifdef _OPENMP
#include <omp.h>
#endif

void setUseOpenMP(bool value);
bool getUseOpenMP();

#endif
