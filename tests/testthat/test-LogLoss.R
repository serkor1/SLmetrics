# objective: Test that the metric
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(desc = "Test `entropy()`-function", code = {

  testthat::skip_on_cran()
  
  wrapped_logloss <- function(
    actual, 
    response, 
    w = NULL, 
    normalize = TRUE) {
    
    if (is.null(w)) {
      logloss(
        actual   = actual,
        response = response,
        normalize = normalize
      )
    } else {
      weighted.logloss(
        actual    = actual,
        response  = response,
        w         = w,
        normalize = normalize
      )
    }

  }

  for (k in 2:5) {
    
      actual <- create_factor(k = k)
      n <- length(actual)
      
      raw_probs <- matrix(rexp(n * k, rate = 1), nrow = n, ncol = k)
      row_sums  <- rowSums(raw_probs)
      response  <- raw_probs / row_sums 
    
      w <- runif(n)
      
      for (weighted in c(FALSE, TRUE)) {
        for (normalize in c(FALSE, TRUE)) {
          
      
          score <- wrapped_logloss(
            actual    = actual,
            response  = response,
            w         = if (weighted) w else NULL,
            normalize = normalize
          )
          
          actual_int <- as.integer(actual)
          label_seq  <- seq_len(k)
          
          py_score <- py_entropy(
            actual    = actual_int,
            qk        = response,
            normalize = normalize,
            w         = if (weighted) w else NULL,
            labels    = label_seq
          )
          
          info <- paste(
            "k =", k,
            "weighted =", weighted,
            "normalize =", normalize
          )
          
          testthat::expect_true(
            object = set_equal(
              current = as.numeric(score),
              target  = as.numeric(py_score)
            ),
            info = info
          )

        }
      }
    
  }
})
