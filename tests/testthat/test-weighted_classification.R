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
      "accuracy"    = accuracy,
      "baccuracy"   = baccuracy,

      # Zero-One Loss
      "zerooneloss" = zerooneloss,

      # specificity methods
      "specificity" = specificity,
      "tnr"         = tnr,
      "selectivity" = selectivity,


      # recall methods;
      "recall"      = recall,
      "sensitivity" = sensitivity,
      "tpr"         = tpr,

      # precision methods
      "precision"   = precision,
      "ppv"         = ppv,

      # fbeta methods
      "fbeta"       = fbeta,

      # likelihood methods
      "dor"         = dor,
      "plr"         = plr,
      "nlr"         = nlr,

      # jaccard methods
      "jaccard"     = jaccard,
      "tscore"      = tscore,
      "csi"         = csi,

      # mcc methods
      "mcc"         = mcc,
      "phi"         = phi,

      # fpr methods
      "fpr"         = fpr,
      "fallout"     = fallout,

      "fdr"         = fdr,
      "npv"         = npv,
      "fer"         = fer,

      "ckappa"      = ckappa

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
          .f(actual, predicted),
          as.numeric(.F(actual, predicted))
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
            .f(actual, predicted, micro = lgl),
            as.numeric(.F(actual, predicted, average = ifelse(lgl, "micro", "macro")))
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