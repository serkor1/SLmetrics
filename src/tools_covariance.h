#ifndef tools_covariance
#define tools_covariance

#include "utilities_Package.h"
#include <cmath>

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
* @brief A class with static methods for weighted/unweighted covariance
*/
class Covariance {
    public:

        // Unweighted Covariance Matrrix
        template <typename T>
        static Rcpp::List cov(
            const T& x,
            bool cor = false,
            bool center = true,
            const std::string& method = "unbiased") {
                    
                // 1) Dimensions and pointers
                const int n = dimensions::nrows(x);
                const int k = dimensions::ncols(x);
                Rcpp::CharacterVector names = dimensions::names(x);
                std::vector<const double*> cols = pointers::col(x);

                // 2) Prepare output objects
                Rcpp::NumericMatrix covariance_matrix(k, k);
                Rcpp::NumericVector means(k, 0.0);

                // 3) Denominator
                int denom = 1;
                bool unbiased = (method == "unbiased");
                if (unbiased) {
                    denom = n - 1;
                } else {
                    denom = n;
                }

                if (center) {
                    // Optionally parallel outside the loop
                    #ifdef _OPENMP
                    if (getUseOpenMP()) {
                        #pragma omp parallel for
                        for (int j = 0; j < k; j++) {
                            const double* colj = cols[j];
                            double sumj = 0.0;
                            // pointer-based accumulation
                            const double* p = colj;
                            const double* pEnd = colj + n;
                            while (p < pEnd) {
                                sumj += *p++;
                            }
                            means[j] = sumj / n;
                        }
                    } else
                    #endif
                    {
                        for (int j = 0; j < k; j++) {
                            const double* colj = cols[j];
                            double sumj = 0.0;
                            const double* p = colj;
                            const double* pEnd = colj + n;
                            while (p < pEnd) {
                                sumj += *p++;
                            }
                            means[j] = sumj / n;
                        }
                    }
                    means.attr("names") = names;
                }

                #ifdef _OPENMP
                if (getUseOpenMP()) {
                    #pragma omp parallel for
                    for (int i = 0; i < k; i++) {
                        for (int j = i; j < k; j++) {
                            double sum_ij = 0.0;
                            const double* xi = cols[i];
                            const double* xj = cols[j];
                            double mi = means[i];
                            double mj = means[j];

                            const double* px = xi;
                            const double* py = xj;
                            const double* px_end = xi + n;

                            if (center) {
                                while (px < px_end) {
                                    double diff_i = (*px++) - mi;
                                    double diff_j = (*py++) - mj;
                                    sum_ij += diff_i * diff_j;
                                }
                            } else {
                                // no-centering path
                                while (px < px_end) {
                                    sum_ij += (*px++) * (*py++);
                                }
                            }

                            double cov_val = sum_ij / denom;
                            covariance_matrix(i, j) = cov_val;
                            covariance_matrix(j, i) = cov_val;
                        }
                    }
                } else
                #endif
                {
                    for (int i = 0; i < k; i++) {
                        for (int j = i; j < k; j++) {
                            double sum_ij = 0.0;
                            const double* xi = cols[i];
                            const double* xj = cols[j];
                            double mi = means[i];
                            double mj = means[j];

                            const double* px = xi;
                            const double* py = xj;
                            const double* px_end = xi + n;
                            if (center) {
                                while (px < px_end) {
                                    double diff_i = (*px++) - mi;
                                    double diff_j = (*py++) - mj;
                                    sum_ij += diff_i * diff_j;
                                }
                            } else {
                                while (px < px_end) {
                                    sum_ij += (*px++) * (*py++);
                                }
                            }

                            double cov_val = sum_ij / denom;

                            covariance_matrix(i, j) = cov_val;
                            covariance_matrix(j, i) = cov_val;
                        }
                    }
                }

                // 6) Set row/col names
                Rcpp::rownames(covariance_matrix) = names;
                Rcpp::colnames(covariance_matrix) = names;


                if (cor) {

                    Rcpp::NumericMatrix correlation_matrix(k, k);
                    double* cov_ptr = covariance_matrix.begin();
                    double* cor_ptr = correlation_matrix.begin();

                    for (int j = 0; j < k; j++) {
                        double sd_j = std::sqrt(cov_ptr[j + (size_t)j * k]);
                        for (int i = 0; i < k; i++) {
                            double sd_i = std::sqrt(cov_ptr[i + (size_t)i * k]);
                            cor_ptr[i + (size_t)j * k] =
                                cov_ptr[i + (size_t)j * k] / (sd_i * sd_j);
                        }
                    }

                    Rcpp::rownames(correlation_matrix) = names;
                    Rcpp::colnames(correlation_matrix) = names;

                    return Rcpp::List::create(
                        Rcpp::_["cov"]    = covariance_matrix,
                        Rcpp::_["center"] = center ? means : Rcpp::NumericVector::create(0.0),
                        Rcpp::_["n.obs"]  = n,
                        Rcpp::_["cor"]    = correlation_matrix);
                }

                // 8) Return
                return Rcpp::List::create(
                    Rcpp::_["cov"]    = covariance_matrix,
                    Rcpp::_["center"] = center ? means : Rcpp::NumericVector::create(0.0),
                    Rcpp::_["n.obs"]  = n);
        }

