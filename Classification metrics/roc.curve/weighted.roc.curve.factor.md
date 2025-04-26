<div class="container">

<div role="main">

|                           |                 |
|---------------------------|----------------:|
| weighted.roc.curve.factor | R Documentation |

## Reciever Operator Characteristics

### Description

A generic S3 function to compute the *reciever operator characteristics*
score for a classification model. This function dispatches to S3 methods
in `roc.curve()` and performs no input validation. If you supply NA
values or vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `roc.curve()` operates on raw pointers, pointer‑level faults
(e.g. from NA or mismatched length) occur before any `R`‑level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `roc.curve()` in a “safe” validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_roc.curve <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  roc.curve(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

#### Area under the curve

Use auc.roc.curve for calculating the area under the curve directly.

### Usage

``` R
## S3 method for class 'factor'
weighted.roc.curve(
  actual,
  response,
  w,
  thresholds = NULL,
  presorted = FALSE,
  ...
)
```

### Arguments

|              |                                                                                                                                                                                                                                                                                         |
|--------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `actual`     | A vector length `n`, and `k` levels. Can be of integer or factor.                                                                                                                                                                                                                       |
| `response`   | A `n \times k` \<double\>-matrix of predicted probabilities. The `i`-th row should sum to 1 (i.e., a valid probability distribution over the `k` classes). The first column corresponds to the first factor level in `actual`, the second column to the second factor level, and so on. |
| `w`          | A \<double\> vector of sample weights.                                                                                                                                                                                                                                                  |
| `thresholds` | An optional \<double\> vector of length `n` (default: NULL).                                                                                                                                                                                                                            |
| `presorted`  | Currently not working.                                                                                                                                                                                                                                                                  |
| `...`        | Arguments passed into other methods.                                                                                                                                                                                                                                                    |

### Value

A data.frame on the following form,

|             |                                                              |
|-------------|--------------------------------------------------------------|
| `threshold` | \<numeric\> Thresholds used to determine `tpr()` and `fpr()` |
| `level`     | \<character\> The level of the actual \<factor\>             |
| `label`     | \<character\> The levels of the actual \<factor\>            |
| `fpr`       | \<numeric\> The false positive rate                          |
| `tpr`       | \<numeric\> The true positve rate                            |

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

## Generate actual classes
## and response probabilities
actual_classes <- factor(
x = sample(
  x = classes, 
  size = 1e2, 
  replace = TRUE, 
  prob = c(0.7, 0.3)
)
)

response_probabilities <- ifelse(
actual_classes == "Kebab", 
rbeta(sum(actual_classes == "Kebab"), 2, 5), 
rbeta(sum(actual_classes == "Falafel"), 5, 2)
)

## Construct response
## matrix
probability_matrix <- cbind(
response_probabilities,
1 - response_probabilities
)


sample_weights <- runif(1e2)


## Visualize

plot(
SLmetrics::weighted.roc.curve(
 actual   = actual_classes, 
 response = probability_matrix,
 w        = sample_weights
 )
)



```
```

{% endcode %}
```

{% endcode %}
