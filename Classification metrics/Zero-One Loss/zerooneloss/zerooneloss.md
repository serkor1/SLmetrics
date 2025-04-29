<div class="container">

<div role="main">

|             |                 |
|-------------|----------------:|
| zerooneloss | R Documentation |

## Zero-One Loss

### Description

A generic S3 function to compute the *zero-one loss* score for a
classification model. This function dispatches to S3 methods in
`zerooneloss()` and performs no input validation. If you supply NA
values or vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `zerooneloss()` operates on raw pointers, pointer-level faults
(e.g. from NA or mismatched length) occur before any `R`-level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `zerooneloss()` in a "safe" validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_zerooneloss <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  zerooneloss(x, y, ...)
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

## evaluate zero-one loss
## via S3 dispatching
zerooneloss(confusion_matrix)

## additional performance metrics
## below
```

{% endcode %}

The `zerooneloss.factor()` method calls `cmatrix()` internally, so
explicitly invoking `zerooneloss.cmatrix()` yourself avoids duplicate
computation, yielding significant speed and memory effciency gains when
you need multiple evaluation metrics.

### Usage

``` R
## Generic S3 method
## for Zero-One Loss
zerooneloss(...)

## Generic S3 method
## for weighted Zero-One Loss
weighted.zerooneloss(...)
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
<td><p>Arguments passed on to <code>zerooneloss.factor</code>,
<code>weighted.zerooneloss.factor</code>,
<code>zerooneloss.cmatrix</code></p>
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
SLmetrics::zerooneloss(
   actual    = actual_classes, 
   predicted = predicted_classes
)
```
```

{% endcode %}
```

{% endcode %}
