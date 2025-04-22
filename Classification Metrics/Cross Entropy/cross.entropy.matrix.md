<div class="container">

<div role="main">

|                      |                 |
|----------------------|----------------:|
| cross.entropy.matrix | R Documentation |

## Cross Entropy

### Description

A generic S3 function to compute the *cross entropy* score for a
classification model. This function dispatches to S3 methods in
`cross.entropy()` and performs no input validation. If you supply NA
values or vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `cross.entropy()` operates on raw pointers, pointer‑level faults
(e.g. from NA or mismatched length) occur before any `R`‑level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `cross.entropy()` in a “safe” validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_cross.entropy <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  cross.entropy(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## S3 method for class 'matrix'
cross.entropy(pk, qk, dim = 0L, base = -1, ...)
```

### Arguments

|            |                                                                                                                                                    |
|------------|----------------------------------------------------------------------------------------------------------------------------------------------------|
| `pk`, `qk` | A pair of \<double\> matrices of length `n` of emprical probabilities `p` and estimated probabilities `q`.                                         |
| `dim`      | An \<integer\> value of length 1 (Default: 0). Defines the dimension along which to calculate the entropy (0: total, 1: row-wise, 2: column-wise). |
| `base`     | A \<double\> value of length 1 (Default: -1). The logarithmic base to use. Default value specifies natural logarithms.                             |
| `...`      | Arguments passed into other methods.                                                                                                               |

### Value

A \<double\> value or vector:

- A single \<double\> value (length 1) if `dim == 0`.

- A \<double\> vector with length equal to the length of rows if
  `dim == 1`.

- A \<double\> vector with length equal to the length of columns if
  `dim == 2`.

### References

MacKay, David JC. Information theory, inference and learning algorithms.
Cambridge university press, 2003.

Kramer, Oliver, and Oliver Kramer. "Scikit-learn." Machine learning for
evolution strategies (2016): 45-53.

Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for
scientific computing in Python." Nature methods 17.3 (2020): 261-272.

### See Also

Other Classification: `accuracy()`, `auc.pr.curve()`, `auc.roc.curve()`,
`baccuracy()`, `brier.score()`, `ckappa()`, `cmatrix()`, `dor()`,
`fbeta()`, `fdr()`, `fer()`, `fmi()`, `fpr()`, `hammingloss()`,
`jaccard()`, `logloss()`, `mcc()`, `nlr()`, `npv()`, `plr()`,
`pr.curve()`, `precision()`, `recall()`, `relative.entropy()`,
`roc.curve()`, `shannon.entropy()`, `specificity()`, `zerooneloss()`

Other Supervised Learning: `accuracy()`, `auc.pr.curve()`,
`auc.roc.curve()`, `baccuracy()`, `brier.score()`, `ccc()`, `ckappa()`,
`cmatrix()`, `deviance.gamma()`, `deviance.poisson()`,
`deviance.tweedie()`, `dor()`, `fbeta()`, `fdr()`, `fer()`, `fmi()`,
`fpr()`, `hammingloss()`, `huberloss()`, `jaccard()`, `logloss()`,
`mae()`, `mape()`, `mcc()`, `mpe()`, `mse()`, `nlr()`, `npv()`,
`pinball()`, `plr()`, `pr.curve()`, `precision()`, `rae()`, `recall()`,
`relative.entropy()`, `rmse()`, `rmsle()`, `roc.curve()`, `rrmse()`,
`rrse()`, `rsq()`, `shannon.entropy()`, `smape()`, `specificity()`,
`zerooneloss()`

Other Entropy: `logloss()`, `relative.entropy()`, `shannon.entropy()`
```

{% endcode %}
```

{% endcode %}
