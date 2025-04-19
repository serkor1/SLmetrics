# script: specificity
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2025-19-01
# objective: Generate method
# script start;

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE shannon entropy
#' @templateVar .FUN shannon.entropy
#' @templateVar .TASK Classification
#' 
#' @template generic_description
#' @template classification_entropy_template
#' 
#' @export
shannon.entropy <- function(...) {
  UseMethod(
    generic = "shannon.entropy"
  )
}

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE relative entropy
#' @templateVar .FUN relative.entropy
#' @templateVar .TASK Classification
#' 
#' @template generic_description
#' @template classification_entropy_template
#' 
#' @export
relative.entropy <- function(...) {
  UseMethod(
    generic = "relative.entropy"
  )
}

#' @title NULL
#' @usage NULL
#' @returns NULL
#' 
#' @templateVar .TITLE cross entropy
#' @templateVar .FUN cross.entropy
#' @templateVar .TASK Classification
#' 
#' @template generic_description
#' @template classification_entropy_template
#' 
#' @export
cross.entropy <- function(...) {
  UseMethod(
    generic = "cross.entropy"
  )
}

# script end;
