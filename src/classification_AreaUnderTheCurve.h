#ifndef CLASSIFICATION_auc_h
#define CLASSIFICATION_auc_h

#include <Rcpp.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>


inline double trapeziod_area(
    double x1,
    double y1, 
    double x2, 
    double y2) {
        
        double width  = (x2 - x1);
        double height = 0.5 * (y2 + y1);

        return width * height;
}

inline double step_area(
    double x1,
    double y1, 
    double x2, 
    double y2) {
        
        double width  = (x2 - x1);
        double height = y1;

        return width * height;
}

static inline 
std::vector<std::size_t> prepare_index(
    const Rcpp::NumericVector& response,
    bool ordered) {
        
        std::size_t n = response.size();
        std::vector<std::size_t> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        if (!ordered) {
            // descending order
            const double* ptr_response = response.begin();
            std::sort(idx.begin(), idx.end(), [&](std::size_t a, std::size_t b) {
            return ptr_response[a] > ptr_response[b];
            });
        }
        
        return idx;
}

/**
 * 
 * @param response_matrix A (n x k)-matrix of probabilities.
 * @param column An integer corresponding to the k'th column.
 * @param ordered A bool. If true it is assumed that the matrix columns are sorted.
 *
 * @returns
 * A (n x 1) std::vector with indices pointing to the sorted values.
 *
 */
// static inline 
// std::vector<std::size_t> prepare_index(
//     const Rcpp::NumericMatrix& response_matrix,
//     int column,
//     bool ordered) {

//         std::size_t n = response_matrix.nrow();
//         std::vector<std::size_t> idx(n);
//         std::iota(idx.begin(), idx.end(), 0);

//         // If not ordered, sort in descending order by response_matrix(row, column)
//         if (!ordered) {
//             std::sort(idx.begin(), idx.end(), [&](std::size_t a, std::size_t b) {
//             return response_matrix(a, column) > response_matrix(b, column);
//             });
//         }
        
//         return idx;

// }
// static inline 
// std::unique_ptr<std::size_t[]> prepare_index(
//     const Rcpp::NumericMatrix& response_matrix,
//     int column,
//     bool ordered) {

//     std::size_t n = response_matrix.nrow();
    
//     std::unique_ptr<std::size_t[]> idx(new std::size_t[n]);
    
//     // 2) Initialize values from 0..(n-1)
//     std::iota(idx.get(), idx.get() + n, 0);
    
//     // 3) If not ordered, sort in descending order by response_matrix(row, column)
//     if (!ordered) {
//         std::sort(idx.get(), idx.get() + n, [&](std::size_t a, std::size_t b) {
//             return response_matrix(a, column) > response_matrix(b, column);
//         });
//     }
    
//     // 4)
//     return idx;
// }
static inline 
std::unique_ptr<std::size_t[]> prepare_index(
    const Rcpp::NumericMatrix& response_matrix,
    int column,
    int n,
    bool ordered) {

        std::unique_ptr<std::size_t[]> idx(new std::size_t[n]);
        std::iota(idx.get(), idx.get() + n, 0);

        const double* col = &response_matrix(0, column);

        if (!ordered) {
            std::sort(idx.get(), idx.get() + n, [col](std::size_t a, std::size_t b) {
                return col[a] > col[b];
            });
        }
        return idx;
}


static inline 
double count_positives(
    const Rcpp::IntegerVector& actual,
    const std::vector<std::size_t>& idx,
    int class_label) {
        
        double positives = 0.0;
        const int* ptr_actual = actual.begin();
        for (std::size_t i = 0; i < idx.size(); i++) {
            if (ptr_actual[idx[i]] == class_label) {
            positives += 1.0;
            }
        }

        return positives;
}

static inline 
double count_positives(
    const int* ptr_actual,
    const std::size_t* idx,
    int n,
    int class_label) {

        double positives = 0.0;
        //const int* ptr_actual = actual.begin();

        for (std::size_t i = 0; i < n; i++) {
            positives += (ptr_actual[idx[i]] == class_label);
        }

        return positives;
}


static inline
double count_positives(
    const Rcpp::IntegerVector& actual, 
    const Rcpp::NumericVector& w,
    const std::vector<std::size_t>& idx,
    int class_label) {
        
        double positives = 0.0;
        const int* ptr_actual   = actual.begin();
        const double* ptr_weight = w.begin();

        for (std::size_t i = 0; i < idx.size(); i++) {
            std::size_t id = idx[i];
            if (ptr_actual[id] == class_label) {
            positives += ptr_weight[id];
            }
        }

        return positives;
}

#endif