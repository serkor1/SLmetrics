<div class="container">

<div role="main">

|                  |                 |
|------------------|----------------:|
| baccuracy.factor | R Documentation |

## Balanced Accuracy

### Description

A generic S3 function to compute the *balanced accuracy* score for a
classification model. This function dispatches to S3 methods in
`baccuracy()` and performs no input validation. If you supply NA values
or vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `baccuracy()` operates on raw pointers, pointer-level faults
(e.g. from NA or mismatched length) occur before any `R`-level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `baccuracy()` in a "safe" validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_baccuracy <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  baccuracy(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

#### Efficient multi-metric evaluation

For multiple performance evaluations of a classification model, first
compute the confusion matrix once via `cmatrix()`. All other performance
metrics can then be derived from this one object via S3 dispatching:


{% code overflow="wrap" lineNumbers="true" %}

``` R
## compute confusion matrix
confusion_matrix <- cmatrix(actual, predicted)

## evaluate balanced accuracy
## via S3 dispatching
baccuracy(confusion_matrix)

## additional performance metrics
## below
```

{% endcode %}

The `baccuracy.factor()` method calls `cmatrix()` internally, so
explicitly invoking `baccuracy.cmatrix()` yourself avoids duplicate
computation, yielding significant speed and memory effciency gains when
you need multiple evaluation metrics.

### Usage

``` R
## S3 method for class 'factor'
baccuracy(actual, predicted, adjust = FALSE, na.rm = TRUE, ...)
```

### Arguments

|                       |                                                                                                                                                                                                                                                                                                                                                                                                |
|-----------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `actual`, `predicted` | A pair of \<integer\> or \<factor\> vectors of length `n`, and `k` levels.                                                                                                                                                                                                                                                                                                                     |
| `adjust`              | A \<logical\> value (default: FALSE). If TRUE the metric is adjusted for random chance `\frac{1}{k}`.                                                                                                                                                                                                                                                                                          |
| `na.rm`               | A \<logical\> value of length `1` (default: TRUE). If TRUE, NA values are removed from the computation. This argument is only relevant when `micro != NULL`. When `na.rm = TRUE`, the computation corresponds to `sum(c(1, 2, NA), na.rm = TRUE) / length(na.omit(c(1, 2, NA)))`. When `na.rm = FALSE`, the computation corresponds to `sum(c(1, 2, NA), na.rm = TRUE) / length(c(1, 2, NA))`. |
| `...`                 | Arguments passed into other methods.                                                                                                                                                                                                                                                                                                                                                           |

### Value

A \<double\>-value

### References

James, Gareth, et al. An introduction to statistical learning. Vol. 112.
No. 1. New York: springer, 2013.

Hastie, Trevor. "The elements of statistical learning: data mining,
inference, and prediction." (2009).

Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python."
the Journal of machine Learning research 12 (2011): 2825-2830.

### Examples

``` R
## Classes and
## seed
set.seed(1903)
classes <- c("Kebab", "Falafel")

## Generate actual
## and predicted classes
actual_classes <- factor(
x = sample(x = classes, size = 1e3, replace = TRUE),
levels = c("Kebab", "Falafel")
)

predicted_classes <- factor(
x = sample(x = classes, size = 1e3, replace = TRUE),
levels = c("Kebab", "Falafel")
)

## Evaluate performance
SLmetrics::baccuracy(
   actual    = actual_classes, 
   predicted = predicted_classes
)


```
```

{% endcode %}
```

{% endcode %}
