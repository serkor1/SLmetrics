# objective: Test that Accuracy
# implemented in {SLmetrics} is aligned with
# target functions.

testthat::test_that(
    desc = "Test likelihood functions", code = {
        testthat::skip_on_cran()

        # 0) Likelihood Ratios
        # from {SLmetrics}
        likelihood <- function(actual,
                               predicted,
                               w = NULL) {
            if (is.null(w)) {
                c(
                    dor(actual, predicted),
                    plr(actual, predicted),
                    nlr(actual, predicted)
                )
            } else {
                c(
                    weighted.dor(actual, predicted, w),
                    weighted.plr(actual, predicted, w),
                    weighted.nlr(actual, predicted, w)
                )
            }
        }

        # 1) Reference likelihood
        # Ratios
        ref_likelihood <- function(actual,
                                   predicted,
                                   w = NULL) {
            c(
                ref_dor(actual, predicted, w = w),
                ref_plr(actual, predicted, w = w),
                ref_nlr(actual, predicted, w = w)
            )
        }

        for (balanced in c(FALSE, TRUE)) {
            # 1) generate class
            # values
            actual <- create_factor(balanced = balanced, k = 2)
            predicted <- create_factor(balanced = balanced, k = 2)
            w <- runif(n = length(actual))

            for (weighted in c(TRUE, FALSE)) {
                # 2.1) generate sensible
                # label information
                info <- paste(
                    "Balanced = ", balanced,
                    "Weighted = ", weighted
                )

                # 2.2) generate score
                # from {slmetrics}
                score <- likelihood(
                    actual     = actual,
                    predicted  = predicted,
                    w          = if (weighted) w else NULL
                )

                # 2.3) test that the values
                # are sensible the values
                # can be NA
                testthat::expect_true(is.numeric(score), info = info)
                testthat::expect_true(length(score) == 3, info = info)

                # 2.4) test that the values
                # are equal to target value

                # 2.4.1) calculate ref_score
                ref_score <- ref_likelihood(
                    actual     = actual,
                    predicted  = predicted,
                    w          = if (weighted) w else NULL
                )

                # 2.4.2) test for equality
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
