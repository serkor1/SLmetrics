<div class="container">

<div role="main">

|                         |                 |
|-------------------------|----------------:|
| weighted.logloss.factor | R Documentation |

## Logarithmic Loss

### Description

A generic S3 function to compute the *logarithmic loss* score for a
classification model. This function dispatches to S3 methods in
`logloss()` and performs no input validation. If you supply NA values or
vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `logloss()` operates on raw pointers, pointer-level faults (e.g.
from NA or mismatched length) occur before any `R`-level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `logloss()` in a "safe" validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_logloss <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  logloss(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## S3 method for class 'factor'
weighted.logloss(actual, response, w, normalize = TRUE, ...)
```

### Arguments

|             |                                                                                                                                                                                                                                                                                         |
|-------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `actual`    | A vector length `n`, and `k` levels. Can be of integer or factor.                                                                                                                                                                                                                       |
| `response`  | A `n \times k` \<double\>-matrix of predicted probabilities. The `i`-th row should sum to 1 (i.e., a valid probability distribution over the `k` classes). The first column corresponds to the first factor level in `actual`, the second column to the second factor level, and so on. |
| `w`         | A \<double\> vector of sample weights.                                                                                                                                                                                                                                                  |
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

### Examples

``` R
## Classes and
## seed
set.seed(1903)
classes <- c("Kebab", "Falafel")

## Generate actual
## and predicted response
## probabilites
actual_classes <- factor(
x = sample(x = classes, size = 1e3, replace = TRUE),
levels = c("Kebab", "Falafel")
)

response <- runif(n = 1e3)

## Generate sample
## weights
sample_weights <- runif(
  n = 1e3
)


## Evaluate performance
SLmetrics::weighted.logloss(
   actual    = actual_classes, 
   response  = cbind(
 response,
 1 - response
   ),
   w = sample_weights
)

## Generate observed
## frequencies 
actual_frequency <- sample(10L:100L, size = 1e3, replace = TRUE)

SLmetrics::weighted.logloss(
   actual    = actual_frequency, 
   response  = response,
   w         = sample_weights
)

```
```

{% endcode %}
```

{% endcode %}
