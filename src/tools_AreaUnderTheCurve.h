#ifndef CLASSIFICATION_AUC_H
#define CLASSIFICATION_AUC_H

#include "SLmetrics.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <numeric>

class AUC  {
    public:

    /**
    @brief The function assumes that x and y 
    are presorted. Otherwise it will be incorrect.
    */
    static double calculate(
        const double* y, 
        const double* x,
        std::size_t   n,
        const int& method = 0,
        const bool& presorted = true) {

            // 0) declare variables
            // for the class
            std::vector<std::size_t> idx;
            bool use_idx = false;
            double area = 0.0;

            // 1) order the data
            // and calculate calculate
            // indices
            if (!presorted) {

                // 1.1) resize the
                // idx-vetor and fill
                // with 0's
                idx.resize(n);
                std::iota(idx.begin(), idx.end(), 0);

                // 1.2) sort by x-values
                // corresponds to idx <- sort(x); y <- y[idx]; x <- x[idx]
                std::sort(idx.begin(), idx.end(),
                        [&](std::size_t a, std::size_t b) {
                            return x[a] < x[b];
                        });

                // 1.3) set use_idx-flag
                // to true
                use_idx = true;
            }

            // 2) calculate area
            // under the curve with 
            // the desired method
            switch (method) {
                // 2.1) Default: Trapezoid
                // method
                default:
                case 0: {
                    if (use_idx) {
                        for (std::size_t i = 1; i < n; ++i) {
                            double width  = x[idx[i]] - x[idx[i - 1]];
                            double height = 0.5 * (y[idx[i]] + y[idx[i - 1]]);
                            area += width * height;
                        }
                    } else {
                        for (std::size_t i = 1; i < n; ++i) {
                            double width  = x[i] - x[i - 1];
                            double height = 0.5 * (y[i] + y[i - 1]);
                            area += width * height;
                        }
                    }
                }
                break;

                // 2.1) Method: Step
                // method (left step)
                case 1: {
                    if (use_idx) {
                        for (std::size_t i = 1; i < n; ++i) {
                            double width  = x[idx[i]] - x[idx[i - 1]];
                            double height = y[idx[i - 1]];
                            area += width * height;
                        }
                    } else {
                        for (std::size_t i = 1; i < n; ++i) {
                            double width  = x[i] - x[i - 1];
                            double height = y[i - 1];
                            area += width * height;
                        }
                    }
                }
                break;
            }
            // Return output
            // as double
            return area;
    }

    private:
        AUC()  = delete;
        ~AUC() = delete;
};

#endif
