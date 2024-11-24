# script: Test-setup
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective:
#
# Setup the test-environment for
# {scikit-learn} and {torch}
#
# script start;

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


# script end;
