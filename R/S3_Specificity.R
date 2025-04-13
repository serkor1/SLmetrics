# script: specificity
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-02
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @return NULL
#' 
#' @aliases tnr selectivity weighted.tnr weighted.selectivity
#' 
#' @section Other names:
#' 
#' The specificity has other names depending on research field:
#' - True Negative Rate, [tnr()] 
#' - Selectivity, [selectivity()]
#' 
#' 
#' @templateVar .TITLE specificity
#' @templateVar .FUN specificity
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' @template classification_standard_template
#' 
#' @export
specificity <- function(...) {
  UseMethod(
    generic = "specificity",
    object  = ..1
  )
}

#' @rdname specificity
#' @usage 
#' ## Generic S3 method
#' ## for weighted specificity
#' weighted.specificity(...)
#' @export
weighted.specificity <- function(...) {
    UseMethod(
      generic = "weighted.specificity",
      object  = ..1
    )
}

#' @export
tnr <- function(...) {
  UseMethod(
    generic = "tnr",
    object  = ..1
  )
}

#' @export
weighted.tnr <- function(...) {
    UseMethod(
      generic = "weighted.tnr",
      object  = ..1
    )
  }

#' @export
selectivity <- function(...) {
  UseMethod(
    generic = "selectivity",
    object  = ..1
  )
}

#' @export
weighted.selectivity <- function(...) {
  UseMethod(
    generic = "weighted.selectivity",
    object  = ..1
  )
}

# script end;
