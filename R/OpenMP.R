# script: Accuracy
# date: 2024-10-05
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Generate methods for accuracy
# script start;

#' @title Control OpenMP
#' @rdname utils_OpenMP
#' @name OpenMP
#' 
#' @usage
#' ## enable OpenMP
#' openmp.on()
#' 
#' @description
#' Enable or disable OpenMP parallelization for computations.
#' 
#' ## Disclaimer
#' This toggle is a brute-force implementation and does **not** guard against data races or nested parallel regions.
#' Nested OpenMP regions can introduce subtle race conditions if multiple layers of parallelism access shared data concurrently.
#' If you combine this package’s OpenMP switch with other parallel machine-learning routines, you may encounter undefined behavior.
#' 
#' @examples
#' \dontrun{
#' ## enable OpenMP
#' SLmetrics::openmp.on()
#'
#' ## disable OpenMP
#' SLmetrics::openmp.off()
#'
#' ## available threads
#' SLmetrics::openmp.threads()
#' 
#' ## set number of threads
#' SLmetrics::openmp.threads(2)
#'}
#' 
#' 
#' @returns
#' If OpenMP is unavailable, the function returns [NULL].
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

#' @rdname utils_OpenMP
#' @inherit OpenMP description
#' @inherit OPenMP return
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

#' @rdname utils_OpenMP
#' @inherit OpenMP description
#' @inherit OPenMP return
#' 
#' @usage
#' ## set number of threads
#' openmp.threads(threads)
#' 
#' @param threads A positive <[integer]>-value (Default: None). If `threads` is missing, the `openmp.threads()` returns the number of available threads. If [NULL] all available threads will be used.
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

# script end;