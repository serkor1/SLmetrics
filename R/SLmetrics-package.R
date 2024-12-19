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
#' {SLmetrics} is a lightweight package written in C++ for supervised and unsupervised Machine Learning applications. The package has been 
#' developed with two primary goals in mind: memory management and execution speed. All functions are designed with internal pointers and references, 
#' ensuring that passed objects are not copied into memory, resulting in optimized performance.
#' 
#' @section Handling of Missing Values:
#' 
#' {SLmetrics} does not provide explicit handling for missing values in either regression or classification applications. Users are advised 
#' to ensure that their input data is preprocessed to remove or impute missing values before passing them to any functions. 
#' 
#' Since the package heavily relies on pointers and references for performance, passing data with missing values may lead to undefined behavior, 
#' including potential crashes of the R session.
#' 
#' For classification metrics that support micro and macro averages, {SLmetrics} does handle invalid values such as divisions by zero, 
#' ensuring robust computation and accurate results.
#' 
#' @keywords internal 
"_PACKAGE"
