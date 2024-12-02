
# Version 0.1-0

> Version 0.1-0 is considered pre-release of {SLmetrics}. We do not
> expect any breaking changes, unless a major bug/issue is reported and
> its nature forces breaking changes.

## General

  - {SLmetrics} is a collection of Machine Learning performance
    evaluation functions for supervised learning. Visit the online
    documentation on [GitHub
    Pages](https://serkor1.github.io/SLmetrics/).

## Examples

### Supervised classification metrics

``` r
# 1) actual classes
print(
    actual <- factor(
        sample(letters[1:3], size = 10, replace = TRUE)
    )
)
```

    #>  [1] b a b b a c b c c a
    #> Levels: a b c

``` r
# 2) predicted classes
print(
    predicted <- factor(
        sample(letters[1:3], size = 10, replace = TRUE)
    )
)
```

    #>  [1] c c a b a b c c a c
    #> Levels: a b c

``` r
# 1) calculate confusion
# matrix and summarise
# it
summary(
    confusion_matrix <- SLmetrics::cmatrix(
        actual    = actual,
        predicted = predicted
    )
)
```

    #> Confusion Matrix (3 x 3) 
    #> ================================================================================
    #>   a b c
    #> a 1 0 2
    #> b 1 1 2
    #> c 1 1 1
    #> ================================================================================
    #> Overall Statistics (micro average)
    #>  - Accuracy:          0.30
    #>  - Balanced Accuracy: 0.31
    #>  - Sensitivity:       0.30
    #>  - Specificity:       0.65
    #>  - Precision:         0.30

``` r
# 2) calculate false positive
# rate using micro average
SLmetrics::fpr(
    confusion_matrix
)
```

    #>         a         b         c 
    #> 0.2857143 0.1666667 0.5714286

### Supervised regression metrics

``` r
# 1) actual values
actual <- rnorm(n = 100)

# 2) predicted values
predicted <- actual + rnorm(n = 100)
```

``` r
# 1) calculate
# huber loss
SLmetrics::huberloss(
    actual    = actual,
    predicted = predicted
)
```

    #> [1] 0.394088
