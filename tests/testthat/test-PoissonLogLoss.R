# objective: Test that the metric
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(desc = "Test `logloss()`-function", code = {

  testthat::skip_on_cran()
  
  wrapped_logloss <- function(
    actual, 
    response, 
    w = NULL, 
    normalize = TRUE) {
    
    if (is.null(w)) {
      logloss(
        actual   = as.integer(actual),
        response = response,
        normalize = normalize
      )
    } else {
      weighted.logloss(
        actual    = as.integer(actual),
        response  = response,
        w         = w,
        normalize = normalize
      )
    }

  }

  ## generate values
  ## for Poisson Logloss
  actual   <- sample(x = c(1L:100L), size = 1e3, replace = TRUE)
  n        <- length(actual)
  response <- runif(n = n) 
  w        <- runif(n)
    
  for (weighted in c(FALSE, TRUE)) {
    for (normalize in c(FALSE, TRUE)) {

      score <- wrapped_logloss(
        actual    = as.integer(actual),
        response  = response,
        w         = if (weighted) w else NULL,
        normalize = normalize
      )
      
      ref_score <- ref_poisson_logloss(
        actual    = actual,
        response  = response,
        normalize = normalize,
        w         = if (weighted) w else NULL
      )
      
      info <- paste(
        "weighted  =", weighted,
        "normalize =", normalize
      )
      
      testthat::expect_true(
        object = set_equal(
          current = as.numeric(score),
          target  = as.numeric(ref_score)
        ),
        info = info
      )

    }
  }
 }
)
