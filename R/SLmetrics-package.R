## usethis namespace: start
#' @importFrom Rcpp sourceCpp
## usethis namespace: end
NULL

## usethis namespace: start
#' @useDynLib SLmetrics, .registration = TRUE
## usethis namespace: end
NULL


#' @title {SLmetrics}: Machine Learning Performance Evaluation on Steroids
#' 
#' @description
#' \{SLmetrics\} is a lightweight package written in C++ for supervised and unsupervised Machine Learning applications. The package has been 
#' developed with two primary goals in mind: memory management and execution speed. All functions are designed with internal pointers and references, 
#' ensuring that passed objects are not copied into memory, resulting in optimized performance.
#' 
#' @section Handling of Missing Values:
#' 
#' \{SLmetrics\} does not provide explicit handling for missing values in either regression or classification applications. Users are advised 
#' to ensure that their input data is preprocessed to remove or impute missing values before passing them to any functions. 
#' 
#' Since the package heavily relies on pointers and references for performance, passing data with missing values may lead to undefined behavior, 
#' including potential crashes of the R session.
#' 
#' For classification metrics that support micro and macro averages, \{SLmetrics\} does handle invalid values such as divisions by zero, 
#' ensuring robust computation and accurate results.
#' 
#' @keywords internal 
"_PACKAGE"

#' @title Classification Documenatation
#' @name classification_documentation
#' 
#' @description
#' This roxygen block is the generic documnentation
#' for classification metrics for all the parameters.
#' 
#' @param actual,predicted A pair of [integer] or [factor] vectors of [length] \eqn{n}, and \eqn{k} levels.
#' @param actual A vector [length] \eqn{n}, and \eqn{k} levels. Can be of [integer] or [factor].
#' @param response A \eqn{n \times k} <[numeric]>-matrix of predicted probabilities.
#'   The \eqn{i}-th row should sum to 1 (i.e., a valid probability distribution
#'   over the \eqn{k} classes). The first column corresponds to the first factor
#'   level in \code{actual}, the second column to the second factor level, and so on.
#' @param method A <[numeric]> value (default: \eqn{0}). Defines the underlying method of calculating the area under the curve. If \eqn{0} it is calculated using the `trapezoid`-method, if \eqn{1} it is calculated using the `step`-method.
#' @param micro A <[logical]>-value of [length] \eqn{1} (default: [NULL]). If [TRUE] it returns the
#' micro average across all \eqn{k} classes, if [FALSE] it returns the macro average.
#' @param presorted Currently not working.
#' @param thresholds An optional <[numeric]> vector of [length] \eqn{n} (default: [NULL]).
#' @param w A <[numeric]> vector of sample weights.
#' @param x A confusion matrix created [cmatrix()].
#' @param estimator An <[integer]>-value of [length] \eqn{1} (default: \eqn{0}).
#' \itemize{
#'   \item 0 - a named <[numeric]>-vector of [length] k (class-wise)
#'   \item 1 - a <[numeric]> value (Micro averaged metric)
#'   \item 2 - a <[numeric]> value (Macro averaged metric)
#' }
#' @param na.rm A <[logical]> value of [length] \eqn{1} (default: [TRUE]). If [TRUE], [NA] values are removed from the computation. 
#' This argument is only relevant when `micro != NULL`. 
#' When `na.rm = TRUE`, the computation corresponds to `sum(c(1, 2, NA), na.rm = TRUE) / length(na.omit(c(1, 2, NA)))`.
#' When `na.rm = FALSE`, the computation corresponds to `sum(c(1, 2, NA), na.rm = TRUE) / length(c(1, 2, NA))`.
#' @param ... Arguments passed into other methods.
#'
#' @returns NULL
#' @keywords internal
#' @usage NULL
NULL


#' @title Entropy Documenatation
#' @name entropy_documentation
#' 
#' @description
#' This roxygen block is the generic documnentation
#' for entropy metrics for all the parameters.
#' 
#' @param pk,qk A pair \eqn{n \times k} <[numeric]>-matrix of observed (pk) and predicted (qk) probabilities.
#'   The \eqn{i}-th row should sum to 1 (i.e., a valid probability distribution
#'   over the \eqn{k} classes). The first column corresponds to the first factor
#'   level in \code{actual}, the second column to the second factor level, and so on.
#' @param pk A \eqn{n \times k} <[numeric]>-matrix of predicted probabilities.
#'   The \eqn{i}-th row should sum to 1 (i.e., a valid probability distribution
#'   over the \eqn{k} classes). The first column corresponds to the first factor
#'   level in \code{actual}, the second column to the second factor level, and so on.
#' @param dim An <[integer]> value of [length] 1 (Default: 0). Defines the dimension along which to calculate the entropy (0: total, 1: row-wise, 2: column-wise).
#' @param base A <[numeric]> value of [length] 1 (Default: -1). The logarithmic base to use. Default value specifies natural logarithms.
#' @param normalize A <[logical]>-value (default: [TRUE]). If [TRUE],
#'   the mean cross-entropy across all observations is returned; otherwise, the
#'   sum of cross-entropies is returned.
#' @param ... Arguments passed into other methods
#'
#' @returns NULL
#' @keywords internal
#' @usage NULL
NULL

#' @title Regression Documenatation
#' @name regression_documentation
#' 
#' @description
#' This roxygen block is the generic documnentation
#' for entropy metrics for all the parameters.
#' 
#' @param actual,predicted A pair of [integer] or [factor] vectors of [length] \eqn{n}, and \eqn{k} levels.
#' @param w A <[numeric]> vector of sample weights.
#' @param ... Arguments passed into other methods
#' @param delta A <[numeric]>-vector of [length] \eqn{1} (default: \eqn{1}). The threshold value for switch between functions (see calculation).
#' @param correction A <[logical]> vector of [length] \eqn{1} (default: [FALSE]). If [TRUE] the variance and covariance
#' will be adjusted with \eqn{\frac{1-n}{n}}
#' @param k A <[numeric]>-vector of [length] 1 (default: 0). For adjusted \eqn{R^2} set \eqn{k = \kappa - 1}, where \eqn{\kappa} is the number of parameters.
#' @param normalization A <[numeric]>-value of [length] \eqn{1} (default: \eqn{1}). \eqn{0}: [mean]-normalization, \eqn{1}: [range]-normalization, \eqn{2}: [IQR]-normalization.
#' @param alpha A <[numeric]>-value of [length] \eqn{1} (default: \eqn{0.5}). The slope of the pinball loss function.
#' @param deviance A <[logical]>-value of [length] 1 (default: [FALSE]). If [TRUE] the function returns the \eqn{D^2} loss.
#'
#' @returns NULL
#' @keywords internal
#' @usage NULL
NULL