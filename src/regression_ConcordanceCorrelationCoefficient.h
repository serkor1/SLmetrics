#ifndef REGRESSION_CONCORDANCE_CORRELATION_CALCULATOR_HPP
#define REGRESSION_CONCORDANCE_CORRELATION_CALCULATOR_HPP

#include <vector>
#include <cmath>
#include "utilities_COV.h"

class ConcordanceCorrelationCalculator {
    public:

        /**
        * Compute the unweighted Concordance Correlation Coefficient (CCC).
        *
        * @param actual     std::vector<double> of observed values
        * @param predicted  std::vector<double> of predicted values
        * @param correction if true, apply the factor (n-1)/n to var/cov
        * @return           the unweighted CCC
        */
        static double computeUnweighted(const std::vector<double>& actual,
                                        const std::vector<double>& predicted,
                                        bool correction = false) {

            // 1) Basic checks
            std::size_t n = actual.size();

            // 2) Get unweighted covariance from CovarianceCalculator
            auto covRes = CovarianceCalculator::cov_unweighted(
                actual.data(), 
                predicted.data(), 
                static_cast<int>(n), 
                /*center=*/ true, 
                /*unbiased=*/ true
            );
            // covRes: CovarianceResult<int> => covRes.n = n, sxx, syy, sxy, xCenter, yCenter

            // 3) If correction => multiply sxx, syy, sxy by factor = (n - 1)/n
            //    (matching your original "const double factor = (N - 1)/N")
            if (correction) {
                double factor = (static_cast<double>(covRes.n) - 1.0) / 
                                static_cast<double>(covRes.n);
                covRes.sxx *= factor;
                covRes.syy *= factor;
                covRes.sxy *= factor;
            }

            // 4) Mean difference
            double meanDiff = covRes.xCenter - covRes.yCenter;

            // 5) CCC formula:  (2 * covariance) / (var_x + var_y + mean_diff^2)
            double numerator   = 2.0 * covRes.sxy;
            double denominator = covRes.sxx + covRes.syy + (meanDiff * meanDiff);

            return numerator / denominator;
        }

        /**
        * Compute the weighted Concordance Correlation Coefficient (CCC).
        *
        * @param actual     std::vector<double> of observed values
        * @param predicted  std::vector<double> of predicted values
        * @param weights    std::vector<double> of weights (same size)
        * @param correction if true, apply your original factor
        * @return           the weighted CCC
        */
        static double computeWeighted(const std::vector<double>& actual,
                                    const std::vector<double>& predicted,
                                    const std::vector<double>& weights,
                                    bool correction = false) {
            // 1) Basic checks
            std::size_t n = actual.size();

            // 2) Get weighted covariance
            //    CovarianceResult<double> => covRes.n = totalWeight
            auto covRes = CovarianceCalculator::cov_weighted(
                actual.data(),
                predicted.data(),
                weights.data(),
                static_cast<int>(n),
                /*center=*/true,
                /*unbiased=*/true
            );

            if (correction) {
                double n = covRes.n;
                double factor = (n - 1.0) / n;
            
                covRes.sxx *= factor;
                covRes.syy *= factor;
                covRes.sxy *= factor;

                Rcpp::Rcout << "After correction: sxx=" << covRes.sxx << ", syy=" << covRes.syy << ", sxy=" << covRes.sxy << std::endl;
            }

            // 4) Mean difference
            double meanDiff = covRes.xCenter - covRes.yCenter;

            // 5) Weighted CCC formula
            double numerator   = 2.0 * covRes.sxy;
            double denominator = covRes.sxx + covRes.syy + (meanDiff * meanDiff);

            return numerator / denominator;
        }

    private:
        // Prevents the compiler from doing
        // bad stuff.
        ConcordanceCorrelationCalculator()  = delete;
        ~ConcordanceCorrelationCalculator() = delete;
};

#endif
