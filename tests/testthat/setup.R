# script: Test-setup
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective:
#
# Setup the test-environment for
# {scikit-learn} and {torch}
#
# script start;

# 0) set amount of test failures
testthat::set_max_fails(Inf)

# 1) set seed for all
# samples
set.seed(1903)

# 2) check if the r-reticulate
# virtual enviroment exists. And install
# it otherwise.
if (!reticulate::virtualenv_exists()) {

  # 2.1) install the virtual
  # environment
  reticulate::virtualenv_create()

  # 2.2) install packages
  # for the virtual environment
  reticulate::py_install(
    python_version = "3.10.x",
    packages = c(
      "numpy",
      "scipy",
      "mkl",
      "mkl-service",
      "mkl_fft",
      "mkl_random",
      "torch",
      "torchmetrics",
      "scikit-learn",
      "imblearn"
    )
  )

}

# 3) force reticulate to
# use virtual environment
#
# NOTE: Has to be set between sessions
# otherwise it won't compile
reticulate::use_virtualenv()


# 4) create factors
# for classification
create_factor <- function(
    k = 5,
    balanced = TRUE,
    n = 1e5) {

  probs <- NULL

  if (!balanced) {

    probs <- rbeta(
      n = k,
      shape1 = 10,
      shape2 = 2
    )

    probs[which.min(probs)] <- 0

    probs <- probs / sum(probs)

  }

  factor(
    x = sample(
      1:k,
      size = n,
      replace = TRUE,
      prob = probs
    ),
    labels = letters[1:k],
    levels = 1:k
  )
}

create_regression <- function(
    n = 1e5) {

  # 1) actual
  # values
  actual <- abs(rnorm(n = n))

  # 2) predicted
  # values
  predicted <- actual + abs(rnorm(n = n))

  # 3) generate
  # weights
  weight <- runif(n)

  list(
    actual    = actual,
    predicted = predicted,
    weight    = weight
  )
}

# 5) test-that helper
# functions

set_equal <- function(
    current,
    target,
    tolerance = 1e-9) {
  
  all.equal(
    target = target,
    current = current,
    tolerance = tolerance,
    check.attributes = FALSE,
    check.class = FALSE
  )

}

# 6) load scripts
# globally
reticulate::source_python(
  "scikit-learn.py"
)
reticulate::source_python(
  "pytorch.py"
)
source("ref-manual.R")

# 7) define all classification
# functions in {SLmetrics}
sl_classification <- list(
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

  # false positive
  "fpr"         = fpr,
  "fallout"     = fallout,

  # fmi methods
  "fmi"         = fmi,

  "fdr"         = fdr,
  "npv"         = npv,
  "fer"         = fer,

  "ckappa"      = ckappa

)

# 7) define all weighted classification
# functions in {SLmetrics}
sl_wclassification <- list(
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

  # false positive
  "fpr"         = weighted.fpr,
  "fallout"     = weighted.fallout,

  "fdr"         = weighted.fdr,
  "npv"         = weighted.npv,
  "fer"         = weighted.fer,

  "ckappa"      = weighted.ckappa

)

# 8) rewrite python
# matrix
py_cmatrix <- function(
  actual,
  predicted,
  w = NULL) {
  
  confusion_matrix <- py_confusion(
    actual,
    predicted,
    w = w
  )
  
  dimnames(confusion_matrix) <- list(
    levels(actual),
    levels(actual)
  )

  class(confusion_matrix) <- "cmatrix"
  

  confusion_matrix
}

# script end;
