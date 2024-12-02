//
// Created by serko on 09/10/2024.
//

#ifndef REGRESSION_MEANSQUAREDERROR_H
#define REGRESSION_MEANSQUAREDERROR_H
#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// Unweighted MSE
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted)
{
    const std::size_t n = actual.size();

    const double* actual_ptr = actual.begin();
    const double* predicted_ptr = predicted.begin();

    double output = 0.0;
    int i = 0;
    int limit = n - (n % 4);

    for (; i < limit; i += 4) {
        double diff0 = *(actual_ptr++) - *(predicted_ptr++);
        double diff1 = *(actual_ptr++) - *(predicted_ptr++);
        double diff2 = *(actual_ptr++) - *(predicted_ptr++);
        double diff3 = *(actual_ptr++) - *(predicted_ptr++);

        output += diff0 * diff0;
        output += diff1 * diff1;
        output += diff2 * diff2;
        output += diff3 * diff3;
    }

    for (; i < n; ++i) {
        double diff = *(actual_ptr++) - *(predicted_ptr++);
        output += diff * diff;
    }

    return output / n;
}

// Weighted MSE
inline __attribute__((always_inline)) double _metric_(const NumericVector& actual, const NumericVector& predicted, const NumericVector& w)
{
    const std::size_t n = actual.size();

    const double* actual_ptr = actual.begin();
    const double* predicted_ptr = predicted.begin();
    const double* w_ptr = w.begin();

    double output = 0.0;
    double weight_sum = 0.0;
    int i = 0;
    int limit = n - (n % 4);

    for (; i < limit; i += 4) {
        double weight0 = *(w_ptr++);
        double weight1 = *(w_ptr++);
        double weight2 = *(w_ptr++);
        double weight3 = *(w_ptr++);

        double diff0 = *(actual_ptr++) - *(predicted_ptr++);
        double diff1 = *(actual_ptr++) - *(predicted_ptr++);
        double diff2 = *(actual_ptr++) - *(predicted_ptr++);
        double diff3 = *(actual_ptr++) - *(predicted_ptr++);

        output += weight0 * diff0 * diff0;
        output += weight1 * diff1 * diff1;
        output += weight2 * diff2 * diff2;
        output += weight3 * diff3 * diff3;

        weight_sum += weight0 + weight1 + weight2 + weight3;
    }

    for (; i < n; ++i) {
        double weight = *(w_ptr++);
        double diff = *(actual_ptr++) - *(predicted_ptr++);

        output += weight * diff * diff;
        weight_sum += weight;
    }

    return output / weight_sum;
}



#endif //REGRESSION_MEANSQUAREDERROR_H
