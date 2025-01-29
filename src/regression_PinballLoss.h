#ifndef REGRESSION_PINBALLLOSS_H
#define REGRESSION_PINBALLLOSS_H

#include "utilities_Package.h"
#include <cstddef>             
#include <cmath>                
#include <algorithm>            
#include <numeric>              
#include <vector>

#ifdef _OPENMP
    #include <omp.h>
#endif

class PinballLoss {
public:
    /**
     * Unweighted pinball loss:
     * 
     * Loss = (1/n) * sum_{i=1..n}  [ (alpha * (a_i - p_i))         if a_i >= p_i
     *                                ((1 - alpha) * (p_i - a_i))   if a_i <  p_i ]
     *
     * @param actual    Pointer to actual data
     * @param predicted Pointer to predicted data
     * @param n         Number of elements
     * @param alpha     Quantile level in [0, 1]
     */
    static double compute(const double* actual,
                          const double* predicted,
                          std::size_t n,
                          double alpha)
    {
        double sumLoss = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sumLoss) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double diff = actual[i] - predicted[i];
            if (diff >= 0.0) {
                sumLoss += alpha * diff;
            } else {
                sumLoss += (1.0 - alpha) * (-diff);
            }
        }

        return sumLoss / static_cast<double>(n);
    }

    /**
     * Weighted pinball loss:
     *
     * Loss = sum_{i=1..n} [ w_i * L(a_i, p_i) ] / sum_{i=1..n} w_i,
     * where L(a, p) is the same piecewise function as above.
     *
     * @param actual    Pointer to actual data
     * @param predicted Pointer to predicted data
     * @param weights   Pointer to weights
     * @param n         Number of elements
     * @param alpha     Quantile level in [0, 1]
     */
    static double compute(const double* actual,
                          const double* predicted,
                          const double* weights,
                          std::size_t n,
                          double alpha)
    {
        double sumLoss = 0.0;
        double sumW    = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sumLoss, sumW) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double w    = weights[i];
            double diff = actual[i] - predicted[i];
            double val  = (diff >= 0.0)
                            ? (alpha * diff)
                            : ((1.0 - alpha) * -diff);

            sumLoss += w * val;
            sumW    += w;
        }

        return sumLoss / sumW;
    }

    /**
     * Compute pinball loss for a single constant prediction `c`.
     * (Unweighted)
     *
     * @param actual Pointer to actual data
     * @param n      Number of elements
     * @param alpha  Quantile level
     * @param c      The constant predicted value
     */
    static double computeConstantPred(const double* actual,
                                      std::size_t n,
                                      double alpha,
                                      double c)
    {
        double sumLoss = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sumLoss) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double diff = actual[i] - c;
            if (diff >= 0.0) {
                sumLoss += alpha * diff;
            } else {
                sumLoss += (1.0 - alpha) * (-diff);
            }
        }

        return sumLoss / static_cast<double>(n);
    }

    /**
     * Compute pinball loss for a single constant prediction `c`.
     * (Weighted)
     *
     * @param actual  Pointer to actual data
     * @param weights Pointer to weights
     * @param n       Number of elements
     * @param alpha   Quantile level
     * @param c       The constant predicted value
     */
    static double computeConstantPred(const double* actual,
                                      const double* weights,
                                      std::size_t n,
                                      double alpha,
                                      double c)
    {
        double sumLoss = 0.0;
        double sumW    = 0.0;

        #ifdef _OPENMP
            #pragma omp parallel for reduction(+:sumLoss, sumW) if(getUseOpenMP())
        #endif
        for (std::size_t i = 0; i < n; ++i) {
            double w    = weights[i];
            double diff = actual[i] - c;
            double val  = (diff >= 0.0)
                            ? (alpha * diff)
                            : ((1.0 - alpha) * -diff);

            sumLoss += w * val;
            sumW    += w;
        }

        return sumLoss / sumW;
    }

    static double quantile(const double* x,
                           std::size_t n,
                           double alpha)
    {
        // Create an index array [0..n-1]
        std::vector<std::size_t> idx(n);
        for (std::size_t i = 0; i < n; ++i) {
            idx[i] = i;
        }

        // Sort indices by x[idx[i]]
        std::sort(idx.begin(), idx.end(),
                  [&](std::size_t a, std::size_t b) {
                      return x[a] < x[b];
                  });

        // Position in the sorted array
        double pos = alpha * (n - 1);
        std::size_t lower_i = static_cast<std::size_t>(pos);
        std::size_t upper_i = (lower_i + 1 < n) ? (lower_i + 1) : (n - 1);
        double frac = pos - static_cast<double>(lower_i);

        double lower_val = x[idx[lower_i]];
        double upper_val = x[idx[upper_i]];

        return lower_val + frac * (upper_val - lower_val);
    }

    static double quantile(const double* x,
                           const double* w,
                           std::size_t n,
                           double alpha)
    {
        // Create an index array [0..n-1]
        std::vector<std::size_t> idx(n);
        for (std::size_t i = 0; i < n; ++i) {
            idx[i] = i;
        }

        // Sort indices by the underlying value x[idx]
        std::sort(idx.begin(), idx.end(),
                  [&](std::size_t a, std::size_t b) {
                      return x[a] < x[b];
                  });

        // Total weight
        double totalW = 0.0;
        for (std::size_t i = 0; i < n; ++i) {
            totalW += w[i];
        }

        double target = alpha * totalW;
        double cumW   = 0.0;
        double lower_val = 0.0, upper_val = 0.0;
        bool found_lower = false;

        for (std::size_t i = 0; i < n; ++i) {
            std::size_t ndx  = idx[i];
            cumW += w[ndx];

            // The moment we cross target, store 'lower_val'
            if (!found_lower && cumW >= target) {
                lower_val   = x[ndx];
                found_lower = true;
            }
            // We store 'upper_val' as well
            if (cumW >= target) {
                upper_val = x[ndx];
                break;
            }
        }

        return lower_val; 
    }
};

#endif // REGRESSION_PINBALLLOSS_H
