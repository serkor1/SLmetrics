# script: Precision Recall Curve
# date: 2024-12-28
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that it returns
# whatever it should return - and correctly.
# script start;

testthat::test_that(
  desc = "Test that `prROC()`-function works as expected", code = {

    testthat::skip_on_cran()

    # 0) construct prROC
    # wrapper
    wrapped_prROC <- function(
      actual,
      response,
      thresholds = NULL,
      w = NULL,
      presorted = FALSE) {
      
        if (is.null(w)) {

          prROC(
            actual,
            response,
            thresholds = if (is.null(thresholds))  {NULL} else thresholds,
            presorted  = presorted 
          )
  
        } else {
  
          weighted.prROC(
            actual,
            response,
            thresholds = if (is.null(thresholds))  {NULL} else thresholds,
            w = w,
            presorted  = presorted 
          )
  
        }
      
    }

    # 1) generate class
    # values
    actual     <- create_factor()
    response   <- create_response(actual, as_matrix = TRUE)
    w          <- runif(n = length(actual))
    thresholds <- seq(1, 0, length.out = 10)
    
    # 2) run tests
    for (presorted in c(TRUE, FALSE)) {
      for (custom_thresholds in c(TRUE, FALSE)) {
        for (weighted in c(TRUE, FALSE)) {

          # 2.1) generate information 
          # label
          info <- paste(
            "presorted = ", presorted,
            "custom_thresholds = ", custom_thresholds,
            "weighted = ", weighted
          )

          # 2.2) construct
          # prROC
          prROC_object <- wrapped_prROC(
            actual     = actual,
            response   = if (presorted) presort(response, decreasing = TRUE) else response,
            w          = if (weighted) w else NULL,
            thresholds = if (custom_thresholds) thresholds else NULL,
            presorted  = presorted
          )

          # 2.3) test that methods
          # works as expected
          testthat::expect_true(
            inherits(
              prROC_object,
              what = c("prROC", "data.frame")
            )
          )

          testthat::expect_no_condition(
            object = invisible(capture.output(print(prROC_object))),
            message = info
          )
  
          testthat::expect_no_condition(
            object = invisible(capture.output(summary(prROC_object))),
            message = info
          )
  
          testthat::expect_no_condition(
            object  = plot(prROC_object, panels = FALSE),
            message = info
          )
  
          testthat::expect_no_condition(
            object  = plot(prROC_object, panels = TRUE),
            message = info
          )

          # 2.4) construct
          # py_prROC
          prROC_reference <- do.call(
            rbind,
            lapply(
              py_prROC(
              actual    = actual,
              response  = response,
              w         = if (weighted) w else NULL),
              FUN = as.data.frame
              )
            )
          
          # 2.5) test if equal
          # only without custom thresholds
          # {scikit-learn} doesn't support
          # it
          if (!custom_thresholds) {
            testthat::expect_true(
              object = set_equal(
                current = prROC_object[is.finite(prROC_object$thresholds),],
                target  = prROC_reference[is.finite(prROC_reference$thresholds),]
              ),
              info = info
            )
          }
          
        }
      }
    }

  }
)
