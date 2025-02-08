# objective: Test that CoefficientOfDetermination
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
  desc = "Test `rsq()` function", code = {

    testthat::skip_on_cran()

    # 0) construct Coefficient Of Determination
    # wrapper
    wrapped_rsq <- function(
      actual, 
      predicted, 
      k = NULL, 
      w = NULL) {
      if (is.null(w)) {
        rsq(
          actual    = actual,
          predicted = predicted,
          k         = k
        )
      } else {
        weighted.rsq(
          actual    = actual,
          predicted = predicted,
          k         = k,
          w         = w
        )
      }
    }

    # 1) prepare
    # data
    data <- mtcars
    actual <- data$mpg
    weights <- runif(length(actual))

    for (weighted in c(TRUE, FALSE)) {
      for (adjusted in c(TRUE, FALSE)) {

        # 1) generate sensible
        # label information
        infor <- paste(
          "Weighted = ", weighted,
          "Adjusted = ", adjusted
        )

        # 2) test that values
        # are equal to target values
        model <- lm(
          formula = mpg ~ .,
          data    = data,
          weights = if (weighted) weights else NULL
        )

        # 2.1) extract values
        # from model
        target_value  <- if (adjusted) { summary(model)$adj.r.squared } else { summary(model)$r.squared }
        current_value <- wrapped_rsq(
          actual    = actual,
          predicted = fitted.values(model),
          w         = if (weighted) weights else NULL,
          k         = if (adjusted) ncol(model.matrix(model)) - 1 else 0
        )

        # 2.2) test that the values are sensible
        testthat::expect_true(is.numeric(target_value), info = info)
        testthat::expect_true(is.numeric(target_value), info = info)

        # 2.3) test for equality
        testthat::expect_true(
          object = set_equal(
            target  = as.numeric(target_value),
            current = as.numeric(current_value)
          ),
          info = info
        )

      }

    }
  }
)