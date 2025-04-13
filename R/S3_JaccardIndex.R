# script: Jaccard Methods
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Create Methods
# script start;

#' @title NULL
#' @usage NULL
#' @return NULL
#' 
#' @aliases csi tscore weighted.csi weighted.tscore
#' 
#' @templateVar .TITLE jaccard
#' @templateVar .FUN jaccard
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' @template classification_standard_template
#' 
#' @section Other names:
#' 
#' The specificity has other names depending on research field:
#' - Critical Success Index, [csi()] 
#' - Threat Score, [tscore()]
#' 
#' @export
jaccard <- function(...) {
  UseMethod(
    generic = "jaccard",
    object  = ..1
  )
}

#' @rdname jaccard
#' @usage
#' ## Generic S3 method
#' ## for weighted Jaccard Index
#' weighted.jaccard(...)
#' @export
weighted.jaccard <- function(...) {
  UseMethod(
    generic = "weighted.jaccard",
    object  = ..1
  )
}

#' @export
csi <- function(...) {
  UseMethod(
    generic = "csi",
    object  = ..1
  )
}

#' @export
weighted.csi <- function(...) {
  UseMethod(
    generic = "weighted.csi",
    object  = ..1
  )
}

#' @export
tscore <- function(...) {
  UseMethod(
    generic = "tscore",
    object  = ..1
  )
}

#' @export
weighted.tscore <- function(...) {
  UseMethod(
    generic = "weighted.tscore",
    object  = ..1
  )
}

# script end;
