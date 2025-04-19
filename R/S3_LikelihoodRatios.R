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
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
nlr <- function(...) {
  UseMethod(
    generic = "nlr"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE negative likelihood ratio
#' @templateVar .FUN nlr
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.nlr <- function(...) {
  UseMethod(
    generic = "weighted.nlr"
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
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
plr <- function(...) {
  UseMethod(
    generic = "plr"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE positive likelihood ratio
#' @templateVar .FUN plr
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.plr <- function(...) {
  UseMethod(
    generic = "weighted.plr"
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
#' 
#' @template generic_description
#' @template classification_standard_template
#'
#' @export
dor <- function(...) {
  UseMethod(
    generic = "dor"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE diagnostic odds ratio
#' @templateVar .FUN plr
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.dor <- function(...) {
  UseMethod(
    generic = "weighted.dor"
  )
}


# script end;
