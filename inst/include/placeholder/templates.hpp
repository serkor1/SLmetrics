#ifndef templates_hpp
#define templates_hpp

#include <Rcpp.h>

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