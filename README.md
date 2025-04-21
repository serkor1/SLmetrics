# Statistical Learning Metrics in R

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
{% code title="Close Repository" overflow="wrap" lineNumbers="true" %}

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