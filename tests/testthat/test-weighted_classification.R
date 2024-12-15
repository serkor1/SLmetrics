# script: weighted classification metrics
# date: 2024-12-12
# author: Serkan Korkmaz, serkor1@duck.com
# objective: Test that the weighted metrics
# corresponds to target values
# script start;

testthat::test_that(
  desc = "Test that the weighted classification metrics equals {scikit-learn}-equivalents",
  code = {

    # 0) load functions from
    # {scikit-learn} and {pytorch}
    reticulate::source_python(
      "scikit-learn.py"
    )

    reticulate::source_python(
      "pytorch.py"
    )

    source("ref-manual.R")

    # 1) generate class
    # values
    actual    <- create_factor(balanced = TRUE)
    predicted <- create_factor(balanced = TRUE)
    weights   <- runif(n = length(actual))

    # 2) generate confusion matrix
    # from {SLmetrics} and {Python}
    sl_matrix <- cmatrix(
      actual    = actual,
      predicted = predicted,
      w         = weights
    )

    py_matrix <- py_cmatrix(
      actual    = actual,
      predicted = predicted,
      w         = weights
    )

    # 2.1) test for equality
    # in content
    testthat::expect_true(
      object = set_equal(
        current    = as.table(py_matrix),
        target     = as.table(sl_matrix)
      )
    )

    # 3) test that all metrics
    # that supports weighted classifications
    # are equal to target metrics
    sl_function <- list(
      # accuracy
      "accuracy"    = weighted.accuracy,
      "baccuracy"   = weighted.baccuracy,

      # Zero-One Loss
      "zerooneloss" = weighted.zerooneloss,

      # specificity methods
      "specificity" = weighted.specificity,
      "tnr"         = weighted.tnr,
      "selectivity" = weighted.selectivity,


      # recall methods;
      "recall"      = weighted.recall,
      "sensitivity" = weighted.sensitivity,
      "tpr"         = weighted.tpr,

      # precision methods
      "precision"   = weighted.precision,
      "ppv"         = weighted.ppv,

      # fbeta methods
      "fbeta"       = weighted.fbeta,

      # likelihood methods
      "dor"         = weighted.dor,
      "plr"         = weighted.plr,
      "nlr"         = weighted.nlr,

      # jaccard methods
      "jaccard"     = weighted.jaccard,
      "tscore"      = weighted.tscore,
      "csi"         = weighted.csi,

      # mcc methods
      "mcc"         = weighted.mcc,
      "phi"         = weighted.phi,

      # fpr methods
      "fpr"         = weighted.fpr,
      "fallout"     = weighted.fallout,

      "fdr"         = weighted.fdr,
      "npv"         = weighted.npv,
      "fer"         = weighted.fer,

      "ckappa"      = weighted.ckappa

    )

    # 4) test that the functions
    # returns the same values as
    # their python equivalents
    py_function <- Filter(
      Negate(is.null),

      setNames(
        lapply(seq_along(sl_function), function(i) {
          tryCatch(
            get(paste0("py_",names(sl_function)[i])),
            error = function(e) {
              NULL
            }
          )

        }),
        paste0("py_", names(sl_function))
      )
    )

    sl_function <- sl_function[
      names(sl_function) %in% gsub("py_", "", names(py_function))
    ]

    for (i in seq_along(sl_function)) {

      .f <-  sl_function[[i]]
      .F <-  py_function[[i]]

      testthat::expect_true(
        object = set_equal(
          .f(actual, predicted, w = weights),
          as.numeric(.F(actual, predicted, w = weights))
        ),
        label = paste(
          "Class-wise functions in",
          names(sl_function)[i],
          "not equivalent to {torch} or {scikit-learn}."
        )
      )

      for (lgl in c(TRUE, FALSE)) {

        testthat::expect_true(
          object = set_equal(
            .f(actual, predicted, micro = lgl, w =  weights),
            as.numeric(.F(actual, predicted, average = ifelse(lgl, "micro", "macro"),w = weights))
          ),
          label = paste(
            "Aggregated functions in",
            names(sl_function)[i],
            "not equivalent to {torch} or {scikit-learn}."
          )
        )

      }


    }




  }
)

# script end;