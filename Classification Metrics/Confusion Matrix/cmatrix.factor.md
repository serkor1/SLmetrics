<div class="container">

<div role="main">

|                |                 |
|----------------|----------------:|
| cmatrix.factor | R Documentation |

## Confusion Matrix

### Description

A generic S3 function to compute the *confusion matrix* for a
classification model. This function dispatches to S3 methods in
`cmatrix()` and performs no input validation. If you supply NA values or
vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `cmatrix()` operates on raw pointers, pointer‑level faults (e.g.
from NA or mismatched length) occur before any `R`‑level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `cmatrix()` in a “safe” validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R

    safe_cmatrix <- function(x, y, ...) {
      stopifnot(
        !anyNA(x), !anyNA(y),
        length(x) == length(y)
      )
      cmatrix(x, y, ...)
    }

```
{% endcode %} 


Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

#### The workhorse

`cmatrix()` is the main function for classification metrics with cmatrix
S3 dispatch. These functions internally calls `cmatrix()`, so there is a
signficant gain in computing the confusion matrix first, and then pass
it onto the metrics. For example:


{% code overflow="wrap" lineNumbers="true" %}

``` R

    ## Compute confusion matrix
    confusion_matrix <- cmatrix(actual, predicted)

    ## Evaluate accuracy
    ## via S3 dispatching
    accuracy(confusion_matrix)

    ## Evaluate recall
    ## via S3 dispatching
    recall(confusion_matrix)

```
{% endcode %} 


### Usage

``` R
## S3 method for class 'factor'
cmatrix(actual, predicted, ...)
```

### Arguments

|                       |                                                                            |
|-----------------------|----------------------------------------------------------------------------|
| `actual`, `predicted` | A pair of \<integer\> or \<factor\> vectors of length `n`, and `k` levels. |
| `...`                 | Arguments passed into other methods.                                       |

### Value

A named `k` x `k` \<matrix\>

### Dimensions

There is no robust defensive measure against misspecifying the confusion
matrix. If the arguments are passed correctly, the resulting confusion
matrix is on the form:

|            |               |               |
|:-----------|:-------------:|--------------:|
|            | A (Predicted) | B (Predicted) |
| A (Actual) |     Value     |         Value |
| B (Actual) |     Value     |         Value |
|            |               |               |

### References

James, Gareth, et al. An introduction to statistical learning. Vol. 112.
No. 1. New York: springer, 2013.

Hastie, Trevor. "The elements of statistical learning: data mining,
inference, and prediction." (2009).

Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python."
the Journal of machine Learning research 12 (2011): 2825-2830.

### See Also

Other Classification: `accuracy()`, `auc.pr.curve()`, `auc.roc.curve()`,
`baccuracy()`, `brier.score()`, `ckappa()`, `cross.entropy()`, `dor()`,
`fbeta()`, `fdr()`, `fer()`, `fmi()`, `fpr()`, `hammingloss()`,
`jaccard()`, `logloss()`, `mcc()`, `nlr()`, `npv()`, `plr()`,
`pr.curve()`, `precision()`, `recall()`, `relative.entropy()`,
`roc.curve()`, `shannon.entropy()`, `specificity()`, `zerooneloss()`

Other Supervised Learning: `accuracy()`, `auc.pr.curve()`,
`auc.roc.curve()`, `baccuracy()`, `brier.score()`, `ccc()`, `ckappa()`,
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

## Compute confusion matrix
SLmetrics::cmatrix(
   actual    = actual_classes, 
   predicted = predicted_classes
)


```

```
{% endcode %} 


```
{% endcode %} 

