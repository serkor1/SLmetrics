<div class="container">

<div role="main">

|                 |                 |
|-----------------|----------------:|
| shannon.entropy | R Documentation |

## Shannon Entropy

### Description

A generic S3 function to compute the *shannon entropy* score for a
classification model. This function dispatches to S3 methods in
`shannon.entropy()` and performs no input validation. If you supply NA
values or vectors of unequal length (e.g. `length(x) != length(y)`), the
underlying `C++` code may trigger undefined behavior and crash your `R`
session.

#### Defensive measures

Because `shannon.entropy()` operates on raw pointers, pointer‑level
faults (e.g. from NA or mismatched length) occur before any `R`‑level
error handling. Wrapping calls in `try()` or `tryCatch()` will *not*
prevent `R`-session crashes.

To guard against this, wrap `shannon.entropy()` in a “safe” validator
that checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R
safe_shannon.entropy <- function(x, y, ...) {
  stopifnot(
    !anyNA(x), !anyNA(y),
    length(x) == length(y)
  )
  shannon.entropy(x, y, ...)
}
```

{% endcode %}

Apply the same pattern to any custom metric functions to ensure input
sanity before calling the underlying `C++` code.

### Usage

``` R
## Generic S3 method
## for Shannon Entropy
shannon.entropy(...)
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
<td><p>Arguments passed on to <code>shannon.entropy.matrix</code></p>
<dl>
<dt><code>pk</code></dt>
<dd>
<p>A <code class="reqn">n \times k</code> &lt;double&gt;-matrix of
observed probabilities. The <code class="reqn">i</code>-th row should
sum to 1 (i.e., a valid probability distribution over the <code
class="reqn">k</code> classes). The first column corresponds to the
first factor level in <code>actual</code>, the second column to the
second factor level, and so on.</p>
</dd>
<dt><code>dim</code></dt>
<dd>
<p>An &lt;integer&gt; value of length 1 (Default: 0). Defines the
dimension along which to calculate the entropy (0: total, 1: row-wise,
2: column-wise).</p>
</dd>
<dt><code>base</code></dt>
<dd>
<p>A &lt;double&gt; value of length 1 (Default: -1). The logarithmic
base to use. Default value specifies natural logarithms.</p>
</dd>
</dl></td>
</tr>
</tbody>
</table>

### Value

A \<double\> value or vector:

- A single \<double\> value (length 1) if `dim == 0`.

- A \<double\> vector with length equal to the length of rows if
  `dim == 1`.

- A \<double\> vector with length equal to the length of columns if
  `dim == 2`.

### References

MacKay, David JC. Information theory, inference and learning algorithms.
Cambridge university press, 2003.

Kramer, Oliver, and Oliver Kramer. "Scikit-learn." Machine learning for
evolution strategies (2016): 45-53.

Virtanen, Pauli, et al. "SciPy 1.0: f'undamental algorithms for
scientific computing in Python." Nature methods 17.3 (2020): 261-272.

