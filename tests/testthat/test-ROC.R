# script: Reciever Operator Characteristics
# date: 2024-10-25
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that it returns
# whatever it should return - and correctly.
# script start;

testthat::test_that(
  desc = "Test that `ROC()`-function works as expected",
  code = {

    # 0) load functions from
    # {scikit-learn} and {pytorch}
    reticulate::source_python(
      "scikit-learn.py"
    )

    n <- 1e3
    k <- 4
    # 1) generate
    # factors
    set.seed(1903)
    actual <- create_factor(
      k = k,
      n = n
    )

    # 2) generate
    # response variable
    response <- rbeta(
      n = n,
      shape1 = 20,
      shape2 = 2
    )

    # 3) generate datasets
    # with ROC
    current <- SLmetrics::ROC(
      actual   = actual,
      response = response
    )

    target <- ROC(
      actual     = actual,
      response   = response,
      threshold = response
    )

    # 4) test if its
    # equal
    testthat::expect_true(
      set_equal(
        current = current,
        target  = target
      )
    )

    # 5) calculate
    # values using
    # scikit-learn
    py_value <- list()
    for (i in 1:k) {

      py_metric <- py_roc(
        actual = as.numeric(
          as.numeric(actual) == i
        ),
        response = response,
        pos_label = 1
      )

      names(py_metric) <- c("fpr", "tpr", "threshold")

      py_metric <- as.data.frame(py_metric)[-1,]


      py_metric$level <- i
      py_metric$label <- letters[i]

      py_metric[[i]] <- py_metric

    }


    py_value <- do.call(
      rbind,
      py_value
    )

    py_value <- py_value[ , names(current)]

    # 6) test if its
    # equal
    testthat::expect_true(
      set_equal(
        current = current,
        target  = target
      )
    )


    # 7) Test that custom
    # thresholds works
    # as expected
    thresholds <- seq(
      0,
      1,
      length.out = 10
    )

    testthat::expect_true(
      set_equal(
        current = ROC(
          actual     = actual,
          response   = response,
          thresholds = thresholds
        ),
        target  = ref_ROC(
          actual     = actual,
          response   = response,
          thresholds = thresholds
        )
      )
    )


  }
)

testthat::test_that(
  desc = "Test that `prROC()`-function works as expected",
  code = {

    # 0) load functions from
    # {scikit-learn} and {pytorch}
    reticulate::source_python(
      "scikit-learn.py"
    )

    n <- 1e3
    k <- 4
    # 1) generate
    # factors
    set.seed(1903)
    actual <- create_factor(
      k = k,
      n = n
    )

    # 2) generate
    # response variable
    response <- rbeta(
      n = n,
      shape1 = 20,
      shape2 = 2
    )

    # 3) generate datasets
    # with ROC
    current <- prROC(
      actual   = actual,
      response = response
    )

    target <- prROC(
      actual     = actual,
      response   = response,
      threshold = response
    )

    # 4) test if its
    # equal
    testthat::expect_true(
      set_equal(
        current = current,
        target  = target
      )
    )

    # 5) calculate
    # values using
    # scikit-learn
    py_value <- list()
    for (i in 1:k) {

      py_metric <- py_prROC(
        actual = as.numeric(
          as.numeric(actual) == i
        ),
        response = response,
        pos_label = 1
      )


      py_metric <- lapply(
        py_metric,
        function(x) {
          x[1:n]
        }
      )

      names(py_metric) <- c("precision", "recall", "threshold")



      py_metric$level <- i
      py_metric$label <- letters[i]


      py_metric <- as.data.frame(py_metric)
      py_metric <- py_metric[order(-py_metric$threshold, py_metric$level, decreasing = FALSE),]

      py_value[[i]] <- py_metric

    }


    py_value <- do.call(
      rbind,
      py_value
    )

    py_value <- py_value[ , names(current)]

    # 6) test if its
    # equal
    testthat::expect_true(
      set_equal(
        current = prROC(
          actual,
          response
        ),
        target  = py_value
      )
    )

    
    # 7) Test that custom
    # thresholds works
    # as expected
    thresholds <- seq(
      0,
      1,
      length.out = 10
    )

    testthat::expect_true(
      set_equal(
        current = prROC(
          actual     = actual,
          response   = response,
          thresholds = thresholds
        ),
        target  = ref_prROC(
          actual     = actual,
          response   = response,
          thresholds = thresholds
        )
      )
    )


  }
)

# script end;



