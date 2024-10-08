# script: Imbalanced Classification
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-04
# objective: The imbalanced classification
# tests wether the functions have been implemented as
# in {scikit-learn}
# script start;

testthat::test_that(
  desc = "Imbalanced classification in {SLmetrics} matches that of {scikit-learn} and {pytorch}",
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
    actual    <- create_factor(balanced = FALSE)
    predicted <- create_factor(balanced = FALSE)

    # 2) generate confusion matrix
    # from {SLmetrics} and {Python}
    sl_matrix <- cmatrix(
      actual    = actual,
      predicted = predicted
    )

    py_matrix <- py_cmatrix(
      actual    = actual,
      predicted = predicted
    )

    # 2.1) test for equality
    # in content
    testthat::expect_true(
      object = set_equal(
        current    = as.table(py_matrix),
        target     = as.table(sl_matrix)
      )
    )

    # 3) test that methods
    # work and returns the same values
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

      # fmi methods
      "fmi"         = fmi,

      "fdr"         = fdr,
      "npv"         = npv,
      "fer"         = fer,

      "ckappa"      = ckappa
    )

    for (i in seq_along(sl_function)) {

      .f <-  sl_function[[i]]

      testthat::expect_true(
        object = set_equal(
          .f(actual, predicted, na.rm = FALSE),
          .f(sl_matrix, na.rm = FALSE)
        ),
        label = paste(
          "Class-wise metods in", names(sl_function)[i], "not equivalent."
        )
      )

      for (lgl in c(TRUE, FALSE)) {

        testthat::expect_true(
          object = set_equal(
            .f(actual, predicted, micro = lgl, na.rm = FALSE),
            .f(sl_matrix, micro = lgl, na.rm = FALSE)
          ),
          label = paste(
            "Aggregated methods in", names(sl_function)[i], "not equivalent."
          )
        )

      }


    }

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

      # 1) replace missing with 0
      # as in python
      sl_measure <- .f(actual, predicted, na.rm = TRUE);
      sl_measure[is.na(sl_measure) | is.nan(sl_measure)] <- 0

      py_measure <- as.numeric(reticulate::py_suppress_warnings(.F(actual, predicted)))
      py_measure[is.na(py_measure) | is.nan(py_measure)] <- 0

      testthat::expect_true(
        object = set_equal(
          sl_measure,
          py_measure

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
            # NOTE: There is a bug in Scikit-learn
            # the fbeta score doesn't remove the NaNs
            .f(actual, predicted, micro = lgl, na.rm = if (names(py_function)[i] == "py_fbeta") FALSE else TRUE) ,
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
