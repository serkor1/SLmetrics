<div class="container">

<div role="main">

|         |                 |
|---------|----------------:|
| logloss | R Documentation |

## @inheritDotParams logloss.integer

### Description

@inheritDotParams logloss.integer

### Usage

``` R
## Generic S3 method
## for weighted Logarithmic Loss
weighted.logloss(...)

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
<td><p>Arguments passed on to <code>logloss.factor</code></p>
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

