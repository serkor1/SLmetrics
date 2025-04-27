# objective: Test that area under the curve
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `auc.pr.curve()`-function", code = {

    # 0) skip on CRAN
    testthat::skip_on_cran()

    # 1) create auc.pr.curve()-wrapper
    pr_auc <- function(
      actual, 
      response, 
      w = NULL,
      micro = NULL,
      presorted = FALSE) {
      
      if (is.null(w)) {

        auc.pr.curve(
          actual    = actual,
          response  = response,
          presorted = presorted,
          micro     = micro,
          method    = 1
        )

      } else {

        weighted.auc.pr.curve(
          actual    = actual,
          response  = response,
          w         = w,
          method    = 1,
          presorted = presorted,
          micro     = micro
        )

      }

    }
    for (micro in c(NA, TRUE, FALSE)) {

      for (weighted in c(TRUE, FALSE)) {

        for (presorted in c(TRUE, FALSE)) {
  
          # 1) actual values
          # and response variables
          actual   <- create_factor()
          set.seed(1903)
          response <- create_response(
            actual = actual
          )

          set.seed(1903)
          response_ <- create_response(
            actual = actual
          )
          w        <- runif(length(actual))
    
          # 2) calculate AUC
          # based on methods
          
          label <- paste(
            "presorted =", presorted,
            "Weighted  =", weighted
          )
  
          # 1.2) calculate AUC
          # for each label
          reference <- py_prAUC(
            actual   = actual,
            response = response_,
            w        = if (weighted) w else NULL,
            micro    = if (is.na(micro)) NULL else ifelse(
              test = micro,
              yes  = "micro",
              no   = "macro"
            )
          )
  
          # 2.2) check for
          # equality
          if (!presorted) {
            testthat::expect_true(
              object = set_equal(
                reference,
                pr_auc(
                  actual    = actual,
                  response  = if (presorted) sort(response, TRUE) else response,
                  presorted = presorted,
                  micro     = if (is.na(micro)) NULL else micro,
                  w         = if (weighted) w else NULL
                )
              ),
              info = label
            )
          }
          
        }
        
      }

    }

  }
)
