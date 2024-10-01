/*
 * A bunch of helpers for calculating
 * various metrics, and simplifying
 * operations where deemed necessary.
 *
 *
 * NOTE: Be aware of implicit casting of vectors vs matrices
 * ie. VectorXi col_sum = matrix.sum() does not have the same
 * dimensions as matrix.sum() which by definition is a matrix!
 *
 * R Studio crashes if the dimensions doesn't align with matrix-algebra! :-(
 */

#include <RcppEigen.h>
#include <cmath>
#define EIGEN_USE_MKL_ALL
EIGEN_MAKE_ALIGNED_OPERATOR_NEW


using namespace Rcpp;

/*
 * This function locates all 0 values
 * and returns a vector
 */

inline __attribute__((always_inline)) Eigen::VectorXi extract(const Eigen::VectorXd& x) {
  // Count how many positive elements there are
  Eigen::Index count = (x.array() > 0).count();

  // Allocate an Eigen::VectorXi to store the indices of positive values
  Eigen::VectorXi indices(count);

  // Copy the indices of positive elements
  Eigen::Index j = 0;
  for (Eigen::Index i = 0; i < x.size(); ++i) {
    if (x(i) > 0) {
      indices(j++) = i;  // Store the index of the positive value
    }
  }

  // Return the indices of positive values
  return indices;
}



inline Eigen::VectorXi TP(const Eigen::MatrixXi& matrix)
{
  /*
   * This function returns a vector of
   * True Positives, which corresponds to the
   * diagonal matrix.
   */

  Eigen::VectorXi TP = matrix.diagonal();

  return TP;
}

inline Eigen::VectorXi FP(const Eigen::MatrixXi& matrix)
{
  /*
   * This function returns a vector of
   * False Positives (FP) for each class,
   * which corresponds to the column-wise sum
   * of the confusion matrix minus the diagonal elements (True Positives).
   */

  Eigen::VectorXi TP = matrix.diagonal();
  Eigen::VectorXi FP = matrix.colwise().sum() - TP.transpose();

  return FP;
}

inline Eigen::VectorXi TN(const Eigen::MatrixXi& matrix)
{
  /*
   * This function returns a vector
   * of True Negatives (TN)
   */

  const int N = matrix.sum();
  Eigen::VectorXi TP = matrix.diagonal();
  Eigen::VectorXi row_sums = matrix.rowwise().sum();
  Eigen::VectorXi col_sums = matrix.colwise().sum();

  // Compute True Negatives (TN) using in-place calculations to minimize temporary objects
  Eigen::VectorXi TN = Eigen::VectorXi::Constant(matrix.rows(), N);
  TN -= row_sums + col_sums - TP;

  return TN;
}



inline Eigen::VectorXi FN(const Eigen::MatrixXi& matrix)
{
  /*
   * This function returns a vector of
   * False Negatives
   */
  Eigen::VectorXi TP = matrix.diagonal();
  Eigen::VectorXi FN = matrix.rowwise().sum() - TP;

  return FN;
}


inline __attribute__((always_inline)) Eigen::MatrixXi confmat(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
{
  /*
   * This function generates a confusion matrix
   * by incrementing locations based on the actual
   * vector. If it includes NA values it will
   * crash, so this function should check for missing
   * values in both vectors. This is for later
   */

  // 1) Get the levels
  // and store
  const Rcpp::CharacterVector& levels = actual.attr("levels");
  const int k = levels.size() + 1;

  // 2) Create the k x k matrix for all available factors
  Eigen::MatrixXi confmat = Eigen::MatrixXi::Zero(k, k).eval();

  // 3) Calculate the size of the actual
  // vector. The implicit assumption
  // is that actual and predicted have the
  // equal size.
  const int n = actual.size();

  // 4) Generate pointers
  // to actual, predicted and
  // mthe matrix
  const int* actual_ptr = actual.begin();
  const int* predicted_ptr = predicted.begin();
  int* matrix_ptr = confmat.data();


  // 6) Process 4 elements at a time (batch size = 6)
  int i = 0;
  for (; i <= n - 6; i += 6) {
    // Load 6 elements from actual and predicted
    const int actual_val_1 = actual_ptr[i];
    const int predicted_val_1 = predicted_ptr[i];

    const int actual_val_2 = actual_ptr[i + 1];
    const int predicted_val_2 = predicted_ptr[i + 1];

    const int actual_val_3 = actual_ptr[i + 2];
    const int predicted_val_3 = predicted_ptr[i + 2];

    const int actual_val_4 = actual_ptr[i + 3];
    const int predicted_val_4 = predicted_ptr[i + 3];

    const int actual_val_5 = actual_ptr[i + 4];
    const int predicted_val_5 = predicted_ptr[i + 4];

    const int actual_val_6 = actual_ptr[i + 5];
    const int predicted_val_6 = predicted_ptr[i + 5];

    // Update matrix for all 4 pairs in one loop
    ++matrix_ptr[predicted_val_1 * k + actual_val_1];
    ++matrix_ptr[predicted_val_2 * k + actual_val_2];
    ++matrix_ptr[predicted_val_3 * k + actual_val_3];
    ++matrix_ptr[predicted_val_4 * k + actual_val_4];
    ++matrix_ptr[predicted_val_5 * k + actual_val_5];
    ++matrix_ptr[predicted_val_6 * k + actual_val_6];
  }

  // 7) Handle any leftover elements (when n is not a multiple of 4)
  for (; i < n; ++i) {
    const int actual_value = actual_ptr[i];
    const int predicted_value = predicted_ptr[i];
    ++matrix_ptr[predicted_value * k + actual_value];
  }

  // // 5) populate the confusion
  // // matrix.
  // //
  // // NOTE: factor variables starts at 1, and
  // // C++ is 0 indexed, so we subtract 1 otherwise
  // // the matrix will be shifted +1 in each dimension
  // for (int i = 0; i < n; ++i) {
  //   const int actual_value = actual_ptr[i];
  //   const int predicted_value = predicted_ptr[i];
  //
  //   // Increment the appropriate element in the matrix
  //   //
  //   // NOTE: This is a rowwise operation in memory.
  //   ++matrix_ptr[predicted_value * k + actual_value];
  // }

  return confmat.block(1, 1, k - 1, k - 1);
}

inline Eigen::MatrixXi seqmat(
    int n,
    double power) {
  Eigen::MatrixXi mat(n, n);

  int* mat_data = mat.data();


  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) {
      int value = std::pow(i - j, power);
      *(mat_data + i * n + j) = value;
      *(mat_data + j * n + i) = value;
    }



  };

  if (power == 0) {

    for (int i = 0; i < n; ++i) {

      *(mat_data + i * n + i) = 0;

    }

  }

  return mat;
}
