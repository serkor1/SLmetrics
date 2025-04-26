<div class="container">

<div role="main">

|                               |                 |
|-------------------------------|----------------:|
| weighted.auc.roc.curve.factor | R Documentation |

## Area under the Receiver Operator Characteristics Curve

### Description

A generic S3 function to compute the *area under the receiver operator
characteristics curve* score for a classification model. This function
dispatches to S3 methods in `auc.roc.curve()` and performs no input
validation. If you supply NA values or vectors of unequal length (e.g.
`length(x) != length(y)`), the underlying `C++` code may trigger
undefined behavior and crash your `R` session.

#### Defensive measures

Because `auc.roc.curve()` operates on raw pointers, pointer‑level faults
(e.g. from NA or mismatched length) occur before any `R`‑level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `auc.roc.curve()` in a “safe” validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_auc.roc.curve <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  auc.roc.curve(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

#### Visualizing area under the receiver operator characteristics curve

Use `roc.curve()` to construct the data.frame and use plot to visualize
the area under the curve.

### Usage

``` R
## S3 method for class 'factor'
weighted.auc.roc.curve(actual, response, w, micro = NULL, method = 0L, ...)
```

### Arguments

|            |                                                                                                                                                                                                                                                                                         |
|------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `actual`   | A vector length `n`, and `k` levels. Can be of integer or factor.                                                                                                                                                                                                                       |
| `response` | A `n \times k` \<double\>-matrix of predicted probabilities. The `i`-th row should sum to 1 (i.e., a valid probability distribution over the `k` classes). The first column corresponds to the first factor level in `actual`, the second column to the second factor level, and so on. |
| `w`        | A \<double\> vector of sample weights.                                                                                                                                                                                                                                                  |
| `micro`    | A \<logical\>-value of length `1` (default: NULL). If TRUE it returns the micro average across all `k` classes, if FALSE it returns the macro average.                                                                                                                                  |
| `method`   | A \<double\> value (default: `0`). Defines the underlying method of calculating the area under the curve. If `0` it is calculated using the `trapezoid`-method, if `1` it is calculated using the `step`-method.                                                                        |
| `...`      | Arguments passed into other methods.                                                                                                                                                                                                                                                    |

### Value

If `estimator` is given as

- 0: a named \<double\>-vector of length k

- 1: a \<double\> value (Micro averaged metric)

- 2: a \<double\> value (Macro averaged metric)

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

## Evaluate performance

SLmetrics::weighted.auc.roc.curve(
actual   = actual_classes, 
response = probability_matrix,
w        = sample_weights
)


```
```

{% endcode %}
```

{% endcode %}