        template <typename T>
        static Rcpp::List cov(
            const T& x,
            Rcpp::NumericVector& wt,
            bool cor = false,
            bool center = true,
            const std::string& method = "unbiased") {

                // 1) Dimensions and pointers
                const int n = dimensions::nrows(x);
                const int k = dimensions::ncols(x);
                Rcpp::CharacterVector names = dimensions::names(x);
                std::vector<const double*> cols = pointers::col(x);

                // 2) Output objects
                Rcpp::NumericMatrix covariance_matrix(k, k);
                Rcpp::NumericVector means(k, 0.0);

                // 3) Sum of raw weights
                double sum_w = 0.0;
                {
                    const double* w_ptr = wt.begin();
                    const double* w_end = w_ptr + n;
                    while (w_ptr < w_end) {
                        sum_w += *w_ptr++;
                    }
                }
                double inv_sum_w = 1.0 / sum_w;

                // 4) Normalize Weights
                double sum_w_sq = 0.0;
                {
                    double* w_ptr = wt.begin();
                    double* w_end = w_ptr + n;

                    if (center) {
                        while (w_ptr < w_end) {
                            double w_value = *w_ptr;
                            w_value *= inv_sum_w; 
                            *w_ptr++ = w_value;  
                            sum_w_sq += (w_value * w_value);
                        }

                        for (int j = 0; j < k; j++) {
                            const double* x_col = cols[j];
                            const double* x_end = x_col + n;
                            const double* w_col = wt.begin();
                            double sum_j = 0.0;
                            while (x_col < x_end) {
                                sum_j += (*x_col++) * (*w_col++);
                            }
                            means[j] = sum_j;
                        }
                    } else {

                        while (w_ptr < w_end) {
                            double w_value = *w_ptr;
                            w_value *= inv_sum_w;
                            *w_ptr++ = w_value;
                            sum_w_sq += (w_value * w_value);
                        }
                    }
                }

                // 5) Denominator
                bool unbiased = (method == "unbiased");
                double denom = 1.0;
                if (unbiased) {
                    denom = 1.0 - sum_w_sq;
                } else {
                    denom = 1.0;
                }

                #ifdef _OPENMP
                if (getUseOpenMP()) {
                    #pragma omp parallel for
                    for (int i = 0; i < k; i++) {
                        for (int j = i; j < k; j++) {
                            double sum_ij = 0.0;
                            double mi = means[i];
                            double mj = means[j];
                            const double* xi = cols[i];
                            const double* xj = cols[j];
                            const double* xiEnd = xi + n;
                            const double* w_ptr = wt.begin();

                            if (center) {
                                while (xi < xiEnd) {
                                    double w_value = *w_ptr++;
                                    double diff_i = (*xi++) - mi;
                                    double diff_j = (*xj++) - mj;
                                    sum_ij += w_value * diff_i * diff_j;
                                }
                            } else {
                                while (xi < xiEnd) {
                                    double w_value = *w_ptr++;
                                    sum_ij += w_value * (*xi++) * (*xj++);
                                }
                            }

                            double cov_val = sum_ij / denom;
                            covariance_matrix(i, j) = cov_val;
                            covariance_matrix(j, i) = cov_val;

                        }
                    }
                } else
                #endif
                {
                    for (int i = 0; i < k; i++) {
                        for (int j = i; j < k; j++) {
                            double sum_ij = 0.0;
                            double mi = means[i];
                            double mj = means[j];
                            const double* xi = cols[i];
                            const double* xj = cols[j];
                            const double* xiEnd = xi + n;
                            const double* w_ptr = wt.begin();

                            if (center) {
                                while (xi < xiEnd) {
                                    double w_value = *w_ptr++;
                                    double diff_i = (*xi++) - mi;
                                    double diff_j = (*xj++) - mj;
                                    sum_ij += w_value * diff_i * diff_j;
                                }

                                means.attr("names") = names;


                            } else {
                                while (xi < xiEnd) {
                                    double w_value = *w_ptr++;
                                    sum_ij += w_value * (*xi++) * (*xj++);
                                }
                            }
                            double cov_val = sum_ij / denom;
                            covariance_matrix(i, j) = cov_val;
                            covariance_matrix(j, i) = cov_val;
                        }
                    }
                }

                Rcpp::rownames(covariance_matrix) = names;
                Rcpp::colnames(covariance_matrix) = names;
                
                if (cor) {
                    Rcpp::NumericMatrix correlation_matrix(k, k);
                    double* cov_ptr = covariance_matrix.begin();
                    double* cor_ptr = correlation_matrix.begin();

                    for (int j = 0; j < k; j++) {
                        double sd_j = std::sqrt(cov_ptr[j + (size_t)j * k]);
                        for (int i = 0; i < k; i++) {
                            double sd_i = std::sqrt(cov_ptr[i + (size_t)i * k]);
                            cor_ptr[i + (size_t)j * k] =
                                cov_ptr[i + (size_t)j * k] / (sd_i * sd_j);
                        }
                    }
                    Rcpp::rownames(correlation_matrix) = names;
                    Rcpp::colnames(correlation_matrix) = names;

                    return Rcpp::List::create(
                        Rcpp::_["cov"]    = covariance_matrix,
                        Rcpp::_["center"] = center ? means : Rcpp::NumericVector::create(0.0),
                        Rcpp::_["n.obs"]  = n,
                        Rcpp::_["wt"]     = wt,
                        Rcpp::_["cor"]    = correlation_matrix);
                }

                // 9) Return final list
                return Rcpp::List::create(
                    Rcpp::_["cov"]    = covariance_matrix,
                    Rcpp::_["center"] = center ? means : Rcpp::NumericVector::create(0.0),
                    Rcpp::_["n.obs"]  = n,
                    Rcpp::_["wt"]     = wt);
        }

};

#endif