<div class="container">

<div role="main">

|          |                 |
|----------|----------------:|
| pr.curve | R Documentation |

## Precision Recall Curve

### Description

A generic S3 function to compute the *precision recall curve* score for
a classification model. This function dispatches to S3 methods in
`pr.curve()` and performs no input validation. If you supply NA values
or vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `pr.curve()` operates on raw pointers, pointer‑level faults
(e.g. from NA or mismatched length) occur before any `R`‑level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `pr.curve()` in a “safe” validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_pr.curve <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  pr.curve(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

#### Area under the curve

Use auc.pr.curve for calculating the area under the curve directly.

### Usage

``` R
## Generic S3 method
## for Precision Recall Curve
pr.curve(...)

## Generic S3 method
## for weighted Precision Recall Curve
weighted.pr.curve(...)
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
<td><p>Arguments passed on to <code>pr.curve.factor</code>,
<code>weighted.pr.curve.factor</code></p>
<dl>
<dt><code>actual</code></dt>
<dd>
<p>A vector length <code class="reqn">n</code>, and <code
class="reqn">k</code> levels. Can be of integer or factor.</p>
</dd>
<dt><code>response</code></dt>
<dd>
<p>A <code class="reqn">n \times k</code> &lt;double&gt;-matrix of
predicted probabilities. The <code class="reqn">i</code>-th row should
sum to 1 (i.e., a valid probability distribution over the <code
class="reqn">k</code> classes). The first column corresponds to the
first factor level in <code>actual</code>, the second column to the
second factor level, and so on.</p>
</dd>
<dt><code>presorted</code></dt>
<dd>
<p>Currently not working.</p>
</dd>
<dt><code>thresholds</code></dt>
<dd>
<p>An optional &lt;double&gt; vector of length <code
class="reqn">n</code> (default: NULL).</p>
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

A data.frame on the following form,

|             |                                                                       |
|-------------|-----------------------------------------------------------------------|
| `threshold` | \<numeric\> Thresholds used to determine `recall()` and `precision()` |
| `level`     | \<character\> The level of the actual \<factor\>                      |
| `label`     | \<character\> The levels of the actual \<factor\>                     |
| `recall`    | \<numeric\> The recall                                                |
| `precision` | \<numeric\> The precision                                             |

### References

James, Gareth, et al. An introduction to statistical learning. Vol. 112.
No. 1. New York: springer, 2013.

Hastie, Trevor. "The elements of statistical learning: data mining,
inference, and prediction." (2009).

Pedregosa, Fabian, et al. "Scikit-learn: Machine learning in Python."
the Journal of machine Learning research 12 (2011): 2825-2830.

### See Also

Other Classification: `accuracy()`, `auc.pr.curve()`, `auc.roc.curve()`,
`baccuracy()`, `brier.score()`, `ckappa()`, `cmatrix()`,
`cross.entropy()`, `dor()`, `fbeta()`, `fdr()`, `fer()`, `fmi()`,
`fpr()`, `hammingloss()`, `jaccard()`, `logloss()`, `mcc()`, `nlr()`,
`npv()`, `plr()`, `precision()`, `recall()`, `relative.entropy()`,
`roc.curve()`, `shannon.entropy()`, `specificity()`, `zerooneloss()`

Other Supervised Learning: `accuracy()`, `auc.pr.curve()`,
`auc.roc.curve()`, `baccuracy()`, `brier.score()`, `ccc()`, `ckappa()`,
`cmatrix()`, `cross.entropy()`, `deviance.gamma()`,
`deviance.poisson()`, `deviance.tweedie()`, `dor()`, `fbeta()`, `fdr()`,
`fer()`, `fmi()`, `fpr()`, `hammingloss()`, `huberloss()`, `jaccard()`,
`logloss()`, `mae()`, `mape()`, `mcc()`, `mpe()`, `mse()`, `nlr()`,
`npv()`, `pinball()`, `plr()`, `precision()`, `rae()`, `recall()`,
`relative.entropy()`, `rmse()`, `rmsle()`, `roc.curve()`, `rrmse()`,
`rrse()`, `rsq()`, `shannon.entropy()`, `smape()`, `specificity()`,
`zerooneloss()`

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

## Visualize precision recall curve

plot(
SLmetrics::pr.curve(
 actual   = actual_classes, 
 response = probability_matrix
 )
)
```
```

{% endcode %}
```

{% endcode %}
