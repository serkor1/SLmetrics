#ifndef REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H
#define REGRESSION_RELATIVEROOTMEANSQUAREDERROR_H

#include <Rcpp.h>
#include "utilities_Package.h"
#include <cmath>
#include <cstddef>
#include <algorithm>
#include <vector>

#ifdef _OPENMP
  #include <omp.h>
#endif

class RRMSE {
    public:

        /**
        * Compute unweighted RRMSE in one pass for RMSE, plus partial pass for IQR if needed.
        *
        * Normalization:
        *   0 -> Mean
        *   1 -> Range
        *   2 -> IQR
        *   default -> 1.0 (no normalization)
        *
        * @param actual      Pointer to array of actual values
        * @param predicted   Pointer to array of predicted values
        * @param n           Number of elements
        * @param normalization  Normalization approach
        */
        static double compute(const double* actual,
                            const double* predicted,
                            std::size_t n,
                            int normalization)
        {
            double sumSq   = 0.0;
            double sumVals = 0.0;
            double minVal  = actual[0];
            double maxVal  = actual[0];

            #ifdef _OPENMP
            if (getUseOpenMP()) {
                #pragma omp parallel
                {
                    double localSumSq   = 0.0;
                    double localSumVals = 0.0;
                    double localMinVal  = actual[0];
                    double localMaxVal  = actual[0];

                    #pragma omp for nowait
                    for (std::size_t i = 0; i < n; ++i) {
                        double diff = actual[i] - predicted[i];
                        localSumSq   += diff * diff;
                        localSumVals += actual[i];
                        if (actual[i] < localMinVal) localMinVal = actual[i];
                        if (actual[i] > localMaxVal) localMaxVal = actual[i];
                    }
                    #pragma omp critical
                    {
                        sumSq   += localSumSq;
                        sumVals += localSumVals;
                        if (localMinVal < minVal) minVal = localMinVal;
                        if (localMaxVal > maxVal) maxVal = localMaxVal;
                    }
                }
            } else
            #endif
            {
                // Serial fallback
                for (std::size_t i = 0; i < n; ++i) {
                    double diff = actual[i] - predicted[i];
                    sumSq   += diff * diff;
                    sumVals += actual[i];
                    if (actual[i] < minVal) minVal = actual[i];
                    if (actual[i] > maxVal) maxVal = actual[i];
                }
            }

            // 2) Compute RMSE
            double rmse = std::sqrt(sumSq / static_cast<double>(n));

            // 3) Compute normalization factor
            double normFactor = 1.0;
            switch (normalization) {
            case 0: // mean
                normFactor = sumVals / static_cast<double>(n);
                break;

            case 1: // range
                normFactor = (maxVal - minVal);
                break;

            case 2: // IQR -> needs sorting, hence a copy is unavoidable
                normFactor = unweightedIQR(actual, n);
                break;

            default:
                normFactor = 1.0; // no normalization
                break;
            }

            // 4) Return RRMSE
            return rmse / normFactor;
        }


        /**
        * Compute weighted RRMSE.
        *
        * Weighted RMSE = sqrt( sum( w_i*(a_i - p_i)^2 ) / sum(w_i) ).
        * Then divided by the normalization factor (weighted or unweighted, depending on 'normalization').
        *
        * Normalization:
        *   0 -> Weighted Mean
        *   1 -> Range (unweighted)
        *   2 -> Weighted IQR
        *   default -> 1.0
        *
        * @param actual        Pointer to array of actual values
        * @param predicted     Pointer to array of predicted values
        * @param weights       Pointer to array of weights
        * @param n             Number of elements
        * @param normalization Normalization approach
        */

