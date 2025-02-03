#ifndef utilities_COV_hpp
#define utilities_COV_hpp

#include "utilities_Package.h" 
#include <cmath>          


template <typename T>
struct CovarianceResult {
    T n;             // number of observations or total weight
    double xCenter;  // x mean (weighted or unweighted)
    double yCenter;  // y mean
    double sxx;      // variance of x
    double syy;      // variance of y
    double sxy;      // covariance of x,y

    inline double corr() const {
        if (sxx > 0.0 && syy > 0.0) {
            return sxy / (std::sqrt(sxx) * std::sqrt(syy));
        }
        return 0.0;
    }
};

class CovarianceCalculator {
    public:
        /**
        * @param x        pointer to array of length n
        * @param y        pointer to array of length n
        * @param n        integer size of arrays
        * @param center   whether to subtract mean
        * @param unbiased whether to use (n-1) denominator
        *
        * @return CovarianceResult<int> (n is an integer)
        */
        static inline CovarianceResult<int> cov_unweighted(
            const double* x,
            const double* y,
            int n,
            bool center   = true,
            bool unbiased = true
        );

        /**
        *
        * @param x        pointer to array of length n
        * @param y        pointer to array of length n
        * @param w        pointer to array of length n
        * @param n        size of arrays
        * @param center   whether to subtract weighted mean
        * @param unbiased whether to apply unbiased correction
        *
        * @return CovarianceResult<double> (n is total weight wSum)
        */
        static inline CovarianceResult<double> cov_weighted(
            const double* x,
            const double* y,
            const double* w,
            int n,
            bool center   = true,
            bool unbiased = true
        );

    private:
        // Prevents the compiler from doing
        // bad stuff.
        CovarianceCalculator()  = delete;
        ~CovarianceCalculator() = delete;

};

inline CovarianceResult<int> CovarianceCalculator::cov_unweighted(
    const double* x,
    const double* y,
    int n,
    bool center,
    bool unbiased) {


        CovarianceResult<int> res;
        res.n = n;


        double xSum = 0.0, ySum = 0.0;
        if (center) {
        #ifdef _OPENMP
                if (getUseOpenMP()) {
                    #pragma omp parallel for reduction(+:xSum,ySum)
                    for (int i = 0; i < n; ++i) {
                        xSum += x[i];
                        ySum += y[i];
                    }
                } else
        #endif
                {
                    // Non-parallel fallback
                    for (int i = 0; i < n; ++i) {
                        xSum += x[i];
                        ySum += y[i];
                    }
                }

                res.xCenter = xSum / static_cast<double>(n);
                res.yCenter = ySum / static_cast<double>(n);
            } else {
                res.xCenter = 0.0;
                res.yCenter = 0.0;
            }

            double sxx = 0.0, syy = 0.0, sxy = 0.0;

        #ifdef _OPENMP
        if (getUseOpenMP()) {
            #pragma omp parallel
            {
                double sxxLocal = 0.0, syyLocal = 0.0, sxyLocal = 0.0;
                #pragma omp for
                for (int i = 0; i < n; ++i) {
                    double xAdj = x[i] - res.xCenter;
                    double yAdj = y[i] - res.yCenter;
                    sxxLocal += xAdj * xAdj;
                    syyLocal += yAdj * yAdj;
                    sxyLocal += xAdj * yAdj;
                }
                #pragma omp critical
                {
                    sxx += sxxLocal;
                    syy += syyLocal;
                    sxy += sxyLocal;
                }
            }
        } else
        #endif
        {
            for (int i = 0; i < n; ++i) {
                double xAdj = x[i] - res.xCenter;
                double yAdj = y[i] - res.yCenter;
                sxx += xAdj * xAdj;
                syy += yAdj * yAdj;
                sxy += xAdj * yAdj;
            }
        }

        // 3) Denominator
        double denom = (unbiased ? (n - 1.0) : static_cast<double>(n));
        res.sxx = sxx / denom;
        res.syy = syy / denom;
        res.sxy = sxy / denom;

        return res;
}


inline CovarianceResult<double> CovarianceCalculator::cov_weighted(
    const double* x,
    const double* y,
    const double* w,
    int n,
    bool center,
    bool unbiased) {
        CovarianceResult<double> res;

        double wSum = 0.0;
        double xAcc = 0.0, yAcc = 0.0;

        #ifdef _OPENMP
        if (getUseOpenMP()) {
            #pragma omp parallel
            {
                double wSumLocal = 0.0;
                double xAccLocal = 0.0;
                double yAccLocal = 0.0;

                #pragma omp for
                for (int i = 0; i < n; ++i) {
                    wSumLocal += w[i];
                    xAccLocal += w[i] * x[i];
                    yAccLocal += w[i] * y[i];
                }
                #pragma omp critical
                {
                    wSum += wSumLocal;
                    xAcc += xAccLocal;
                    yAcc += yAccLocal;
                }
            }
        } else
        #endif
        {
            for (int i = 0; i < n; ++i) {
                wSum     += w[i];
                xAcc     += w[i] * x[i];
                yAcc     += w[i] * y[i];
            }
        }

        if (center && wSum > 0.0) {
            res.xCenter = xAcc / wSum;
            res.yCenter = yAcc / wSum;
        } else {
            res.xCenter = 0.0;
            res.yCenter = 0.0;
        }

        double sxx = 0.0, syy = 0.0, sxy = 0.0;

        #ifdef _OPENMP
        if (getUseOpenMP()) {
            #pragma omp parallel
            {
                double sxxLocal = 0.0, syyLocal = 0.0, sxyLocal = 0.0;
                #pragma omp for
                for (int i = 0; i < n; ++i) {

                    double wNorm = w[i] / wSum;
                    double xAdj  = x[i] - res.xCenter;
                    double yAdj  = y[i] - res.yCenter;

                    sxxLocal += wNorm * xAdj * xAdj;
                    syyLocal += wNorm * yAdj * yAdj;
                    sxyLocal += wNorm * xAdj * yAdj;
                }
                #pragma omp critical
                {
                    sxx += sxxLocal;
                    syy += syyLocal;
                    sxy += sxyLocal;
                }
            }
        } else
        #endif
        {
            for (int i = 0; i < n; ++i) {
                double wNorm = w[i] / wSum;
                double xAdj  = x[i] - res.xCenter;
                double yAdj  = y[i] - res.yCenter;

                sxx += wNorm * xAdj * xAdj;
                syy += wNorm * yAdj * yAdj;
                sxy += wNorm * xAdj * yAdj;
            }
        }

        // 3) Unbiased correction
        if (unbiased) {
            // sum of squares of (wNorm)
            double sumNormW2 = 0.0;
        #ifdef _OPENMP
            if (getUseOpenMP()) {
                double localNorm = 0.0;
                #pragma omp parallel for reduction(+:localNorm)
                for (int i = 0; i < n; ++i) {
                    double wNorm = w[i] / wSum;
                    localNorm += wNorm * wNorm;
                }
                sumNormW2 = localNorm;
            } else
        #endif
            {
                for (int i = 0; i < n; ++i) {
                    double wNorm = w[i] / wSum;
                    sumNormW2 += wNorm * wNorm;
                }
            }
            double denom = 1.0 - sumNormW2;
            if (denom > 0.0) {
                sxx /= denom;
                syy /= denom;
                sxy /= denom;
            }
        }

        // Fill results
        res.sxx = sxx;
        res.syy = syy;
        res.sxy = sxy;

        // store total weight in res.n
        res.n = wSum;

        return res;
}

#endif
