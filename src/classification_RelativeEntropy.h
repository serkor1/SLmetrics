#ifndef RELATIVE_ENTROPY_CLASS_H
#define RELATIVE_ENTROPY_CLASS_H

#include "utilities_Package.h"
#include <Rcpp.h>
#include <cmath>
#include <vector>
#include <memory>


class RelativeEntropyClass {
public:

    static Rcpp::NumericVector Entropy(const double* __restrict pk,
                                         const double* __restrict qk,
                                         const int n,
                                         const int k,
                                         const int axis,
                                         const double base = -1.0) {
        const bool adjust_base = (base != -1.0);
        const double log_base = adjust_base ? std::log(base) : 1.0;
        if (adjust_base && (base <= 0 || log_base == 0.0)) {
            Rcpp::stop("Invalid logarithm base");
        }
        
        switch (axis) {
            case 1:  return column_entropy(pk, qk, n, k, adjust_base, log_base);
            case 2:  return row_entropy(pk, qk, n, k, adjust_base, log_base);
            default: return total_entropy(pk, qk, n, k, adjust_base, log_base);
        }
    }

private:
    
    static Rcpp::NumericVector column_entropy(const double* __restrict pk,
                                                         const double* __restrict qk,
                                                         const int n,
                                                         const int k,
                                                         const bool adjust_base,
                                                         const double log_base) {
        Rcpp::NumericVector result(k);

        #pragma omp parallel for if(getUseOpenMP()) schedule(static)
        for (int j = 0; j < k; ++j) {

            const double* pk_col = pk + j * n;
            const double* qk_col = qk + j * n;

            double sum_pk = 0.0, sum_qk = 0.0;
            #pragma omp simd reduction(+:sum_pk, sum_qk)
            for (int i = 0; i < n; ++i) {
                sum_pk += pk_col[i];
                sum_qk += qk_col[i];
            }


            if (sum_pk <= 0.0 || sum_qk <= 0.0) {
                result[j] = R_NaN;
                continue;
            }

            const double inv_sum_pk = 1.0 / sum_pk;
            const double inv_sum_qk = 1.0 / sum_qk;
            double entropy = 0.0;
            #pragma omp simd reduction(+:entropy)
            for (int i = 0; i < n; ++i) {
                double p = pk_col[i] * inv_sum_pk;
                double q = qk_col[i] * inv_sum_qk;
                if (p > 0.0 && q > 0.0) {
                    entropy += p * (std::log(p) - std::log(q));
                }
            }
            if (adjust_base) entropy /= log_base;
            result[j] = entropy;
        }

        return result;
    }


    static Rcpp::NumericVector row_entropy(const double* __restrict pk,
                                                      const double* __restrict qk,
                                                      const int n,
                                                      const int k,
                                                      const bool adjust_base,
                                                      const double log_base) {
        Rcpp::NumericVector result(n);

        #pragma omp parallel for if(getUseOpenMP()) schedule(static)
        for (int i = 0; i < n; ++i) {
            double sum_pk = 0.0, sum_qk = 0.0;
            for (int j = 0; j < k; ++j) {
                sum_pk += pk[i + j * n];
                sum_qk += qk[i + j * n];
            }

            if (sum_pk <= 0.0 || sum_qk <= 0.0) {
                result[i] = R_NaN;
                continue;
            }

            const double inv_sum_pk = 1.0 / sum_pk;
            const double inv_sum_qk = 1.0 / sum_qk;
            double entropy = 0.0;
            for (int j = 0; j < k; ++j) {
                double p = pk[i + j * n] * inv_sum_pk;
                double q = qk[i + j * n] * inv_sum_qk;
                if (p > 0.0 && q > 0.0) {
                    entropy += p * (std::log(p) - std::log(q));
                }
            }

            if (adjust_base) entropy /= log_base;
            result[i] = entropy;
        }
        return result;
    }

    
    static Rcpp::NumericVector total_entropy(const double* __restrict pk,
                                                        const double* __restrict qk,
                                                        const int n,
                                                        const int k,
                                                        const bool adjust_base,
                                                        const double log_base) {
        const int total = n * k;
        double sum_pk = 0.0, sum_qk = 0.0;
        #pragma omp simd reduction(+:sum_pk, sum_qk)
            for (int i = 0; i < total; ++i) {
                sum_pk += pk[i];
                sum_qk += qk[i];
            }

        if (sum_pk <= 0.0 || sum_qk <= 0.0) {
            return Rcpp::NumericVector::create(R_NaN);
        }

        const double inv_sum_pk = 1.0 / sum_pk;
        const double inv_sum_qk = 1.0 / sum_qk;
        double entropy = 0.0;
        #pragma omp parallel for reduction(+:entropy) if(getUseOpenMP()) schedule(static)
            for (int i = 0; i < total; ++i) {
                double p = pk[i] * inv_sum_pk;
                double q = qk[i] * inv_sum_qk;
                if (p > 0.0 && q > 0.0) {
                    entropy += p * (std::log(p) - std::log(q));
                }
            }

        if (adjust_base) entropy /= log_base;
        return Rcpp::NumericVector::create(entropy);
    }
};

#endif
