<div class="container">

<div role="main">

|                          |                 |
|--------------------------|----------------:|
| regression_documentation | R Documentation |

## Regression Documenatation

### Description

This roxygen block is the generic documnentation for entropy metrics for
all the parameters.

### Arguments

<table role="presentation">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><code id="actual">actual</code>, <code
id="predicted">predicted</code></td>
<td><p>A pair of &lt;double&gt; vectors of length <code
class="reqn">n</code>.</p></td>
</tr>
<tr class="even">
<td><code id="w">w</code></td>
<td><p>A &lt;double&gt; vector of sample weights.</p></td>
</tr>
<tr class="odd">
<td><code id="...">...</code></td>
<td><p>Arguments passed into other methods</p></td>
</tr>
<tr class="even">
<td><code id="delta">delta</code></td>
<td><p>A &lt;double&gt;-vector of length <code class="reqn">1</code>
(default: <code class="reqn">1</code>). The threshold value for switch
between functions (see calculation).</p></td>
</tr>
<tr class="odd">
<td><code id="correction">correction</code></td>
<td><p>A &lt;logical&gt; vector of length <code class="reqn">1</code>
(default: FALSE). If TRUE the variance and covariance will be adjusted
with <code class="reqn">\frac{1-n}{n}</code></p></td>
</tr>
<tr class="even">
<td><code id="k">k</code></td>
<td><p>A &lt;double&gt;-vector of length 1 (default: 0). For adjusted
<code class="reqn">R^2</code> set <code
class="reqn">k = \kappa - 1</code>, where <code
class="reqn">\kappa</code> is the number of parameters.</p></td>
</tr>
<tr class="odd">
<td><code id="normalization">normalization</code></td>
<td><p>A &lt;double&gt;-value of length <code class="reqn">1</code>
(default: <code class="reqn">1</code>). <code class="reqn">0</code>:
mean-normalization, <code class="reqn">1</code>: range-normalization,
<code class="reqn">2</code>: IQR-normalization.</p></td>
</tr>
<tr class="even">
<td><code id="alpha">alpha</code></td>
<td><p>A &lt;double&gt;-value of length <code class="reqn">1</code>
(default: <code class="reqn">0.5</code>). The slope of the pinball loss
function.</p></td>
</tr>
<tr class="odd">
<td><code id="deviance">deviance</code></td>
<td><p>A &lt;logical&gt;-value of length 1 (default: FALSE). If TRUE the
function returns the <code class="reqn">D^2</code> loss.</p></td>
</tr>
<tr class="even">
<td><code id="power">power</code></td>
<td><p>A &lt;double&gt; value, default = 2. Tweedie power parameter.
Either power &lt;= 0 or power &gt;= 1.</p>
<p>The higher <code class="reqn">power</code>, the less weight is given
to extreme deviations between actual and predicted values.</p>
<ul>
<li><p><strong>power &lt; 0:</strong> Extreme stable distribution.
Requires: predicted &gt; 0.</p></li>
<li><p><strong>power = 0:</strong> Normal distribution, output
corresponds to <code>mse()</code>, actual and predicted can be any real
numbers.</p></li>
<li><p><strong>power = 1:</strong> Poisson distribution
(<code>deviance.poisson()</code>). Requires: actual &gt;= 0 and
predicted &gt; 0.</p></li>
<li><p><strong>1 &lt; power &lt; 2:</strong> Compound Poisson
distribution. Requires: actual &gt;= 0 and predicted &gt; 0.</p></li>
<li><p><strong>power = 2:</strong> Gamma distribution
(<code>deviance.gamma()</code>). Requires: actual &gt; 0 and predicted
&gt; 0.</p></li>
<li><p><strong>power = 3:</strong> Inverse Gaussian distribution.
Requires: actual &gt; 0 and predicted &gt; 0.</p></li>
<li><p><strong>otherwise:</strong> Positive stable distribution.
Requires: actual &gt; 0 and predicted &gt; 0.</p></li>
</ul></td>
</tr>
</tbody>
</table>

</div>

</div>
