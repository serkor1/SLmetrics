<div class="container">

<div role="main">

|                 |                 |
|-----------------|----------------:|
| logloss.integer | R Documentation |

## Logarithmic Loss

### Description

A generic S3 function to compute the *logarithmic loss* score for a
classification model. This function dispatches to S3 methods in
`logloss()` and performs no input validation. If you supply NA values or
vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `logloss()` operates on raw pointers, pointer‑level faults (e.g.
from NA or mismatched length) occur before any `R`‑level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `logloss()` in a “safe” validator that
checks for NA values and matching length, for example:

<div class="sourceCode r">

    safe_logloss <- function(x, y, ...) {
      stopifnot(
        !anyNA(x), !anyNA(y),
        length(x) == length(y)
      )
      logloss(x, y, ...)
    }

</div>

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## S3 method for class 'integer'
logloss(actual, response, normalize = TRUE, ...)
```

### Arguments

|             |                                                                                                                                                                                                                                                                                         |
|-------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `actual`    | A vector length `n`, and `k` levels. Can be of integer or factor.                                                                                                                                                                                                                       |
| `response`  | A `n \times k` \<double\>-matrix of predicted probabilities. The `i`-th row should sum to 1 (i.e., a valid probability distribution over the `k` classes). The first column corresponds to the first factor level in `actual`, the second column to the second factor level, and so on. |
| `normalize` | A \<logical\>-value (default: TRUE). If TRUE, the mean cross-entropy across all observations is returned; otherwise, the sum of cross-entropies is returned.                                                                                                                            |
| `...`       | Arguments passed into other methods.                                                                                                                                                                                                                                                    |

### Value

A \<double\>

### References

MacKay, David JC. Information theory, inference and learning algorithms.
Cambridge university press, 2003.

Kramer, Oliver, and Oliver Kramer. "Scikit-learn." Machine learning for
evolution strategies (2016): 45-53.

Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for
scientific computing in Python." Nature methods 17.3 (2020): 261-272.

### See Also

Other Classification: `accuracy()`, `auc.pr.curve()`, `auc.roc.curve()`,
`baccuracy()`, `brier.score()`, `ckappa()`, `cmatrix()`,
`cross.entropy()`, `dor()`, `fbeta()`, `fdr()`, `fer()`, `fmi()`,
`fpr()`, `hammingloss()`, `jaccard()`, `mcc()`, `nlr()`, `npv()`,
`plr()`, `pr.curve()`, `precision()`, `recall()`, `relative.entropy()`,
`roc.curve()`, `shannon.entropy()`, `specificity()`, `zerooneloss()`

Other Supervised Learning: `accuracy()`, `auc.pr.curve()`,
`auc.roc.curve()`, `baccuracy()`, `brier.score()`, `ccc()`, `ckappa()`,
`cmatrix()`, `cross.entropy()`, `deviance.gamma()`,
`deviance.poisson()`, `deviance.tweedie()`, `dor()`, `fbeta()`, `fdr()`,
`fer()`, `fmi()`, `fpr()`, `hammingloss()`, `huberloss()`, `jaccard()`,
`mae()`, `mape()`, `mcc()`, `mpe()`, `mse()`, `nlr()`, `npv()`,
`pinball()`, `plr()`, `pr.curve()`, `precision()`, `rae()`, `recall()`,
`relative.entropy()`, `rmse()`, `rmsle()`, `roc.curve()`, `rrmse()`,
`rrse()`, `rsq()`, `shannon.entropy()`, `smape()`, `specificity()`,
`zerooneloss()`

Other Entropy: `cross.entropy()`, `relative.entropy()`,
`shannon.entropy()`

</div>

</div>
