#ifndef REGRESSION_CONCORDANCE_CORRELATION_COEFFICIENT_H
#define REGRESSION_CONCORDANCE_CORRELATION_COEFFICIENT_H

#include "utilities_COV.h" 
#include <cstddef>          
#include <cmath>            

#ifdef _OPENMP
    #include <omp.h>
#endif

class CCC {
public:
    /**
     * Compute unweighted CCC.
     *
     * @param actual     Pointer to array of length n
     * @param predicted  Pointer to array of length n
     * @param n          Number of observations
     * @param correction If true, apply factor (n - 1) / n to sxx, syy, sxy
     * @return           The Concordance Correlation Coefficient (unweighted)
     */
    static double compute(const double* actual,
                          const double* predicted,
                          std::size_t n,
                          bool correction)
    {
        
        CovarianceResult<int> covRes = CovarianceCalculator::cov_unweighted(
            actual,
            predicted,
            static_cast<int>(n),
            /*center=*/true,
            /*unbiased=*/true
        );

        if (correction) {
            // factor = (n - 1)/n
            double factor = (static_cast<double>(covRes.n) - 1.0) / static_cast<double>(covRes.n);
            covRes.sxx *= factor;
            covRes.syy *= factor;
            covRes.sxy *= factor;
        }

        double meanDiff   = covRes.xCenter - covRes.yCenter;
        double numerator   = 2.0 * covRes.sxy;
        double denominator = covRes.sxx + covRes.syy + (meanDiff * meanDiff);

        return numerator / denominator;
    }

    /**
     * Compute weighted CCC.
     *
     * @param actual     Pointer to array of length n
     * @param predicted  Pointer to array of length n
     * @param weights    Pointer to array of length n
     * @param n          Number of observations
     * @param correction If true, apply factor (wSum - 1)/wSum to sxx, syy, sxy
     * @return           The Concordance Correlation Coefficient (weighted)
     */
    static double compute(const double* actual,
                          const double* predicted,
                          const double* weights,
                          std::size_t n,
                          bool correction)
    {

        CovarianceResult<double> covRes = CovarianceCalculator::cov_weighted(
            actual,
            predicted,
            weights,
            static_cast<int>(n),
            /*center=*/true,
            /*unbiased=*/true
        );

        if (correction) {
            double wSum = covRes.n;
            double factor = (wSum - 1.0) / wSum;

            covRes.sxx *= factor;
            covRes.syy *= factor;
            covRes.sxy *= factor;
        }

        double meanDiff   = covRes.xCenter - covRes.yCenter;
        double numerator   = 2.0 * covRes.sxy;
        double denominator = covRes.sxx + covRes.syy + (meanDiff * meanDiff);

        return numerator / denominator;
    }
};

#endif
