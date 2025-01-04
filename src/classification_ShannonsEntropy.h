#ifndef CLASSIFICATION_ENTROPY_H
#define CLASSIFICATION_ENTROPY_H

#include "utilities_Package.h"
#include <Rcpp.h>
#include <cmath>
#include <algorithm>
#include <optional>

class ShannonsEntropyClass {
    public:

        /*
            Shannons Entropy
        */

        static Rcpp::NumericVector Entropy(const Rcpp::NumericMatrix& pk, const int& axis, const double& base = -1.0) {
            
            /*
                Cases:
                    1 row-wise
                    2 column-wise
                    default: Total
            */
             // 2) Calculate the sum for normalization
            double sum = 0.0;

            const int& n = pk.nrow();
            const int& k = pk.ncol();

            switch (axis) {
                case 1: {

                    Rcpp::NumericVector output(k);

                    #pragma omp parallel for if (getUseOpenMP())
                    for (int j = 0; j < k; ++j) {
                        double sum = 0.0;
                            for (int i = 0; i < n; ++i) {
                            sum += pk(i, j);
                        }

                        double entropy = 0.0;                   
                        for (int i = 0; i < n; ++i) {
                            double p = pk(i, j) / sum;
                            if (p > 0) {
                                entropy -= p * std::log(p);
                            }
                        }

                        if (base != -1) 
                        {
                            entropy /= std::log(base);
                        }

                        output[j] = entropy;
                    }

                    return output;

                }

                case 2: {

                    Rcpp::NumericVector output(n);

                    #pragma omp parallel for if (getUseOpenMP())
                    for (int i = 0; i < n; ++i) {

                        double sum = 0.0;
                        for (int j = 0; j < k; ++j) {
                            sum += pk(i, j);
                        } 
                        double entropy = 0.0;
                        for (int j = 0; j < k; ++j) {
                            double p = pk(i, j) / sum;
                            if (p > 0) {
                                entropy -= p * std::log(p);
                            }
                        }

                        if (base != -1) {
                            entropy /= std::log(base);
                        }

                        output[i] = entropy;
                    }

                    return output;
                }
                    

                    
                default: {

                    double entropy = 0.0;

                    #pragma omp parallel for reduction(+:sum) if (getUseOpenMP())
                    for(int i = 0; i < n; ++i) {
                        for(int j = 0; j < k; ++j) {
                            sum += pk(i, j);
                        }
                    }

                    #pragma omp parallel for reduction(+:entropy) if (getUseOpenMP())
                    for(int i = 0; i < n; ++i) {
                        for(int j = 0; j < k; ++j) {
                            double p = pk(i, j) / sum;
                            entropy -= p * std::log(p);
                        }
                    }
                    
                    // 4) adjust base
                    // accordingly
                    if (base != -1.0)
                    {
                        entropy /= std::log(base);
                    };
                    
                    // 5) return entropy
                    return Rcpp::NumericVector::create(entropy);

                }
                    
            }
        }
};

#endif // CLASSIFICATION_ENTROPY_H