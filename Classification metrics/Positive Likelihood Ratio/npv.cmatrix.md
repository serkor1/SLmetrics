<div class="container">

<div role="main">

|             |                 |
|-------------|----------------:|
| npv.cmatrix | R Documentation |

## Negative Predictive Value

### Description

A generic S3 function to compute the *negative predictive value* score
for a classification model. This function dispatches to S3 methods in
`npv()` and performs no input validation. If you supply NA values or
vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `npv()` operates on raw pointers, pointer-level faults (e.g.
from NA or mismatched length) occur before any `R`-level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `npv()` in a "safe" validator that checks
for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_npv <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  npv(x, y, ...)
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

## evaluate negative predictive value
## via S3 dispatching
npv(confusion_matrix)

## additional performance metrics
## below
```

{% endcode %}

The `npv.factor()` method calls `cmatrix()` internally, so explicitly
invoking `npv.cmatrix()` yourself avoids duplicate computation, yielding
significant speed and memory effciency gains when you need multiple
evaluation metrics.

### Usage

``` R
## S3 method for class 'cmatrix'
npv(x, estimator = 0L, na.rm = TRUE, ...)
```

### Arguments

<table role="presentation">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><code id="x">x</code></td>
<td><p>A confusion matrix created <code>cmatrix()</code>.</p></td>
</tr>
<tr class="even">
<td><code id="estimator">estimator</code></td>
<td><p>An &lt;integer&gt;-value of length <code class="reqn">1</code>
(default: <code class="reqn">0</code>).</p>
<ul>
<li><p>0 - a named &lt;double&gt;-vector of length k
(class-wise)</p></li>
<li><p>1 - a &lt;double&gt; value (Micro averaged metric)</p></li>
<li><p>2 - a &lt;double&gt; value (Macro averaged metric)</p></li>
</ul></td>
</tr>
<tr class="odd">
<td><code id="na.rm">na.rm</code></td>
<td><p>A &lt;logical&gt; value of length <code class="reqn">1</code>
(default: TRUE). If TRUE, NA values are removed from the computation.
This argument is only relevant when <code>micro != NULL</code>. When
<code>na.rm = TRUE</code>, the computation corresponds to
<code>sum(c(1, 2, NA), na.rm = TRUE) / length(na.omit(c(1, 2, NA)))</code>.
When <code>na.rm = FALSE</code>, the computation corresponds to
<code>sum(c(1, 2, NA), na.rm = TRUE) / length(c(1, 2, NA))</code>.</p></td>
</tr>
<tr class="even">
<td><code id="...">...</code></td>
<td><p>Arguments passed into other methods.</p></td>
</tr>
</tbody>
</table>

### Value

If `estimator` is given as

- 0 - a named \<double\> vector of length k

- 1 - a \<double\> value (Micro averaged metric)

- 2 - a \<double\> value (Macro averaged metric)

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


## Construct confusion
## matrix
confusion_matrix <- SLmetrics::cmatrix(
actual    = actual_classes,
predicted = predicted_classes
)

## Evaluate performance
SLmetrics::npv(confusion_matrix)

```
```

{% endcode %}
```

{% endcode %}
