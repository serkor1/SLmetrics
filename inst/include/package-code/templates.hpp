/**
 * @file templates.hpp
 * @brief Defines template specializations for Rcpp vector types.
 *
 * This file provides a mechanism to map a C++ numeric type (e.g. int or double)
 * to the corresponding Rcpp vector type (IntegerVector or NumericVector).
 */
#ifndef templates_hpp
#define templates_hpp

#include <RcppArmadillo.h>

template <typename T>
struct vctr;

template <>
struct vctr<double> {
    using type = Rcpp::NumericVector;
};

template <>
struct vctr<int> {
    using type = Rcpp::IntegerVector;
};

// Define a convenient alias.
template <typename T>
using vctr_t = typename vctr<T>::type;

#endif