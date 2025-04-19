<div class="container">

<div role="main">

|              |                 |
|--------------|----------------:|
| auc.pr.curve | R Documentation |

## Area under the Precision Recall Curve

### Description

A generic S3 function to compute the *area under the precision recall
curve* score for a classification model. This function dispatches to S3
methods in `auc.pr.curve()` and performs no input validation. If you
supply NA values or vectors of unequal length (e.g.
`length(x) != length(y)`), the underlying `C++` code may trigger
undefined behavior and crash your `R` session.

#### Defensive measures

Because `auc.pr.curve()` operates on raw pointers, pointer‑level faults
(e.g. from NA or mismatched length) occur before any `R`‑level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `auc.pr.curve()` in a “safe” validator that
checks for NA values and matching length, for example:

<div class="sourceCode r">

    safe_auc.pr.curve <- function(x, y, ...) {
      stopifnot(
        !anyNA(x), !anyNA(y),
        length(x) == length(y)
      )
      auc.pr.curve(x, y, ...)
    }

</div>

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

#### Visualizing area under the precision recall curve

Use `pr.curve()` to construct the data.frame and use plot to visualize
the area under the curve.

### Usage

``` R
## Generic S3 method
## for Area under the Precision Recall Curve
auc.pr.curve(...)

## Generic S3 method for
## unweighted area under the
## Precision Recall Curve
auc.pr.curve(...)

## Generic S3 method
## for weighted Area under the Precision Recall Curve
weighted.auc.pr.curve(...)
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
<td><p>Arguments passed on to <code>auc.pr.curve.factor</code>,
<code>weighted.auc.pr.curve.factor</code></p>
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
<dt><code>method</code></dt>
<dd>
<p>A &lt;double&gt; value (default: <code class="reqn">0</code>).
Defines the underlying method of calculating the area under the curve.
If <code class="reqn">0</code> it is calculated using the
<code>trapezoid</code>-method, if <code class="reqn">1</code> it is
calculated using the <code>step</code>-method.</p>
</dd>
<dt><code>micro</code></dt>
<dd>
<p>A &lt;logical&gt;-value of length <code class="reqn">1</code>
(default: NULL). If TRUE it returns the micro average across all <code
class="reqn">k</code> classes, if FALSE it returns the macro
average.</p>
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

### See Also

Other Classification: `accuracy()`, `auc.roc.curve()`, `baccuracy()`,
`brier.score()`, `ckappa()`, `cmatrix()`, `cross.entropy()`, `dor()`,
`fbeta()`, `fdr()`, `fer()`, `fmi()`, `fpr()`, `hammingloss()`,
`jaccard()`, `logloss()`, `mcc()`, `nlr()`, `npv()`, `plr()`,
`pr.curve()`, `precision()`, `recall()`, `relative.entropy()`,
`roc.curve()`, `shannon.entropy()`, `specificity()`, `zerooneloss()`

Other Supervised Learning: `accuracy()`, `auc.roc.curve()`,
`baccuracy()`, `brier.score()`, `ccc()`, `ckappa()`, `cmatrix()`,
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

## Calculate area under the precision recall curve

SLmetrics::auc.pr.curve(
    actual   = actual_classes, 
    response = probability_matrix
)
```

</div>

</div>
