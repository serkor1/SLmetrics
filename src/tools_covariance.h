#ifndef tools_covariance
#define tools_covariance

#include "utilities_Package.h"

/**
* @namespace dimensions
* @brief A collection of helper functions for extracting dimensions and names 
* from Rcpp::NumericMatrix or Rcpp::DataFrame objects.
*
* This namespace provides:
*   - nrows(): retrieve the number of rows
*   - ncols(): retrieve the number of columns
*   - names(): retrieve the column names
*/
namespace dimensions {

    template <typename T>
    int nrows(const T &x) {
        if constexpr (std::is_same_v<T, Rcpp::NumericMatrix>) {
            return x.nrow();
        } else {
            return x.nrows();
        }
    }

    template <typename T>
    int ncols(const T &x) {
        if constexpr (std::is_same_v<T, Rcpp::NumericMatrix>) {
            return x.ncol();
        } else {
            return x.size();
        }
    }

    template <typename T>
    Rcpp::CharacterVector names(const T &x) {
        if constexpr (std::is_same_v<T, Rcpp::NumericMatrix>) {
            return Rcpp::colnames(x);
        } else {
            return x.names();
        }
    }

}

/**
* @namespace pointers
* @brief A collection of helper functions for extracting column pointers from
* from Rcpp::NumericMatrix or Rcpp::DataFrame objects.
*
* This namespace provides:
*   - col(): retrieve the column pointers
*/
namespace pointers {

    template <typename T>
    std::vector<const double*> col(const T &x) {

        const int n = dimensions::nrows(x);
        const int k = dimensions::ncols(x);

        
        std::vector<const double*> ptrs(k, nullptr);

        if constexpr (std::is_same_v<T, Rcpp::NumericMatrix>) {
            
            const double* base_ptr = x.begin();
            for (int j = 0; j < k; j++) {
                ptrs[j] = base_ptr + j * n;
            }

        } else {
            
            for (int j = 0; j < k; j++) {
                Rcpp::NumericVector col = x[j];
                ptrs[j] = col.begin();
            }

        }

        return ptrs;
    }

}

/**
* @class Covariance
* @brief This class returns a Rcpp::List similar to `cov.wt()`
*
* TODO: Convert to @struct to use internally, and return it as a Rcpp::List on the R-side
* TODO: Find a better name for the @class ¯\_(ツ)_/¯
* TODO: Implement a weighted version
* TODO: Optimize its parallelization
*/
class Covariance {
    public:
        
        template <typename T>
        static Rcpp::List cov(const T &x) {

            // 1) dimensions and names of the input
            const int n = dimensions::nrows(x);
            const int k = dimensions::ncols(x);
            const Rcpp::CharacterVector names = dimensions::names(x);

            // 2) get column pointers
            std::vector<const double*> col_ptrs = pointers::col(x);

            // 3) prepare output
            Rcpp::NumericMatrix covariance_matrix(k, k);

            // 4) compute column means
            // std::vector<double> means(k, 0.0);
            Rcpp::NumericVector means(k, 0.0);

            #ifdef _OPENMP
                if (getUseOpenMP()) {
                    #pragma omp parallel for
                    for (int j = 0; j < k; j++) {
                        double sum = 0.0;
                        const double* col_ptr = col_ptrs[j];
                        for (int i = 0; i < n; i++) {
                            sum += col_ptr[i];
                        }
                        means[j] = sum / n;
                    }
                } else 
            #endif
                {
                    for (int j = 0; j < k; j++) {
                        double sum = 0.0;
                        const double* col_ptr = col_ptrs[j];
                        for (int i = 0; i < n; i++) {
                            sum += col_ptr[i];
                        }
                        means[j] = sum / n;
                    }
                }

            // 5) calculate covariances
            #ifdef _OPENMP
                if (getUseOpenMP()) {
                    #pragma omp parallel for
                    for (int i = 0; i < k; i++) {
                        for (int j = i; j < k; j++) {
                            double sum = 0.0;
                            const double* xi = col_ptrs[i];
                            const double* xj = col_ptrs[j];
                            double mi = means[i];
                            double mj = means[j];

                            for (int row = 0; row < n; row++) {
                                sum += (xi[row] - mi) * (xj[row] - mj);
                            }
                            double cov = sum / (n - 1);
                            covariance_matrix(i, j) = cov;
                            covariance_matrix(j, i) = cov;
                        }
                    }
                } else
            #endif
                {
                    for (int i = 0; i < k; i++) {
                        for (int j = i; j < k; j++) {
                            double sum = 0.0;
                            const double* xi = col_ptrs[i];
                            const double* xj = col_ptrs[j];
                            double mi = means[i];
                            double mj = means[j];

                            for (int row = 0; row < n; row++) {
                                sum += (xi[row] - mi) * (xj[row] - mj);
                            }
                            double cov = sum / (n - 1);
                            covariance_matrix(i, j) = cov;
                            covariance_matrix(j, i) = cov;
                        }
                    }
                }
            
            // 6) set names of the
            // covariance matrix
            Rcpp::rownames(covariance_matrix) = names;
            Rcpp::colnames(covariance_matrix) = names;

            // 7) set names of the 
            // means
            means.attr("names") = names;

            // 8) return as Rcpp::List
            return Rcpp::List::create(
                Rcpp::_["cov"]    = covariance_matrix,
                Rcpp::_["center"] = means,
                Rcpp::_["n.obs"]  = n
            );
        }
}; 

#endif
