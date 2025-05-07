<div class="container">

<div role="main">

|         |                 |
|---------|----------------:|
| logloss | R Documentation |

## Logarithmic Loss

### Description

A generic S3 function to compute the *logarithmic loss* score for a
classification model. This function dispatches to S3 methods in
`logloss()` and performs no input validation. If you supply NA values or
vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `logloss()` operates on raw pointers, pointer-level faults (e.g.
from NA or mismatched length) occur before any `R`-level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `logloss()` in a "safe" validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_logloss <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  logloss(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## Generic S3 method
## for Logarithmic Loss
logloss(...)

## Generic S3 method
## for weighted Logarithmic Loss
weighted.logloss(...)
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
<td><p>Arguments passed on to <code>logloss.integer</code>,
<code>logloss.factor</code>, <code>weighted.logloss.integer</code>,
<code>weighted.logloss.factor</code></p>
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
<dt><code>normalize</code></dt>
<dd>
<p>A &lt;logical&gt;-value (default: TRUE). If TRUE, the mean
cross-entropy across all observations is returned; otherwise, the sum of
cross-entropies is returned.</p>
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

A \<double\>

### References

MacKay, David JC. Information theory, inference and learning algorithms.
Cambridge university press, 2003.

Kramer, Oliver, and Oliver Kramer. "Scikit-learn." Machine learning for
evolution strategies (2016): 45-53.

Virtanen, Pauli, et al. "SciPy 1.0: f'undamental algorithms for
scientific computing in Python." Nature methods 17.3 (2020): 261-272.

### Examples

``` R
## Classes and
## seed
set.seed(1903)
classes <- c("Kebab", "Falafel")

## Generate actual
## and predicted response
## probabilities
actual_classes <- factor(
x = sample(x = classes, size = 1e3, replace = TRUE),
levels = c("Kebab", "Falafel")
)

response <- runif(n = 1e3)

## Logloss
SLmetrics::logloss(
   actual    = actual_classes, 
   response  = cbind(
 response,
 1 - response
   )
)

## Generate observed
## frequencies 
actual_frequency <- sample(10L:100L, size = 1e3, replace = TRUE)

## Poisson Logloss
SLmetrics::logloss(
   actual    = actual_frequency, 
   response  = response
)




```
```

{% endcode %}
```

{% endcode %}
