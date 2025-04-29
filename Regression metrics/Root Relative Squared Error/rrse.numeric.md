<div class="container">

<div role="main">

|              |                 |
|--------------|----------------:|
| rrse.numeric | R Documentation |

## Root Relative Squared Error

### Description

A generic S3 function to compute the *root relative squared error* score
for a regression model. This function dispatches to S3 methods in
`rrse()` and performs no input validation. If you supply NA values or
vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `rrse()` operates on raw pointers, pointer-level faults (e.g.
from NA or mismatched length) occur before any `R`-level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `rrse()` in a "safe" validator that checks
for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_rrse <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  rrse(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## S3 method for class 'numeric'
rrse(actual, predicted, ...)
```

### Arguments

|                       |                                             |
|-----------------------|---------------------------------------------|
| `actual`, `predicted` | A pair of \<double\> vectors of length `n`. |
| `...`                 | Arguments passed into other methods         |

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

### Examples

``` R
## Generate actual
## and predicted values
actual_values    <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)
predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)

## Evaluate performance
SLmetrics::rrse(
   actual    = actual_values, 
   predicted = predicted_values
)
```
```

{% endcode %}
```

{% endcode %}
