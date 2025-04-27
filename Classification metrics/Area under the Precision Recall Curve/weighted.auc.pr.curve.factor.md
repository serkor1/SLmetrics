<div class="container">

<div role="main">

|                              |                 |
|------------------------------|----------------:|
| weighted.auc.pr.curve.factor | R Documentation |

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


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_auc.pr.curve <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  auc.pr.curve(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

#### Visualizing area under the precision recall curve

Use `pr.curve()` to construct the data.frame and use plot to visualize
the area under the curve.

#### Efficient multi-metric evaluation

To avoid sorting the same probability matrix multiple times (once per
class or curve), you can precompute a single set of sort indices and
pass it via the `indices` argument. This reduces the overall cost from
O(K·N log N) to O(N log N + K·N).


{% code overflow="wrap" lineNumbers="true" %}

``` R
## presort response
## probabilities
indices <- preorder(response, decreasing = TRUE)

## evaluate area under the precision recall curve
auc.pr.curve(actual, response, indices = indices)
```

{% endcode %}

### Usage

``` R
## S3 method for class 'factor'
weighted.auc.pr.curve(
  actual,
  response,
  w,
  estimator = 0L,
  method = 0L,
  indices = NULL,
  ...
)
```

### Arguments

<table role="presentation">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><code id="actual">actual</code></td>
<td><p>A vector length <code class="reqn">n</code>, and <code
class="reqn">k</code> levels. Can be of integer or factor.</p></td>
</tr>
<tr class="even">
<td><code id="response">response</code></td>
<td><p>A <code class="reqn">n \times k</code> &lt;double&gt;-matrix of
predicted probabilities. The <code class="reqn">i</code>-th row should
sum to 1 (i.e., a valid probability distribution over the <code
class="reqn">k</code> classes). The first column corresponds to the
first factor level in <code>actual</code>, the second column to the
second factor level, and so on.</p></td>
</tr>
<tr class="odd">
<td><code id="w">w</code></td>
<td><p>A &lt;double&gt; vector of sample weights.</p></td>
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
<td><code id="method">method</code></td>
<td><p>A &lt;double&gt; value (default: <code class="reqn">0</code>).
Defines the underlying method of calculating the area under the curve.
If <code class="reqn">0</code> it is calculated using the
<code>trapezoid</code>-method, if <code class="reqn">1</code> it is
calculated using the <code>step</code>-method.</p></td>
</tr>
<tr class="even">
<td><code id="indices">indices</code></td>
<td><p>An optional <code class="reqn">n \times k</code> matrix of
&lt;integer&gt; values of sorted response probability indices.</p></td>
</tr>
<tr class="odd">
<td><code id="...">...</code></td>
<td><p>Arguments passed into other methods.</p></td>
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

SLmetrics::weighted.auc.pr.curve(
actual   = actual_classes, 
response = probability_matrix,
w        = sample_weights
)


```
```

{% endcode %}
```

{% endcode %}
