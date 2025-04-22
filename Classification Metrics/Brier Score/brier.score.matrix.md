<div class="container">

<div role="main">

|                    |                 |
|--------------------|----------------:|
| brier.score.matrix | R Documentation |

## Brier Score

### Description

A generic S3 function to compute the *brier score* score for a
classification model. This function dispatches to S3 methods in
`brier.score()` and performs no input validation. If you supply NA
values or vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `brier.score()` operates on raw pointers, pointer‑level faults
(e.g. from NA or mismatched length) occur before any `R`‑level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `brier.score()` in a “safe” validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_brier.score <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  brier.score(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## S3 method for class 'matrix'
brier.score(ok, qk, ...)
```

### Arguments

|       |                                                                                                                                                                                                                                                                                         |
|-------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `ok`  | A \<double\> indicator matrix with `n` samples and `k` classes.                                                                                                                                                                                                                         |
| `qk`  | A `n \times k` \<double\>-matrix of predicted probabilities. The `i`-th row should sum to 1 (i.e., a valid probability distribution over the `k` classes). The first column corresponds to the first factor level in `actual`, the second column to the second factor level, and so on. |
| `...` | Arguments passed into other methods.                                                                                                                                                                                                                                                    |

### Value

A \<double\>-value

### References

Gneiting, Tilmann, and Adrian E. Raftery. "Strictly proper scoring
rules, prediction, and estimation." Journal of the American statistical
Association 102.477 (2007): 359-378.

James, Gareth, et al. An introduction to statistical learning. Vol. 112.
No. 1. New York: springer, 2013.

Hastie, Trevor. "The elements of statistical learning: data mining,
inference, and prediction." (2009).

Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python."
the Journal of machine Learning research 12 (2011): 2825-2830.

### See Also

Other Classification: `accuracy()`, `auc.pr.curve()`, `auc.roc.curve()`,
`baccuracy()`, `ckappa()`, `cmatrix()`, `cross.entropy()`, `dor()`,
`fbeta()`, `fdr()`, `fer()`, `fmi()`, `fpr()`, `hammingloss()`,
`jaccard()`, `logloss()`, `mcc()`, `nlr()`, `npv()`, `plr()`,
`pr.curve()`, `precision()`, `recall()`, `relative.entropy()`,
`roc.curve()`, `shannon.entropy()`, `specificity()`, `zerooneloss()`

Other Supervised Learning: `accuracy()`, `auc.pr.curve()`,
`auc.roc.curve()`, `baccuracy()`, `ccc()`, `ckappa()`, `cmatrix()`,
`cross.entropy()`, `deviance.gamma()`, `deviance.poisson()`,
`deviance.tweedie()`, `dor()`, `fbeta()`, `fdr()`, `fer()`, `fmi()`,
`fpr()`, `hammingloss()`, `huberloss()`, `jaccard()`, `logloss()`,
`mae()`, `mape()`, `mcc()`, `mpe()`, `mse()`, `nlr()`, `npv()`,
`pinball()`, `plr()`, `pr.curve()`, `precision()`, `rae()`, `recall()`,
`relative.entropy()`, `rmse()`, `rmsle()`, `roc.curve()`, `rrmse()`,
`rrse()`, `rsq()`, `shannon.entropy()`, `smape()`, `specificity()`,
`zerooneloss()`

### Examples

``` R
## seed
set.seed(1903)

## The general setup
## with 3 classes
n_obs     <- 10
n_classes <- 3

## Generate indicator matrix
## with observed outcome (ok) and 
## its predicted probability matrix (qk)
ok <- diag(n_classes)[ sample.int(n_classes, n_obs, TRUE), ]
qk <- matrix(runif(n_obs * n_classes), n_obs, n_classes)
qk <- qk / rowSums(qk)

## Evaluate performance
SLmetrics::brier.score(
   ok = ok, 
   qk = qk
)

```
```

{% endcode %}
```

{% endcode %}
