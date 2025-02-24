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
      ordered = FALSE,
      method = 0) {
      
      if (is.null(w)) {

        roc.auc(
          actual   = actual,
          response = response,
          ordered  = ordered,
          method   = method
        )

      } else {

        weighted.roc.auc(
          actual   = actual,
          response = response,
          w        = w,
          method   = method,
          ordered  = ordered
        )

      }

    }

    for (ordered in c(TRUE, FALSE)) {

      # 1) actual values
      # and response variables
      actual   <- create_factor()
      response <- runif(length(actual))
      w        <- runif(length(actual))

      if (ordered) {
        # 1.1) create order
        # by response
        idx      <- order(response, decreasing = TRUE)
        actual   <- actual[idx]
        response <- response[idx]
        w        <- w[idx]

      }

      # 1.2) calculate ROC object
      # and store
      object <- ROC(
        actual   = actual,
        response = response
      )

      # 2) calculate AUC
      # based on methods
      for (method in c(0, 1)) {

        label <- paste(
          "Method  = ", method,
          "Ordered = ", ordered
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
              ordered  = ordered
            )
          ),
          info = label
        )
        
      
      }
    }
  }
)

testthat::test_that(
  desc = "Test `pr.auc()`-function", code = {

    # 0) skip on CRAN
    testthat::skip_on_cran()

    # 1) create roc.auc()-wrapper
    pr_auc <- function(
      actual, 
      response, 
      w = NULL,
      ordered = FALSE,
      method = 0) {
      
      if (is.null(w)) {

        pr.auc(
          actual   = actual,
          response = response,
          ordered  = ordered,
          method   = method
        )

      } else {

        weighted.pr.auc(
          actual   = actual,
          response = response,
          w        = w,
          method   = method,
          ordered  = ordered
        )

      }

    }

    for (ordered in c(TRUE, FALSE)) {

      # 1) actual values
      # and response variables
      actual   <- create_factor(k = 2)
      response <- runif(length(actual))
      w        <- runif(length(actual))

      if (ordered) {
        # 1.1) create order
        # by response
        idx      <- order(response,decreasing = TRUE)
        actual   <- actual[idx]
        response <- response[idx]
        w        <- w[idx]

      }

      # 1.2) calculate precision-recall
      # object
      object <- prROC(
        actual   = actual,
        response = response
      )

      # 2) calculate AUC
      # based on methods
      for (method in c(0, 1)) {

        label <- paste(
          "Method  = ", method,
          "Ordered = ", ordered
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
              ordered  = ordered
            )
          ),
          info = label
        )
        
      
      }
    }
  }
)
