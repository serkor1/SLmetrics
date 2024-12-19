# script: Imbalanced Classification
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-10-04
# objective: Test that aggregated
# classifcation works as in {scikit-learn}
# script start;

testthat::test_that(
  desc = "Aggregtetd classification in {SLmetrics} matches that of {scikit-learn} and {pytorch}",
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
      # NOTE: There is a bug in Scikit-learn
      # the fbeta score doesn't remove the NaNs
      # "fbeta"       = fbeta,
      # jaccard methods
      "jaccard"     = jaccard,
      "tscore"      = tscore,
      "csi"         = csi,
      # fpr methods
      "fpr"         = fpr,
      "fallout"     = fallout,
      # fmi methods
      "fdr"         = fdr,
      "npv"         = npv,
      "fer"         = fer
    )

    for (i in seq_along(sl_function)) {
      .f <-  sl_function[[i]]
      for (lgl in c(TRUE, FALSE)) {
        testthat::expect_true(
          object = set_equal(
            .f(actual, predicted, micro = lgl, na.rm = TRUE),
            .f(sl_matrix, micro = lgl, na.rm = TRUE)
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
     
      for (lgl in c(TRUE, FALSE)) {
        testthat::expect_true(
          object = set_equal(
            .f(actual, predicted, micro = lgl, na.rm = TRUE),
            as.numeric(.F(actual, predicted, average = ifelse(lgl, "micro", "macro")))
          ),
          label = paste(
            names(sl_function)[i],
            paste0("with micro:", lgl, ""),
            "not equivalent to {torch} or {scikit-learn}."
          )
        )
      }
    }
  }
)

# script end;
