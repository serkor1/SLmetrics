#ifndef CLASSIFICATION_ENTROPY_H
#define CLASSIFICATION_ENTROPY_H

#include "utilities_Package.h"
#include <Rcpp.h>
#include <cmath>
#include <algorithm>

class ShannonsEntropyClass {
public:

    /*
        Shannon's Entropy
    */

    static Rcpp::NumericVector Entropy(const Rcpp::NumericMatrix& pk, const int& axis, const double& base = -1.0) {

        /*
            Cases:
                1 row-wise
                2 column-wise
                default: Total
        */
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
                    double sum = 0.0;

                    // Compute sum for normalization
                    for (int i = 0; i < n; ++i) {
                        sum += pk(i, j);
                    }

                    double inv_sum = 1.0 / sum;
                    double entropy = 0.0;

                    for (int i = 0; i < n; ++i) {
                        double p = pk(i, j) * inv_sum;
                        if (p > 0.0) {
                            entropy -= p * std::log(p);
                        }
                    }

                    if (adjust_base) {
                        entropy /= log_base;
                    }

                    output[j] = entropy;
                }

                return output;
            }

            case 2: { // Row-wise

                Rcpp::NumericVector output(n);

                #pragma omp parallel for if(getUseOpenMP()) schedule(static)
                for (int i = 0; i < n; ++i) {
                    double sum = 0.0;

                    // Compute sum for normalization
                    for (int j = 0; j < k; ++j) {
                        sum += pk(i, j);
                    }

                    double inv_sum = 1.0 / sum;
                    double entropy = 0.0;

                    for (int j = 0; j < k; ++j) {
                        double p = pk(i, j) * inv_sum;
                        if (p > 0.0) {
                            entropy -= p * std::log(p);
                        }
                    }

                    if (adjust_base) {
                        entropy /= log_base;
                    }

                    output[i] = entropy;
                }

                return output;
            }

            default: { // Total (aggregate)

                double total_sum = 0.0;
                // Compute total sum for normalization
                #pragma omp parallel for reduction(+:total_sum) if(getUseOpenMP()) schedule(static)
                for(int i = 0; i < n; ++i) {
                    for(int j = 0; j < k; ++j) {
                        total_sum += pk(i, j);
                    }
                }

                double inv_total_sum = 1.0 / total_sum;
                double entropy = 0.0;

                // Compute total entropy
                #pragma omp parallel for reduction(+:entropy) if(getUseOpenMP()) schedule(static)
                for(int i = 0; i < n; ++i) {
                    for(int j = 0; j < k; ++j) {
                        double p = pk(i, j) * inv_total_sum;
                        if (p > 0.0) {
                            entropy -= p * std::log(p);
                        }
                    }
                }

                if (adjust_base) {
                    entropy /= log_base;
                }

                return Rcpp::NumericVector::create(entropy);
            }

        }
    }
};

#endif // CLASSIFICATION_ENTROPY_H
