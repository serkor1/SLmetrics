<div class="container">

<div role="main">

|       |                 |
|-------|----------------:|
| rrmse | R Documentation |

## Relative Root Mean Squared Error

### Description

A generic S3 function to compute the *relative root mean squared error*
score for a regression model. This function dispatches to S3 methods in
`rrmse()` and performs no input validation. If you supply NA values or
vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `rrmse()` operates on raw pointers, pointer‑level faults (e.g.
from NA or mismatched length) occur before any `R`‑level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `rrmse()` in a “safe” validator that checks
for NA values and matching length, for example:

<div class="sourceCode r">

    safe_rrmse <- function(x, y, ...) {
      stopifnot(
        !anyNA(x), !anyNA(y),
        length(x) == length(y)
      )
      rrmse(x, y, ...)
    }

</div>

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## Generic S3 method
## for Relative Root Mean Squared Error
rrmse(...)

## Generic S3 method
## for weighted Concordance Correlation Coefficient
weighted.rrmse(...)
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
<td><p>Arguments passed on to <code>rrmse.numeric</code>,
<code>weighted.rrmse.numeric</code></p>
<dl>
<dt><code>actual,predicted</code></dt>
<dd>
<p>A pair of &lt;double&gt; vectors of length <code
class="reqn">n</code>.</p>
</dd>
<dt><code>normalization</code></dt>
<dd>
<p>A &lt;double&gt;-value of length <code class="reqn">1</code>
(default: <code class="reqn">1</code>). <code class="reqn">0</code>:
mean-normalization, <code class="reqn">1</code>: range-normalization,
<code class="reqn">2</code>: IQR-normalization.</p>
</dd>
<dt><code>w</code></dt>
<dd>
<p>A &lt;double&gt; vector of sample weights.</p>
</dd>
</dl></td>
</tr>
</tbody>
</table>

### Value

A \<double\> value

### References

James, Gareth, et al. An introduction to statistical learning. Vol. 112.
No. 1. New York: springer, 2013.

Hastie, Trevor. "The elements of statistical learning: data mining,
inference, and prediction." (2009).

Virtanen, Pauli, et al. "SciPy 1.0: fundamental algorithms for
scientific computing in Python." Nature methods 17.3 (2020): 261-272.

### See Also

Other Regression: `ccc()`, `deviance.gamma()`, `deviance.poisson()`,
`deviance.tweedie()`, `huberloss()`, `mae()`, `mape()`, `mpe()`,
`mse()`, `pinball()`, `rae()`, `rmse()`, `rmsle()`, `rrse()`, `rsq()`,
`smape()`

Other Supervised Learning: `accuracy()`, `auc.pr.curve()`,
`auc.roc.curve()`, `baccuracy()`, `brier.score()`, `ccc()`, `ckappa()`,
`cmatrix()`, `cross.entropy()`, `deviance.gamma()`,
`deviance.poisson()`, `deviance.tweedie()`, `dor()`, `fbeta()`, `fdr()`,
`fer()`, `fmi()`, `fpr()`, `hammingloss()`, `huberloss()`, `jaccard()`,
`logloss()`, `mae()`, `mape()`, `mcc()`, `mpe()`, `mse()`, `nlr()`,
`npv()`, `pinball()`, `plr()`, `pr.curve()`, `precision()`, `rae()`,
`recall()`, `relative.entropy()`, `rmse()`, `rmsle()`, `roc.curve()`,
`rrse()`, `rsq()`, `shannon.entropy()`, `smape()`, `specificity()`,
`zerooneloss()`

### Examples

``` R
## Generate actual
## and predicted values
actual_values    <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)
predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)

## Evaluate performance
SLmetrics::rrmse(
   actual    = actual_values, 
   predicted = predicted_values
)
```

</div>

</div>
