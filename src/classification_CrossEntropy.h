#ifndef CROSS_ENTROPY_CLASS_H
#define CROSS_ENTROPY_CLASS_H

#include "utilities_Package.h"
#include <Rcpp.h>
#include <cmath>
#include <algorithm>

class CrossEntropyClass {
public:
    /*
        Cross Entropy Calculation
        Computes the cross entropy between two probability distributions.
    */
    static Rcpp::NumericVector Entropy(const Rcpp::NumericMatrix& pk,
                                       const Rcpp::NumericMatrix& qk,
                                       const int& axis,
                                       const double& base = -1.0) {
        const int n = pk.nrow();
        const int k = pk.ncol();

        // Precompute log(base) if needed
        double log_base = 0.0;
        bool adjust_base = (base != -1.0);
        if (adjust_base) {
            log_base = std::log(base);
            // Handle the case where base <= 0
            if (log_base == 0.0) {
                Rcpp::stop("Log base cannot be 1 or non-positive.");
            }
        }

        switch (axis) {
            case 1: { // Column-wise
                Rcpp::NumericVector output(k);

                #pragma omp parallel for if(getUseOpenMP()) schedule(static)
                for (int j = 0; j < k; ++j) {
                    double sum_pk = 0.0;
                    double sum_qk = 0.0;

                    // Compute sums for normalization
                    for (int i = 0; i < n; ++i) {
                        sum_pk += pk(i, j);
                        sum_qk += qk(i, j);
                    }

                    double inv_sum_pk = 1.0 / sum_pk;
                    double inv_sum_qk = 1.0 / sum_qk;
                    double cross_entropy = 0.0;

                    // Compute cross entropy for the j-th column
                    for (int i = 0; i < n; ++i) {
                        double p = pk(i, j) * inv_sum_pk;
                        double q = qk(i, j) * inv_sum_qk;
                        if (p > 0.0 && q > 0.0) {
                            cross_entropy -= p * std::log(q);
                        }
                    }

                    // Adjust base if specified
                    if (adjust_base) {
                        cross_entropy /= log_base;
                    }

                    output[j] = cross_entropy;
                }

                return output;
            }

            case 2: { // Row-wise
                Rcpp::NumericVector output(n);

                #pragma omp parallel for if(getUseOpenMP()) schedule(static)
                for (int i = 0; i < n; ++i) {
                    double sum_pk = 0.0;
                    double sum_qk = 0.0;

                    // Compute sums for normalization
                    for (int j = 0; j < k; ++j) {
                        sum_pk += pk(i, j);
                        sum_qk += qk(i, j);
                    }

                    double inv_sum_pk = 1.0 / sum_pk;
                    double inv_sum_qk = 1.0 / sum_qk;
                    double cross_entropy = 0.0;

                    // Compute cross entropy for the i-th row
                    for (int j = 0; j < k; ++j) {
                        double p = pk(i, j) * inv_sum_pk;
                        double q = qk(i, j) * inv_sum_qk;
                        if (p > 0.0 && q > 0.0) {
                            cross_entropy -= p * std::log(q);
                        }
                    }

                    // Adjust base if specified
                    if (adjust_base) {
                        cross_entropy /= log_base;
                    }

                    output[i] = cross_entropy;
                }

                return output;
            }

            default: { // Total (aggregate)
                double sum_pk = 0.0;
                double sum_qk = 0.0;

                // Compute total sums for normalization
                #pragma omp parallel for reduction(+:sum_pk, sum_qk) if(getUseOpenMP()) schedule(static)
                for(int i = 0; i < n; ++i) {
                    for(int j = 0; j < k; ++j) {
                        sum_pk += pk(i, j);
                        sum_qk += qk(i, j);
                    }
                }

                double inv_sum_pk = 1.0 / sum_pk;
                double inv_sum_qk = 1.0 / sum_qk;
                double cross_entropy = 0.0;

                // Compute total cross entropy
                #pragma omp parallel for reduction(+:cross_entropy) if(getUseOpenMP()) schedule(static)
                for(int i = 0; i < n; ++i) {
                    for(int j = 0; j < k; ++j) {
                        double p = pk(i, j) * inv_sum_pk;
                        double q = qk(i, j) * inv_sum_qk;
                        if (p > 0.0 && q > 0.0) {
                            cross_entropy -= p * std::log(q);
                        }
                    }
                }

                // Adjust base if specified
                if (adjust_base) {
                    cross_entropy /= log_base;
                }

                return Rcpp::NumericVector::create(cross_entropy);
            }
        }
    }
};

#endif // CROSS_ENTROPY_CLASS_H
