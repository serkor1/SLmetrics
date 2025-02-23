#ifndef CLASSIFICATION_auc_h
#define CLASSIFICATION_auc_h

#include <Rcpp.h>
#include <vector>
#include <algorithm>
#include <numeric>


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