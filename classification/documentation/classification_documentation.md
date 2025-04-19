<div class="container">

<div role="main">

|                              |                 |
|------------------------------|----------------:|
| classification_documentation | R Documentation |

## Classification Documenatation

### Description

This roxygen block is the generic documnentation for classification
metrics for all the parameters.

### Arguments

<table role="presentation">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><code id="p">p</code>, <code id="q">q</code></td>
<td><p>A pair of &lt;double&gt; vectors of length <code
class="reqn">n</code> of empirical probabilities <code
class="reqn">p</code> and estimated probabilities <code
class="reqn">q</code>.</p></td>
</tr>
<tr class="even">
<td><code id="pk">pk</code>, <code id="qk">qk</code></td>
<td><p>A pair of &lt;double&gt; matrices of length <code
class="reqn">n</code> of emprical probabilities <code
class="reqn">p</code> and estimated probabilities <code
class="reqn">q</code>.</p></td>
</tr>
<tr class="odd">
<td><code id="ok">ok</code></td>
<td><p>A &lt;double&gt; indicator matrix with <code
class="reqn">n</code> samples and <code class="reqn">k</code>
classes.</p></td>
</tr>
<tr class="even">
<td><code id="qk">qk</code></td>
<td><p>A <code class="reqn">n \times k</code> &lt;double&gt;-matrix of
predicted probabilities. The <code class="reqn">i</code>-th row should
sum to 1 (i.e., a valid probability distribution over the <code
class="reqn">k</code> classes). The first column corresponds to the
first factor level in <code>actual</code>, the second column to the
second factor level, and so on.</p></td>
</tr>
<tr class="odd">
<td><code id="actual">actual</code>, <code
id="predicted">predicted</code></td>
<td><p>A pair of &lt;integer&gt; or &lt;factor&gt; vectors of length
<code class="reqn">n</code>, and <code class="reqn">k</code>
levels.</p></td>
</tr>
<tr class="even">
<td><code id="actual">actual</code></td>
<td><p>A vector length <code class="reqn">n</code>, and <code
class="reqn">k</code> levels. Can be of integer or factor.</p></td>
</tr>
<tr class="odd">
<td><code id="response">response</code></td>
<td><p>A <code class="reqn">n \times k</code> &lt;double&gt;-matrix of
predicted probabilities. The <code class="reqn">i</code>-th row should
sum to 1 (i.e., a valid probability distribution over the <code
class="reqn">k</code> classes). The first column corresponds to the
first factor level in <code>actual</code>, the second column to the
second factor level, and so on.</p></td>
</tr>
<tr class="even">
<td><code id="method">method</code></td>
<td><p>A &lt;double&gt; value (default: <code class="reqn">0</code>).
Defines the underlying method of calculating the area under the curve.
If <code class="reqn">0</code> it is calculated using the
<code>trapezoid</code>-method, if <code class="reqn">1</code> it is
calculated using the <code>step</code>-method.</p></td>
</tr>
<tr class="odd">
<td><code id="micro">micro</code></td>
<td><p>A &lt;logical&gt;-value of length <code class="reqn">1</code>
(default: NULL). If TRUE it returns the micro average across all <code
class="reqn">k</code> classes, if FALSE it returns the macro
average.</p></td>
</tr>
<tr class="even">
<td><code id="presorted">presorted</code></td>
<td><p>Currently not working.</p></td>
</tr>
<tr class="odd">
<td><code id="thresholds">thresholds</code></td>
<td><p>An optional &lt;double&gt; vector of length <code
class="reqn">n</code> (default: NULL).</p></td>
</tr>
<tr class="even">
<td><code id="w">w</code></td>
<td><p>A &lt;double&gt; vector of sample weights.</p></td>
</tr>
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

</div>

</div>
