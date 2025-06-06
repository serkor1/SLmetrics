# script: Test-setup
# author: Serkan Korkmaz, serkor1@duck.com
# date: 2024-09-21
# objective:
#
# Setup the test-environment for
# {scikit-learn} and {torch}
#
# script start;

# 1) set amount of test failures
testthat::set_max_fails(Inf)

# 2) set seed for all samples
set.seed(1903)

# 3) check if the r-reticulate virtual environment exists.
#    And install it otherwise.
tryCatch(
    expr = {
        if (!reticulate::virtualenv_exists()) {
            # 3.1) install the virtual environment
            reticulate::virtualenv_create()

            # 3.2) install packages for the virtual environment
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

        # 4) force reticulate to use the virtual environment
        #
        # NOTE: Has to be set between sessions
        # otherwise it won't compile
        reticulate::use_virtualenv()

        # 5) load scripts globally
        if (interactive()) {
            reticulate::source_python("tests/testthat/scikit-learn.py")
            reticulate::source_python("tests/testthat/pytorch.py")
            reticulate::source_python("tests/testthat/ref-scipy.py")

            source("tests/testthat/ref-classification-utils.R")
            source("tests/testthat/ref-classification.R")
            source("tests/testthat/ref-regression.R")
        } else {
            reticulate::source_python("scikit-learn.py")
            reticulate::source_python("pytorch.py")
            reticulate::source_python("ref-scipy.py")

            source("ref-classification-utils.R")
            source("ref-classification.R")
            source("ref-regression.R")
        }
    },
    error = function(error) {
        message("Please setup your Python environment.")
    }
)

# 6) create factors for classification
create_factor <- function(
    k = 3,
    balanced = TRUE,
    n = 1e2) {
    probs <- NULL

    if (!balanced) {
        probs <- rbeta(
            n = k,
            shape1 = 10,
            shape2 = 2
        )

        if (k > 2) {
            probs[which.min(probs)] <- 0
        }

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
    n = 1e2) {
    # 1) actual values
    actual <- abs(rnorm(n = n))

    # 2) predicted values
    predicted <- actual + abs(rnorm(n = n))

    # 3) generate weights
    weight <- runif(n)

    list(
        actual    = actual,
        predicted = predicted,
        weight    = weight
    )
}

create_response <- function(
    actual,
    as_matrix = TRUE) {
    # 0) construct raw probability
    # value function
    rand_sum <- function(n) {
        x <- sort(runif(n - 1))
        c(x, 1) - c(0, x)
    }

    # 1) construct response
    # values
    if (as_matrix) {
        response_values <- t(
            replicate(
                n = length(actual),
                rand_sum(
                    length(
                        levels(actual)
                    )
                )
            )
        )
    } else {
        response_values <- as.numeric(rand_sum(
            length(actual)
        ))
    }

    return(response_values)
}

# 7) testthat helper functions
set_equal <- function(...) {
    UseMethod("set_equal", object = ..1)
}

set_equal.default <- function(
    current,
    target,
    tolerance = 1e-9) {
    all.equal(
        target            = target,
        current           = current,
        tolerance         = tolerance,
        check.attributes  = FALSE,
        check.class       = FALSE
    )
}

set_equal.numeric <- function(
    current,
    target,
    rel_tol = 1e-9,
    abs_tol = 1e-12) {
    # 1) check equality in length
    if (length(current) != length(target)) {
        return(
            paste(
                "Lengths differ: current =",
                length(current),
                ", target =",
                length(target)
            )
        )
    }

    # 2) check values relative to tolerance
    differences <- abs(sum(current, -target, na.rm = TRUE))
    max_tolerable_diff <- pmax(rel_tol * abs(target), abs_tol, na.rm = TRUE)

    if (any(differences > max_tolerable_diff)) {
        return(
            paste(
                "Values differ beyond tolerance. Max difference =",
                max(differences, na.rm = TRUE)
            )
        )
    }

    TRUE
}

# 8) define all classification functions in {SLmetrics}
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

    # recall methods
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
    "ckappa"      = ckappa,
    "hammingloss" = hammingloss
)

# 9) define all weighted classification functions in {SLmetrics}
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

    # recall methods
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
    "ckappa"      = weighted.ckappa,
    "hammingloss" = weighted.hammingloss
)

# script end;
