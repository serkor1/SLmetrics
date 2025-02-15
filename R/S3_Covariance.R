# script: Create a plot of
# the confusion_matrix
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-20
# objective:
# script start;

#' @inherit stats::cov.wt
#' 
#' @param ... Arguments passed into other methods
#' 
#' @family Tools
cov.wt <- function(x, ...) {
  UseMethod(
    generic = "cov.wt",
    object  = x
  )
}

# script end;