<div class="container">

<div role="main">

|     |                 |
|-----|----------------:|
| nlr | R Documentation |

## Negative Likelihood Ratio

### Description

A generic S3 function to compute the *negative likelihood ratio* score
for a classification model. This function dispatches to S3 methods in
`nlr()` and performs no input validation. If you supply NA values or
vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `nlr()` operates on raw pointers, pointer‑level faults (e.g.
from NA or mismatched length) occur before any `R`‑level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `nlr()` in a “safe” validator that checks
for NA values and matching length, for example:

<div class="sourceCode r">

    safe_nlr <- function(x, y, ...) {
      stopifnot(
        !anyNA(x), !anyNA(y),
        length(x) == length(y)
      )
      nlr(x, y, ...)
    }

</div>

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

#### Efficient multi-metric evaluation

For multiple performance evaluations of a classification model, first
compute the confusion matrix once via `cmatrix()`. All other performance
metrics can then be derived from this one object via S3 dispatching:

<div class="sourceCode r">

    ## compute confusion matrix
    confusion_matrix <- cmatrix(actual, predicted)

    ## evaluate negative likelihood ratio
    ## via S3 dispatching
    nlr(confusion_matrix)

    ## additional performance metrics
    ## below

</div>

The `nlr.factor()` method calls `cmatrix()` internally, so explicitly
invoking `nlr.cmatrix()` yourself avoids duplicate computation, yielding
significant speed and memory effciency gains when you need multiple
evaluation metrics.

### Usage

``` R
## Generic S3 method
## for Negative Likelihood Ratio
nlr(...)

## Generic S3 method
## for weighted Negative Likelihood Ratio
weighted.nlr(...)
```

### Arguments

<table role="presentation">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><code id="...">...</code></td>
<td><p>Arguments passed on to <code>nlr.factor</code>,
<code>weighted.nlr.factor</code>, <code>nlr.cmatrix</code></p>
<dl>
<dt><code>actual,predicted</code></dt>
<dd>
<p>A pair of &lt;integer&gt; or &lt;factor&gt; vectors of length <code
class="reqn">n</code>, and <code class="reqn">k</code> levels.</p>
</dd>
<dt><code>w</code></dt>
<dd>
<p>A &lt;double&gt; vector of sample weights.</p>
</dd>
<dt><code>x</code></dt>
<dd>
<p>A confusion matrix created <code>cmatrix()</code>.</p>
</dd>
</dl></td>
</tr>
</tbody>
</table>

### Value

A \<double\>-value

### References

James, Gareth, et al. An introduction to statistical learning. Vol. 112.
No. 1. New York: springer, 2013.

Hastie, Trevor. "The elements of statistical learning: data mining,
inference, and prediction." (2009).

Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python."
the Journal of machine Learning research 12 (2011): 2825-2830.

### See Also

The `plr()`-function for the Positive Likehood Ratio (LR+)

Other Classification: `accuracy()`, `auc.pr.curve()`, `auc.roc.curve()`,
`baccuracy()`, `brier.score()`, `ckappa()`, `cmatrix()`,
`cross.entropy()`, `dor()`, `fbeta()`, `fdr()`, `fer()`, `fmi()`,
`fpr()`, `hammingloss()`, `jaccard()`, `logloss()`, `mcc()`, `npv()`,
`plr()`, `pr.curve()`, `precision()`, `recall()`, `relative.entropy()`,
`roc.curve()`, `shannon.entropy()`, `specificity()`, `zerooneloss()`

Other Supervised Learning: `accuracy()`, `auc.pr.curve()`,
`auc.roc.curve()`, `baccuracy()`, `brier.score()`, `ccc()`, `ckappa()`,
`cmatrix()`, `cross.entropy()`, `deviance.gamma()`,
`deviance.poisson()`, `deviance.tweedie()`, `dor()`, `fbeta()`, `fdr()`,
`fer()`, `fmi()`, `fpr()`, `hammingloss()`, `huberloss()`, `jaccard()`,
`logloss()`, `mae()`, `mape()`, `mcc()`, `mpe()`, `mse()`, `npv()`,
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

## Evaluate performance
SLmetrics::nlr(
   actual    = actual_classes, 
   predicted = predicted_classes
)
```

</div>

</div>
