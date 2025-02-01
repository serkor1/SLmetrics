#' @title Use OpenMP
#' 
#' @usage
#' ## enable OpenMP
#' openmp.on()
#' 
#' @description
#' This function allows you to enable or disable the use of OpenMP for parallelizing computations.
#' 
#' @param threads A positive <[integer]>-value (Default: None]). If `threads` is missing, the `openmp.threads()` returns the number of available threads. If [NULL] all available threads will be used.
#' 
#' @example man/examples/scr_OpenMP.R
#'
#' @export
openmp.on <- function() {

  # 0) define OpenMP
  # usage
  usage <- .enable_openmp()

  # 1) check if OpenMP
  # is available
  if (is.null(usage)) {
    warning(
      "OpenMP is not available on your system!",
      call. = FALSE
    )

    invisible(return(NULL))
  }

  # 2) send messagge
  # to user if enabled
  message(
    "OpenMP enabled!"
  )

}

#' @rdname openmp.on
#' 
#' @usage
#' ## disable OpenMP
#' openmp.off()
#' 
#' @export
openmp.off <- function() {

  # 0) define OpenMP
  # usage
  usage <- .disable_openmp()

  # 1) check if OpenMP
  # is available
  if (is.null(usage)) {
    warning(
      "OpenMP is not available on your system!",
      call. = FALSE
    )

    invisible(return(NULL))
  }

  # 2) send messagge
  # to user if enabled
  message(
    "OpenMP disabled!"
  )

}

#' @rdname openmp.on
#' @usage
#' ## set number of threads
#' openmp.threads(threads)
#' 
#' @export
openmp.threads <- function(threads) {
  available <- .available_threads()
  
  if (missing(threads)) {
    if (available == 0) {
      warning("OpenMP is not available on your system!", call. = FALSE)
      return(invisible(NULL))
    }
    return(available)
  }
  
  if (!is.null(threads)) {
    if (threads <= 0) {
      stop("Number of threads must be a positive integer.", call. = FALSE)
    }
    threads <- min(threads, available)
  }
  
  usage <- .use_threads(if (is.null(threads)) -1 else threads)
  
  if (!is.null(threads) && usage == 0) {
    warning("OpenMP is not available on your system!", call. = FALSE)
    return(invisible(NULL))
  }
  
  message(sprintf("Using %d threads.", usage))
}
