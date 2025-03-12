// [[Rcpp::plugins(cpp23)]]
#include <Rcpp.h>
#include <algorithm>
#include <functional>

#ifdef PARALLEL
    #include <execution>
        namespace execution = std::execution;
#else
    enum class execution { seq, unseq, par_unseq, par };
#endif

/**
 * @brief This function assumes that the matrix columns
 * are independent, and sorts each column independently of
 * of eachother
 */
//' @method presort matrix
//' @export
// [[Rcpp::export(presort.matrix)]]
Rcpp::NumericMatrix sort_matrix(
  Rcpp::NumericMatrix x, 
  bool decreasing = false) {

    // 0) extract matrix
    // dimensions for the
    // sorting    
    const int n_rows = x.nrow();
    const int n_cols = x.ncol();
    
    // 1) extract pointer
    // to matrix and loop
    double* data = x.begin();
    #ifdef PARALLEL
        if (decreasing) {
            for (int col = 0; col < n_cols; ++col) {
                double* col_begin = data + col * n_rows;
                double* col_end   = col_begin + n_rows;

                std::sort(execution::par_unseq, col_begin, col_end, std::greater<>());
            }
        } else {
            for (int col = 0; col < n_cols; ++col) {
                double* col_begin = data + col * n_rows;
                double* col_end   = col_begin + n_rows;

                std::sort(execution::par_unseq, col_begin, col_end);
            }
        }
    #else
        if (decreasing) {
            for (int col = 0; col < n_cols; ++col) {
                double* col_begin = data + col * n_rows;
                double* col_end   = col_begin + n_rows;

                std::sort(col_begin, col_end, std::greater<>());
            }
        } else {
            for (int col = 0; col < n_cols; ++col) {
                double* col_begin = data + col * n_rows;
                double* col_end   = col_begin + n_rows;

                std::sort(col_begin, col_end);
            }
        }
    #endif

    return x;
}

//' @method preorder matrix
//' @export
// [[Rcpp::export(preorder.matrix)]]
Rcpp::IntegerMatrix order_matrix(
    Rcpp::NumericMatrix x, 
    bool decreasing = false) {

        const int n_rows = x.nrow();
        const int n_cols = x.ncol();
        Rcpp::IntegerMatrix index_matrix(n_rows, n_cols);
        std::vector<int> indices(n_rows);
        std::iota(indices.begin(), indices.end(), 0);

        // std::ranges::iota(indices, 0);

        for (int col = 0; col < n_cols; ++col) {
            #ifdef PARALLEL
              if (decreasing) {
                  std::sort(execution::par_unseq, indices.begin(), indices.end(),
                          [&x, col](int i, int j) {
                              return x(i, col) > x(j, col);
                          });
              } else {
                  std::sort(execution::par_unseq, indices.begin(), indices.end(),
                          [&x, col](int i, int j) {
                              return x(i, col) < x(j, col);
                          });
              }
            #else
              if (decreasing) {
                  std::sort(indices.begin(), indices.end(),
                          [&x, col](int i, int j) {
                              return x(i, col) > x(j, col);
                          });
              } else {
                  std::sort(indices.begin(), indices.end(),
                          [&x, col](int i, int j) {
                              return x(i, col) < x(j, col);
                          });
              }
            #endif

            for (int row = 0; row < n_rows; ++row) {
                index_matrix(row, col) = indices[row] + 1;
            }
        }
        
        return index_matrix;
}