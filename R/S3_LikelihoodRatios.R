# script: Likelihood Methods
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate Likelihood
# methods. Combines Positive, Negative and Diagnostic Odds Ratio
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @seealso
#' The [plr()]-function for the Positive Likehood Ratio (LR+)
#' 
#' @templateVar .TITLE negative likelihood ratio
#' @templateVar .FUN nlr
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' @template classification_standard_template
#' 
#' @export
nlr <- function(...) {
  UseMethod(
    generic = "nlr",
    object  = ..1
  )
}

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @rdname nlr
#' @usage
#' ## Generic S3 method
#' ## for weighted Negative
#' ## Likelihood Ratio
#' 
#' weighted.nlr(...)
#' @export
weighted.nlr <- function(...) {
  UseMethod(
    generic = "weighted.nlr",
    object  = ..1
  )
}

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @seealso
#'
#' The [nlr()]-function for the Negative Likehood Ratio (LR-)
#' 
#' @templateVar .TITLE positive likelihood ratio
#' @templateVar .FUN plr
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' @template classification_standard_template
#' 
#' @export
plr <- function(...) {
  UseMethod(
    generic = "plr",
    object  = ..1
  )
}

#' @rdname plr
#' 
#' @usage
#' ## Generic S3 method
#' ## for weighted Positive 
#' ##Likelihood Ratio
#' weighted.plr(...)
#' @export
weighted.plr <- function(...) {
  UseMethod(
    generic = "weighted.plr",
    object  = ..1
  )
}

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE diagnostic odds ratio
#' @templateVar .FUN dor
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT false
#' @template classification_standard_template
#' 
#' @export
dor <- function(...) {
  UseMethod(
    generic = "dor",
    object  = ..1
  )
}

#' @rdname dor
#' @usage
#' ## Generic S3 method
#' ## for weighted Diagnostic Odds Ratio
#' weighted.dor(...)
#' @export
weighted.dor <- function(...) {
  UseMethod(
    generic = "weighted.dor",
    object  = ..1
  )
}


# script end;
