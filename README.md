# Statistical Learning Metrics in R

[{SLmetrics}](https://github.com/serkor1/SLmetrics) is an implementation of 40+ scoring metrics for supervised and unsupervised machine learning and statistical learning models.

## Benchmarks

{% code title="Benchmark" overflow="wrap" lineNumbers="false" %}

``` r
## seed
set.seed(1903)

## generate
## values
actual    <- rnorm(n = 1e8)
predicted <- actual + rnorm(n = 1e8)

## benchmark
## RMSE
bench::mark(
  `{SLmetrics}` = SLmetrics::rmse(actual, predicted),
  `{yardstick}` = yardstick::rmse_vec(actual, predicted),
  `{MLmetrics}` = MLmetrics::RMSE(predicted, actual),
  `{base}`      = sqrt(as.numeric(crossprod(actual - predicted))/length(actual))
)
#> Warning: Some expressions had a GC in every iteration; so filtering is
#> disabled.
#> # A tibble: 4 × 6
#>   expression       min   median `itr/sec` mem_alloc `gc/sec`
#>   <bch:expr>  <bch:tm> <bch:tm>     <dbl> <bch:byt>    <dbl>
#> 1 {SLmetrics}  44.36ms  45.93ms    21.8      5.95MB    0    
#> 2 {yardstick}    3.98s    3.98s     0.251     4.1GB    0.754
#> 3 {MLmetrics} 669.96ms 669.96ms     1.49      763MB    0    
#> 4 {base}      483.24ms 562.09ms     1.78   762.94MB    0.890
```
{% endcode %}

## Install CRAN version

{% code title="CRAN version" overflow="wrap" lineNumbers="true" %}

```r
pak::pak(
    pkg = "SLmetrics",
    ask = FALSE
    )
```

{% endcode %}

## Install development version

{% stepper %}
{% step %}
### Clone repository
{% code title="Clone Repository" overflow="wrap" lineNumbers="true" %}

``` console
git clone --recurse-submodules https://github.com/serkor1/SLmetrics.git
```

{% endcode %}
{% endstep %}
{% step %}
### Install with {pak}

{% code title="Install with {pak}" overflow="wrap" lineNumbers="true" %}
```r
pak::pak(
    pkg = ".",
    ask = FALSE
)
```
{% endcode %}

{% endstep %}
{% endstepper %}