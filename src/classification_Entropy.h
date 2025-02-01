#ifndef CLASSIFICATION_ENTROPY_H
#define CLASSIFICATION_ENTROPY_H

#include "utilities_Package.h"
#include <Rcpp.h>
#include <cmath>
#include <algorithm>

class ShannonsEntropyClass {
    public:
        static Rcpp::NumericVector Entropy(const double* __restrict pk,
                                        const int n,
                                        const int k, 
                                        const int axis, 
                                        const double base = -1.0) {
            
            const bool adjust_base = (base != -1.0);
            const double log_base = adjust_base ? std::log(base) : 1.0;

            if (adjust_base && (base <= 0 || log_base == 0.0)) {
                Rcpp::stop("Log base cannot be 1 or non-positive.");
            }

            switch (axis) {
                case 1:  return column_entropy(pk, n, k, adjust_base, log_base);
                case 2:  return row_entropy(pk, n, k, adjust_base, log_base);
                default: return total_entropy(pk, n, k, adjust_base, log_base);
            }
        }

    private:
        static Rcpp::NumericVector column_entropy(const double* __restrict pk,
                                                const int n,
                                                const int k,
                                                const bool adjust_base,
                                                const double log_base) {
            Rcpp::NumericVector result(k);

            #pragma omp parallel for if(getUseOpenMP()) schedule(static)
            for (int j = 0; j < k; ++j) {
                const double* pk_col = pk + j * n;
                double sum = 0.0;

                #pragma omp simd reduction(+:sum)
                    for (int i = 0; i < n; ++i) {
                        sum += pk_col[i];
                    }

                    if (sum <= 0.0) {
                        result[j] = R_NaN;
                        continue;
                    }

                const double inv_sum = 1.0 / sum;
                double entropy = 0.0;

                #pragma omp simd reduction(+:entropy)
                    for (int i = 0; i < n; ++i) {
                        const double p = pk_col[i] * inv_sum;
                        entropy += (p > 0.0) ? (-p * std::log(p)) : 0.0;
                    }

                if (adjust_base) entropy /= log_base;

                result[j] = entropy;
            }

            return result;
        }

        static Rcpp::NumericVector row_entropy(const double* __restrict pk,
                                            const int n,
                                            const int k,
                                            const bool adjust_base,
                                            const double log_base) {

            Rcpp::NumericVector result(n);

            #pragma omp parallel for if(getUseOpenMP()) schedule(static)
                for (int i = 0; i < n; ++i) {
                    double sum = 0.0;

                    for (int j = 0; j < k; ++j) {
                        sum += pk[i + j * n];
                    }

                    if (sum <= 0.0) {
                        result[i] = R_NaN;
                        continue;
                    }

                    const double inv_sum = 1.0 / sum;
                    double entropy = 0.0;

                    for (int j = 0; j < k; ++j) {
                        const double p = pk[i + j * n] * inv_sum;
                        if (p > 0.0) {
                            entropy -= p * std::log(p);
                        }
                    }

                    if (adjust_base) entropy /= log_base;
                    result[i] = entropy;
                }

            return result;
        }

        static Rcpp::NumericVector total_entropy(const double* __restrict pk,
                                                const int n,
                                                const int k,
                                                const bool adjust_base,
                                                const double log_base) {
            const int total = n * k;
            double sum = 0.0;

            #pragma omp simd reduction(+:sum)
                for (int i = 0; i < total; ++i) {
                    sum += pk[i];
                }

                if (sum <= 0.0) {
                    return Rcpp::NumericVector::create(R_NaN);
                }

            const double inv_sum = 1.0 / sum;
            double entropy = 0.0;

            #pragma omp parallel for reduction(+:entropy) if(getUseOpenMP()) schedule(static)
                for (int i = 0; i < total; ++i) {
                    const double p = pk[i] * inv_sum;
                    entropy += (p > 0.0) ? (-p * std::log(p)) : 0.0;
                }

            if (adjust_base) entropy /= log_base;

            return Rcpp::NumericVector::create(entropy);
        }
};

#endif // CLASSIFICATION_ENTROPY_H