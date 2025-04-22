<div class="container">

<div role="main">

|             |                 |
|-------------|----------------:|
| ccc.numeric | R Documentation |

## Concordance Correlation Coefficient

### Description

A generic S3 function to compute the *concordance correlation
coefficient* score for a regression model. This function dispatches to
S3 methods in `ccc()` and performs no input validation. If you supply NA
values or vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `ccc()` operates on raw pointers, pointer‑level faults (e.g.
from NA or mismatched length) occur before any `R`‑level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `ccc()` in a “safe” validator that checks
for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_ccc <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  ccc(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## S3 method for class 'numeric'
ccc(actual, predicted, correction = FALSE, ...)
```

### Arguments

|                       |                                                                                                                                |
|-----------------------|--------------------------------------------------------------------------------------------------------------------------------|
| `actual`, `predicted` | A pair of \<double\> vectors of length `n`.                                                                                    |
| `correction`          | A \<logical\> vector of length `1` (default: FALSE). If TRUE the variance and covariance will be adjusted with `\frac{1-n}{n}` |
| `...`                 | Arguments passed into other methods                                                                                            |

### Value

A \<double\> value

### References

James, Gareth, et al. An introduction to statistical learning. Vol. 112.
No. 1. New York: springer, 2013.

Hastie, Trevor. "The elements of statistical learning: data mining,
inference, and prediction." (2009).

Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for
scientific computing in Python." Nature methods 17.3 (2020): 261-272.

Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python."
the Journal of machine Learning research 12 (2011): 2825-2830.

### See Also

Other Regression: `deviance.gamma()`, `deviance.poisson()`,
`deviance.tweedie()`, `huberloss()`, `mae()`, `mape()`, `mpe()`,
`mse()`, `pinball()`, `rae()`, `rmse()`, `rmsle()`, `rrmse()`, `rrse()`,
`rsq()`, `smape()`

Other Supervised Learning: `accuracy()`, `auc.pr.curve()`,
`auc.roc.curve()`, `baccuracy()`, `brier.score()`, `ckappa()`,
`cmatrix()`, `cross.entropy()`, `deviance.gamma()`,
`deviance.poisson()`, `deviance.tweedie()`, `dor()`, `fbeta()`, `fdr()`,
`fer()`, `fmi()`, `fpr()`, `hammingloss()`, `huberloss()`, `jaccard()`,
`logloss()`, `mae()`, `mape()`, `mcc()`, `mpe()`, `mse()`, `nlr()`,
`npv()`, `pinball()`, `plr()`, `pr.curve()`, `precision()`, `rae()`,
`recall()`, `relative.entropy()`, `rmse()`, `rmsle()`, `roc.curve()`,
`rrmse()`, `rrse()`, `rsq()`, `shannon.entropy()`, `smape()`,
`specificity()`, `zerooneloss()`

### Examples

``` R
## Generate actual
## and predicted values
actual_values    <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)
predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)

## Evaluate performance
SLmetrics::ccc(
   actual    = actual_values, 
   predicted = predicted_values
)
```
```

{% endcode %}
```

{% endcode %}
