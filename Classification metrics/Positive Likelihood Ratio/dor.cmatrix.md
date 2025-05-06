<div class="container">

<div role="main">

|             |                 |
|-------------|----------------:|
| dor.cmatrix | R Documentation |

## Diagnostic Odds Ratio

### Description

A generic S3 function to compute the *diagnostic odds ratio* score for a
classification model. This function dispatches to S3 methods in `dor()`
and performs no input validation. If you supply NA values or vectors of
unequal length (e.g. `length(x) != length(y)`), the underlying `C++`
code may trigger undefined behavior and crash your `R` session.

#### Defensive measures

Because `dor()` operates on raw pointers, pointer-level faults (e.g.
from NA or mismatched length) occur before any `R`-level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `dor()` in a "safe" validator that checks
for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_dor <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  dor(x, y, ...)
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

## evaluate diagnostic odds ratio
## via S3 dispatching
dor(confusion_matrix)

## additional performance metrics
## below
```

{% endcode %}

The `dor.factor()` method calls `cmatrix()` internally, so explicitly
invoking `dor.cmatrix()` yourself avoids duplicate computation, yielding
significant speed and memory effciency gains when you need multiple
evaluation metrics.

### Usage

``` R
## S3 method for class 'cmatrix'
dor(x, ...)
```

### Arguments

|       |                                         |
|-------|-----------------------------------------|
| `x`   | A confusion matrix created `cmatrix()`. |
| `...` | Arguments passed into other methods.    |

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


## Construct confusion
## matrix
confusion_matrix <- SLmetrics::cmatrix(
actual    = actual_classes,
predicted = predicted_classes
)

## Evaluate performance
SLmetrics::dor(confusion_matrix)

```
```

{% endcode %}
```

{% endcode %}
