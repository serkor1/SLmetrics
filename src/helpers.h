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

inline Eigen::MatrixXi confmat(const Rcpp::IntegerVector& actual, const Rcpp::IntegerVector& predicted)
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
  const int k = levels.size();

  // 2) Create the k x k matrix for all available factors
  Eigen::MatrixXi confmat = Eigen::MatrixXi::Zero(k, k);

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

  // 5) populate the confusion
  // matrix.
  //
  // NOTE: factor variables starts at 1, and
  // C++ is 0 indexed, so we subtract 1 otherwise
  // the matrix will be shifted +1 in each dimension
  for (int i = 0; i < n; ++i) {
    const int actual_value = actual_ptr[i] - 1;
    const int predicted_value = predicted_ptr[i] - 1;

    // Increment the appropriate element in the matrix
    //
    // NOTE: This is a rowwise operation in memory.
    ++matrix_ptr[predicted_value * k + actual_value];
  }

  return confmat;
}
