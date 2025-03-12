#' @title Use OpenMP
#' 
#' @usage
#' ## enable OpenMP
#' openmp.on()
#' 
#' @description
#' This function allows you to enable or disable the use of OpenMP for parallelizing computations.
#' 
#' @param threads A positive <[integer]>-value (Default: None). If `threads` is missing, the `openmp.threads()` returns the number of available threads. If [NULL] all available threads will be used.
#' 
#' @example man/examples/scr_OpenMP.R
#'
#' @export
openmp.on <- function() {

  # 0) check availability
  # on system
  if (!openmp_available()) {
    return(NULL)
  }
  
  # 1) enable OpenMP
  .enable_openmp()

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

  # 0) check availability
  # on system
  if (!openmp_available()) {
    return(NULL)
  }
  
  # 1) disable OpenMP
  .disable_openmp()

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

  # 0) check availability
  # on system
  if (!openmp_available()) {
    return(NULL)
  }

  # 1) extract available
  # threads
  available <- .available_threads()
  
  # 1.1) if no threads have
  # been passed return the
  # number of threads
  if (missing(threads)) {
    return(available)
  }
  
  # 2) check the passed
  # number of checks
  if (!is.null(threads)) {

    # 2.1) if negative number
    # of threads - stop()
    # or the CPU explodes
    if (threads <= 0) {
      stop(
        "`threads`-argument must be a positive <integer>.",
         call. = FALSE
      )
    }

    # 2.2) if the user
    # passes thread count
    # higher than available
    # truncate it
    threads <- min(threads, available)
  }
  
  # 3) pass the threads to
  # OpenMP on the C++ side
  # and lets get rolling!
  # -1 means all systems go - wutang wutang!
  threads <- .use_threads(
    value = if (is.null(threads)) -1 else threads
  )
  
  message(sprintf("Using %d threads.", threads))
}