        static double compute(const double* actual,
                            const double* predicted,
                            const double* weights,
                            std::size_t n,
                            int normalization)
        {
            double sumSq     = 0.0;  // sum of w_i * (diff^2)
            double sumW      = 0.0;  // sum of w_i
            double sumWVals  = 0.0;  // sum of w_i * actual_i
            double minVal    = actual[0];
            double maxVal    = actual[0];

            #ifdef _OPENMP
            if (getUseOpenMP()) {
                #pragma omp parallel
                {
                    double localSumSq    = 0.0;
                    double localSumW     = 0.0;
                    double localSumWVals = 0.0;
                    double localMinVal   = actual[0];
                    double localMaxVal   = actual[0];

                    #pragma omp for nowait
                    for (std::size_t i = 0; i < n; ++i) {
                        double w    = weights[i];
                        double diff = actual[i] - predicted[i];
                        localSumSq    += w * diff * diff;
                        localSumW     += w;
                        localSumWVals += w * actual[i];

                        if (actual[i] < localMinVal) localMinVal = actual[i];
                        if (actual[i] > localMaxVal) localMaxVal = actual[i];
                    }

                    #pragma omp critical
                    {
                        sumSq     += localSumSq;
                        sumW      += localSumW;
                        sumWVals  += localSumWVals;
                        if (localMinVal < minVal) minVal = localMinVal;
                        if (localMaxVal > maxVal) maxVal = localMaxVal;
                    }
                }
            } else
            #endif
            {
                // Serial
                for (std::size_t i = 0; i < n; ++i) {
                    double w    = weights[i];
                    double diff = actual[i] - predicted[i];
                    sumSq    += w * diff * diff;
                    sumW     += w;
                    sumWVals += w * actual[i];

                    if (actual[i] < minVal) minVal = actual[i];
                    if (actual[i] > maxVal) maxVal = actual[i];
                }
            }

            // 2) Weighted RMSE
            double rmse = std::sqrt(sumSq / sumW);

            // 3) Compute normalization factor
            double normFactor = 1.0;
            switch (normalization) {
            case 0: // weighted mean
                normFactor = sumWVals / sumW;
                break;

            case 1: // range (unweighted)
                normFactor = (maxVal - minVal);
                break;

            case 2: // weighted IQR -> requires sorting
                normFactor = weightedIQR(actual, weights, n);
                break;

            default:
                normFactor = 1.0; // no normalization
                break;
            }

            // 4) Weighted RRMSE
            return rmse / normFactor;
        }

    private:

        static double unweightedIQR(const double* values, std::size_t n)
        {
            // Copy once (last resort) because we must sort for quantiles:
            std::vector<double> tmp(values, values + n);
            std::sort(tmp.begin(), tmp.end());

            double q1 = unweightedQuantileSorted(tmp, 0.25);
            double q3 = unweightedQuantileSorted(tmp, 0.75);
            return (q3 - q1);
        }


        static double weightedIQR(const double* values,
                                const double* weights,
                                std::size_t n)
        {
            
            std::vector<std::pair<double,double>> vw;
            vw.reserve(n);
            for (std::size_t i = 0; i < n; ++i) {
                vw.emplace_back(values[i], weights[i]);
            }
            
            std::sort(vw.begin(), vw.end(),
                    [](auto &a, auto &b){ return a.first < b.first; });

            double q1 = weightedQuantileSorted(vw, 0.25);
            double q3 = weightedQuantileSorted(vw, 0.75);
            return (q3 - q1);
        }

        static double unweightedQuantileSorted(const std::vector<double> &sortedVals,
                                            double alpha)
        {
            // No checks for n>1, alpha in [0,1], etc., per user request
            std::size_t n = sortedVals.size();
            double pos = alpha * (n - 1);
            std::size_t idxLower = static_cast<std::size_t>(pos);
            std::size_t idxUpper = (idxLower + 1 < n) ? (idxLower + 1) : (n - 1);
            double frac = pos - static_cast<double>(idxLower);

            double valLower = sortedVals[idxLower];
            double valUpper = sortedVals[idxUpper];
            return valLower + (valUpper - valLower) * frac;
        }

        static double weightedQuantileSorted(const std::vector<std::pair<double,double>> &vw,
                                            double alpha)
        {
            // Sum all weights
            double totalW = 0.0;
            for (auto &p : vw) {
                totalW += p.second;
            }
            double target = alpha * totalW;

            double cumW = 0.0;
            double prevVal = vw[0].first;
            for (auto &p : vw) {
                double val = p.first;
                double w   = p.second;
                cumW += w;

                if (cumW >= target) {

                    return val;

                }
                prevVal = val;
            }
            
            return vw.back().first;
        }

    private:
        // Prevents the compiler from doing
        // bad stuff.
        RRMSE()  = delete;
        ~RRMSE() = delete;
};

#endif
