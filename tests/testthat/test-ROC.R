# script: Reciever Operator Characteristics
# date: 2024-10-25
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that it returns
# whatever it should return - and correctly.
# script start;

testthat::test_that(
  desc = "Test that `ROC()`-function works as expected", code = {

    testthat::skip_on_cran()

    # 0) construct ROC
    # wrapper
    wrapped_ROC <- function(
      actual,
      response,
      thresholds = NULL,
      w = NULL,
      presorted = FALSE) {
      
        if (is.null(w)) {

          ROC(
            actual,
            response,
            thresholds = if (is.null(thresholds))  {NULL} else thresholds,
            presorted  = presorted 
          )
  
        } else {
  
          weighted.ROC(
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
          # ROC
          roc_object <- wrapped_ROC(
            actual     = actual,
            response   = if (presorted) sort(response, decreasing = TRUE) else response,
            w          = if (weighted) w else NULL,
            thresholds = if (custom_thresholds) thresholds else NULL,
            presorted  = presorted
          )

          # 2.3) test that methods
          # works as expected
          testthat::expect_true(
            inherits(
              roc_object,
              what = c("ROC", "data.frame")
            )
          )

          testthat::expect_no_condition(
            object = invisible(capture.output(print(roc_object))),
            message = info
          )
  
          testthat::expect_no_condition(
            object = invisible(capture.output(summary(roc_object))),
            message = info
          )
  
          testthat::expect_no_condition(
            object  = plot(roc_object, panels = FALSE),
            message = info
          )
  
          testthat::expect_no_condition(
            object  = plot(roc_object, panels = TRUE),
            message = info
          )

          # 2.4) construct
          # py_roc
          roc_reference <- do.call(
            rbind,
            lapply(
              py_ROC(
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
                current = roc_object[is.finite(roc_object$thresholds),],
                target  = roc_reference[is.finite(roc_reference$thresholds),]
              ),
              info = info
            )
          }
          
        }
      }
    }

  }
)
