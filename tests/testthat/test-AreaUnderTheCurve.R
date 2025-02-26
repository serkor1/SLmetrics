# objective: Test that area under the curve
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `roc.auc()`-function", code = {

    # 0) skip on CRAN
    testthat::skip_on_cran()

    # 1) create roc.auc()-wrapper
    roc_auc <- function(
      actual, 
      response, 
      w = NULL,
      presorted = FALSE,
      method = 0) {
      
      if (is.null(w)) {

        roc.auc(
          actual   = actual,
          response = response,
          presorted  = presorted,
          method   = method
        )

      } else {

        weighted.roc.auc(
          actual   = actual,
          response = response,
          w        = w,
          method   = method,
          presorted  = presorted
        )

      }

    }

    for (weighted in c(TRUE, FALSE)) {

      for (presorted in c(TRUE, FALSE)) {

        # 1) actual values
        # and response variables
        actual   <- create_factor(k = 2)
        response <- runif(length(actual))
        w        <- runif(length(actual))
  
        if (presorted) {
          # 1.1) create order
          # by response
          idx      <- order(response, decreasing = TRUE)
          actual   <- actual[idx]
          response <- response[idx]
          w        <- w[idx]
  
        }

        response <- matrix(
          data = cbind(
            response,
            response
          ),
          nrow = length(actual)
        )
  
        # 1.2) calculate ROC object
        # and store
        if (weighted) {

          object <- weighted.ROC(
            actual   = actual,
            response = response,
            w        = w
          )

        } else {

          object <- ROC(
            actual   = actual,
            response = response
          )


        }
        
  
        # 2) calculate AUC
        # based on methods
        for (method in c(0, 1)) {
  
          label <- paste(
            "Method   =", method,
            "presorted  =", presorted,
            "Weighted =", weighted
          )
  
          # 1.1) extract list
          # of labels
          x_list <- split(
            x = object,
            f = object$label
          )
  
          # 1.2) calculate AUC
          # for each label
          reference <- vapply(
            x_list, 
            function(x) {
              auc(
                y = x$tpr,
                x = x$fpr,
                method = method
              )
            }, 
            FUN.VALUE = numeric(1),
            USE.NAMES = TRUE
          )
  
          names(reference) <- names(x_list)
  
          # 2.2) check for
          # equality
          testthat::expect_true(
            object = set_equal(
              reference,
              roc_auc(
                actual   = actual,
                response = response,
                method   = method,
                presorted  = presorted,
                w        = if (weighted) w else NULL
              )
            ),
            info = label
          )
          
        
        }
      }
      
    }

    
  }
)

testthat::test_that(
  desc = "Test `pr.auc()`-function", code = {

    # 0) skip on CRAN
    testthat::skip_on_cran()

    # 1) create pr.auc()-wrapper
    pr_auc <- function(
      actual, 
      response, 
      w = NULL,
      presorted = FALSE,
      method = 0) {
      
      if (is.null(w)) {

        pr.auc(
          actual   = actual,
          response = response,
          presorted  = presorted,
          method   = method
        )

      } else {

        weighted.pr.auc(
          actual   = actual,
          response = response,
          w        = w,
          method   = method,
          presorted  = presorted
        )

      }

    }

    for (weighted in c(TRUE, FALSE)) {

      for (presorted in c(TRUE, FALSE)) {

        # 1) actual values
        # and response variables
        actual   <- create_factor(k = 2)
        response <- runif(length(actual))
        w        <- runif(length(actual))
  
        if (presorted) {
          # 1.1) create order
          # by response
          idx      <- order(response,decreasing = TRUE)
          actual   <- actual[idx]
          response <- response[idx]
          w        <- w[idx]
  
        }

        response <- matrix(
          data = cbind(
            response,
            response
          ),
          nrow = length(actual)
        )
  
        # 1.2) calculate precision-recall
        # object
        if (weighted) {

          object <- weighted.prROC(
            actual   = actual,
            response = response,
            w        = w
          )

        } else {

          object <- prROC(
            actual   = actual,
            response = response
          )

        }
        
  
        # 2) calculate AUC
        # based on methods
        for (method in c(0, 1)) {
  
          label <- paste(
            "Method  = ", method,
            "presorted = ", presorted,
            "Weighted=", weighted
          )
  
          # 1.1) extract list
          # of labels
          x_list <- split(
            x = object,
            f = object$label
          )
  
          # 1.2) calculate AUC
          # for each label
          reference <- vapply(
            x_list, 
            function(x) {
              auc(
                y = x$precision,
                x = x$recall,
                method = method
              )
            }, 
            FUN.VALUE = numeric(1),
            USE.NAMES = TRUE
          )
  
          names(reference) <- names(x_list)
  
          # 2.2) check for
          # equality
          testthat::expect_true(
            object = set_equal(
              reference,
              pr_auc(
                actual   = actual,
                response = response,
                method   = method,
                presorted  = presorted,
                w        = if (weighted) w else NULL
              )
            ),
            info = label
          )
          
        
        }
      }

    }

  }
)
