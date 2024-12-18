#ifndef REGRESSION_UTILS_H
#define REGRESSION_UTILS_H

#include <vector>
#include <cmath>
#include <cstddef>
#include <limits>
#include <functional>

/**
 * Base class for regression utilities. This allows derived classes to
 * implement their own metric computations using standardized infrastructure
 * for both weighted and unweighted calculations.
 */
class RegressionBase {
public:
    virtual double compute(const std::vector<double>& actual,
                           const std::vector<double>& predicted) const {
        return 0.0;
    }

    virtual double compute(const std::vector<double>& actual,
                           const std::vector<double>& predicted,
                           const std::vector<double>& weights) const {
        return 0.0;
    }

    virtual ~RegressionBase() = default;

protected:
    // Template for unweighted calculation
    template <typename ErrorFunction>
    static double calculate(const std::vector<double>& actual,
                            const std::vector<double>& predicted,
                            ErrorFunction errorFunc) 
    {
        const std::size_t n = actual.size();

        const double* actual_ptr = actual.data();
        const double* predicted_ptr = predicted.data();

        double output = 0.0;
        std::size_t i = 0;

        // Loop unrolling for efficiency
        std::size_t unroll_limit = n - (n % 4);
        for (; i < unroll_limit; i += 4) {
            output += errorFunc(*actual_ptr++, *predicted_ptr++);
            output += errorFunc(*actual_ptr++, *predicted_ptr++);
            output += errorFunc(*actual_ptr++, *predicted_ptr++);
            output += errorFunc(*actual_ptr++, *predicted_ptr++);
        }

        // Process remaining elements
        for (; i < n; ++i) {
            output += errorFunc(*actual_ptr++, *predicted_ptr++);
        }

        return output / static_cast<double>(n);
    }

    // Template for weighted calculation
    template <typename ErrorFunction>
    static double calculate(const std::vector<double>& actual,
                            const std::vector<double>& predicted,
                            const std::vector<double>& weights,
                            ErrorFunction errorFunc) 
    {
        const std::size_t n = actual.size();

        const double* actual_ptr = actual.data();
        const double* predicted_ptr = predicted.data();
        const double* weights_ptr = weights.data();

        double numerator = 0.0;
        double denominator = 0.0;
        std::size_t i = 0;

        // Loop unrolling for efficiency
        std::size_t unroll_limit = n - (n % 4);
        for (; i < unroll_limit; i += 4) {
            const double& w1 = *weights_ptr++;
            const double& w2 = *weights_ptr++;
            const double& w3 = *weights_ptr++;
            const double& w4 = *weights_ptr++;

            numerator += errorFunc(*actual_ptr++, *predicted_ptr++) * w1;
            denominator += w1;

            numerator += errorFunc(*actual_ptr++, *predicted_ptr++) * w2;
            denominator += w2;

            numerator += errorFunc(*actual_ptr++, *predicted_ptr++) * w3;
            denominator += w3;

            numerator += errorFunc(*actual_ptr++, *predicted_ptr++) * w4;
            denominator += w4;
        }

        // Process remaining elements
        for (; i < n; ++i) {
            const double& weight = *weights_ptr++;
            numerator += errorFunc(*actual_ptr++, *predicted_ptr++) * weight;
            denominator += weight;
        }

        return numerator / denominator;
    }
};

#endif // REGRESSION_UTILS_H