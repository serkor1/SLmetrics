# script: Test implementation of f_beta score
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective: Check that the implementation of the
# f_beta score matches that of sklearn
# script start;

testthat::test_that(
  desc = "Test that `fbeta()` matches that of sklearn for all beta values and aggregations",
  code = {


    # 0) source the python
    # program
    reticulate::source_python(
      "scikit-learn.py"
    )

    # 1) create two vectors
    # of classes where one class
    # has not been predicted at all

    # 1.1) actual
    # values
    actual <- factor(
      x = sample(
        x = 1:3,
        size = 1e3,
        replace = TRUE,
        prob = c(0,0.5,0.5)
      ),
      levels = c(1:3),
      labels = letters[1:3]
    )

    # 1.2) predicted
    # values
    predicted <- factor(
      x = sample(
        1:3,
        size = 1e3,
        replace = TRUE,
        prob = c(0,0.5,0.5)
      ),
      levels = c(1:3),
      labels = letters[1:3]
    )

    # 2) test that
    for (lgl in c(FALSE, TRUE)) {
      for (beta in c(1,2,3,4,5)){

        # 2.1) calcuale scores
        py_score <- as.numeric(
          py_fbeta(
            actual    = actual,
            predicted = predicted,
            beta      = beta,
            average   = if (lgl)
              "micro"
            else
              NULL
          )
        )

        sl_score <- fbeta(
          actual    = actual,
          predicted = predicted,
          beta      = beta,
          aggregate = lgl
        )


        testthat::expect_true(
          all(
            is.numeric(sl_score),
            length(sl_score) == if (lgl) 1 else 3
          )
        )

        testthat::expect_true(
          all.equal(
            target  = na.omit(sl_score),
            current = py_score,
            tolerance =  1e-9,
            check.attributes = FALSE,
            check.class = FALSE
          )
        )

        if (!lgl) {

          testthat::expect_true(
            all.equal(
              target  = mean(sl_score, na.rm = TRUE),
              current = py_fbeta(
                actual    = actual,
                predicted = predicted,
                beta      = beta,
                average   = "macro"
              ),
              tolerance =  1e-9,
              check.attributes = FALSE,
              check.class = FALSE
            )
          )

        }

      }
    }


  }
)

# script end;
