# script: Utilities
# date: 2024-09-27
# author: Serkan Korkmaz, serkor1@duck.com
# objective: A collection of utilities
# to make the programming easier
# script start;

# summary line
full_line <- function() {

  console_width <- getOption("width")

  separator <- paste(
    rep("=", console_width),
    collapse = ""
    )

  # Print the separator
  cat(separator, sep = "\n")

}

# ROC-plots
roc_plot <- function(
  formula,
  groups = NULL,
  DT,
  xlab = NULL,
  ylab = NULL,
  main = NULL,
  add_poly = FALSE,
  ...) {


  lattice::xyplot(
    x        = formula,
    data     = DT,
    groups   = groups,
    type     = "l",
    xlab     = xlab,
    ylab     = ylab,
    main     = main,
    lwd      = 2,
    auto.key = list(
      space = "bottom",
      columns = length(unique(DT$label)),
      between.columns = 1
    ),
    xlim = c(0, 1),
    ylim = c(0, 1),
    panel = function(x, y, ...) {

      if (add_poly) {
      
        # 1) vertices for the polygon
        poly_x <- c(0, x, 1)
        poly_y <- c(0, y, 0)

        # 1.1) plot the polygon
        lattice::panel.polygon(
          poly_x,
          poly_y,
          col = grDevices::adjustcolor(
          col = "lightblue",
          alpha.f = 0.4),
          border = NA
        )
        
      }

      # 2) xyplot
      lattice::panel.xyplot(
        x = x,
        y = y, ...
      )

      # 3) plot the x = y
      # line (the chance line)
      lattice::panel.abline(
        a = 0,
        b = 1,
        lty = 2
        )
      

    },
    ...

  )

}


# OpenMP-tools

# OpenMP availability
openmp_available <- function() {

  # 1) check if available
  available <- .openmp_available()

  if (!available) {
    # throw warning and 
    # return NULL
    warning(
      "OpenMP is not available on your system!",
      call. = FALSE
    )

  }

  return(
    available
  )

}

# available threads
available_threads <- function() {

  # 1) get available
  # threads
  threads <- .available_threads()

  if (threads != -1) {
    return(threads)
  }
  
  NULL
  
}

# script end;
