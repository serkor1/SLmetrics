# script: Receiver Operating Characteristics
# date: 2024-04-27
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test the curve and its area under
# the curve
# script start;

testthat::test_that(
  desc = "Test that 'roc()'-family works as expected", code = {
    # 0) skip on CRAN as python
    # modules can't be run on CRAN
    # machines
    testthat::skip_on_cran()

    # 1) create wrapper function
    # of the ROC-family
    wrapper <- function(
      actual,
      response,
      thresholds = NULL,
      w = NULL,
      indices = NULL,
      estimator = 0) {
        # 1.0) container
        # for results
        output_list <- list()

        # 1.1) calculate ROC curves
        # conditional on weights
        if (is.null(w)) {
          output_list$curve <- roc.curve(
            actual     = actual,
            response   = response,
            thresholds = thresholds,
            indices    = indices
          )
        } else {
          output_list$curve <- weighted.roc.curve(
            actual     = actual,
            response   = response,
            w          = w,
            thresholds = thresholds,
            indices    = indices
          )
        }

        # 1.1) calculate AUC
        # conditional on weights
        if (is.null(w)) {
          output_list$auc <- auc.roc.curve(
            actual     = actual,
            response   = response,
            estimator  = estimator,
            indices    = indices
          )
        } else {
          output_list$auc <- weighted.auc.roc.curve(
            actual     = actual,
            response   = response,
            w          = w,
            estimator  = estimator,
            indices    = indices
          )
        }
      
        # 1.2) return the list
        return(output_list)
      
    }

    # 2) generate values
    # for testing
    actual     <- create_factor()
    response   <- create_response(actual, as_matrix = TRUE)
    w          <- runif(n = length(actual))
    thresholds <- seq(1, 0, length.out = 10)

    # 3) run the tests with presorted
    # values, custom thresholds and weights
    for (presorted in c(TRUE, FALSE)) {
      for (custom_thresholds in c(TRUE, FALSE)) {
        for (weighted in c(TRUE, FALSE)) {

          # 3.1) generate information
          # label
          info <- paste(
            "presorted:", presorted,
            "custom_thresholds:", custom_thresholds,
            "weighted:", weighted
          )

          # 3.2) construct values
          # and test internal consistency
          #
          # 3.2.1) value to be tested
          # throughout the script
          value <- wrapper(
            actual     = actual,
            response   = response,
            w          = if (weighted) w else NULL,
            thresholds = if (custom_thresholds) thresholds else NULL,
            indices    = if (presorted & !custom_thresholds) preorder(response, decreasing = TRUE) else NULL
          )

          # 3.2.2) the inverted values
          # ie. opposite of whether indices
          # have been provided
          inv_value <- wrapper(
            actual     = actual,
            response   = response,
            w          = if (weighted) w else NULL,
            thresholds = if (custom_thresholds) thresholds else NULL,
            indices    = if (!presorted & !custom_thresholds) preorder(response, decreasing = TRUE) else NULL
          )

          # 3.2.3) test that they are all
          # equal - so we know that when passing
          # indices the calculations are consistent.
          testthat::expect_equal(
            value,
            inv_value
          )

          # 3.3) test curve values against
          # {scikit-learn}
          reference_value <- do.call(
            what = rbind,
            args = lapply(
              X = py_ROC(actual = actual, response = response, w = if (weighted) w else NULL),
              FUN = as.data.frame
              )
          )

          # 3.3.1) only test without
          # custom thresholds as {scikit-learn}
          # does not provide this
          if (!custom_thresholds) {
            testthat::expect_true(
              object = set_equal(
                current = value$curve[is.finite(value$curve$threshold),],
                target  = reference_value[is.finite(reference_value$threshold),]
              ),
              info = info
            )
          }

          # 3.4) test AUC values against
          # {scikit-learn}
          reference_value <- py_rocAUC(
            actual   = actual,
            response = response,
            w        = if (weighted) w else NULL
          )

          # 3.4.1) no conditionals
          # are needed here
          testthat::expect_true(
            object = set_equal(
              current = value$auc,
              target  = reference_value
            ),
            info = info
          )

          # 3.5) test methods for ROC class
          # and its class
          testthat::expect_true(
            inherits(
              value$curve,
              what = c("ROC", "data.frame")
            )
          )

          testthat::expect_no_condition(
            object = invisible(capture.output(print(value$curve))),
            message = info
          )
  
          testthat::expect_no_condition(
            object = invisible(capture.output(summary(value$curve))),
            message = info
          )
  
          testthat::expect_no_condition(
            object  = plot(value$curve, panels = FALSE),
            message = info
          )
  
          testthat::expect_no_condition(
            object  = plot(value$curve, panels = TRUE),
            message = info
          )


        }
      }
    }


    # 4) calculate AUC with varying estimators
    # 0: Has already been tested
    # 1: micro average (micro for {scikit-learn})
    # 2: macro average (macro for {scikit-learn})
    for (estimator in c(1, 2)) {
        for (presorted in c(TRUE, FALSE)) {
            for (weighted in c(TRUE, FALSE)) {

                # 4.1) generate info
                info <- paste(
                  "estimator:", estimator,
                  "weighted:", weighted
                )
        
                # 4.2) generate values
                # to test
                value <- wrapper(
                  actual     = actual,
                  response   = response,
                  w          = if (weighted) w else NULL,
                  indices    = if (presorted) preorder(response, decreasing = TRUE) else NULL,
                  estimator  = estimator
                )
        
                # 4.3) generate values
                # to test against
                reference_value <- py_rocAUC(
                  actual   = actual,
                  response = response,
                  w        = if (weighted) w else NULL,
                  micro    = if (estimator == 1) "micro" else "macro"
                )
        
                # 4.4) test for equality
                # in values
                testthat::expect_true(
                  object = set_equal(
                    current = value$auc,
                    target  = reference_value
                  ),
                  info = info
                )
              }
        }
      
    }

  }
)

# script end;