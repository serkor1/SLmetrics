# script: Jaccard Methods
# date: 2024-10-06
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Create Methods
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @aliases csi tscore weighted.csi weighted.tscore
#' 
#' @templateVar .TITLE jaccard index
#' @templateVar .FUN jaccard
#' @templateVar .TASK Classification
#' @templateVar .MULTI_OUTPUT true
#' 
#' @template generic_description
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
    generic = "jaccard"
  )
}

#' @usage NULL
#' 
#' @templateVar .TITLE jaccard index
#' @templateVar .FUN jaccard
#' @templateVar .TASK Classification
#' 
#' @template generic_inherit
#' 
#' @export
weighted.jaccard <- function(...) {
  UseMethod(
    generic = "weighted.jaccard"
  )
}

#' @export
csi <- function(...) {
  UseMethod(
    generic = "csi"
  )
}

#' @export
weighted.csi <- function(...) {
  UseMethod(
    generic = "weighted.csi"
  )
}

#' @export
tscore <- function(...) {
  UseMethod(
    generic = "tscore"
  )
}

#' @export
weighted.tscore <- function(...) {
  UseMethod(
    generic = "weighted.tscore"
  )
}

# script end;
