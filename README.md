
<!-- README.md is generated from README.Rmd. Please edit that file -->

# {SLmetrics}: Machine learning performance evaluation on steroids <img src="man/figures/logo.png" align="right" height="150" alt="" />

<!-- badges: start -->

[![CRAN
status](https://www.r-pkg.org/badges/version/SLmetrics)](https://CRAN.R-project.org/package=SLmetrics)
[![CRAN RStudio mirror
downloads](https://cranlogs.r-pkg.org/badges/last-month/SLmetrics?color=blue)](https://r-pkg.org/pkg/SLmetrics)
[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
[![R-CMD-check](https://github.com/serkor1/SLmetrics/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/serkor1/SLmetrics/actions/workflows/R-CMD-check.yaml)
[![codecov](https://codecov.io/gh/serkor1/SLmetrics/branch/development/graph/badge.svg?token=X2osJDSRlN)](https://codecov.io/gh/serkor1/SLmetrics)
<!-- badges: end -->

{SLmetrics} is a collection of *lightning fast* performance evaluation
metrics for regression and classification models written in `C++` and
[{Rcpp}](https://github.com/RcppCore/Rcpp); it’s like using a
supercharged [{yardstick}](https://github.com/tidymodels/yardstick) to
measure model performance, without the risk of soft to super-hard
deprecations. {SLmetrics} provides (almost) the same array of metrics as
in [{scikit-learn}](https://github.com/scikit-learn/scikit-learn) and
[{pytorch}](https://github.com/pytorch/pytorch) but without having to
[{reticulate}](https://github.com/rstudio/reticulate) or go through the
whole compile, run and debug cycle in `Python`.

Depending on the mood and alignment of planets {SLmetrics} stands for
Supervised Learning metrics, or Statistical Learning metrics. If
{SLmetrics} catches on, the latter will be the core philosophy and
include unsupervised learning metrics. If not, then it will remain a
{pkg} for Supervised Learning metrics, and a sandbox for me to develop
my `C++` skills.

## :information\_source: Why?

Machine Learning (ML) in itself can be a complicated task; the steps
taken from feature engineering to the deployment of the model requires
carefully measured actions, and decisions. One low-hanging of fruit of
easing this task is *performance evaluation*. In it’s core, performance
evaluation is essentially *just* a comparison of two vectors; a
programmatically and, at times, mathematically trivial step in the ML
pipeline. And therefore a {pkg} that implements performance evaluations
of ML models can, and should, be proportional to the triviality of the
application itself; ie. be efficient, fast, straightforward and simple.
There should be no need to consider *quasiquations*, *dependencies*,
*deprecations* or variations of the same functions relative to its
arguments; it should be plug-and-play, and “just” work out of the box.

Below is four arguments of why {SLmetrics} should be considered in your
ML pipeline,

Firstly, {SLmetrics} is *fast*. One, obviously, can’t build an
`R`-package on `C++` and [{Rcpp}](https://github.com/RcppCore/Rcpp)
without a proper pissing contest at the urinals; a detailed [blog
post](https://www.r-bloggers.com/) about the difference in speed has
been posted on [R-bloggers](https://www.r-bloggers.com/). For a quick
summary see below,

<details>

<summary> Showcase: speed comparison </summary>

Below is two simple cases that any {pkg} should be able to handle
gracefully; computing a confusion matrix and computing the root mean
squared error. The source code of the performance test can be found
[here](https://github.com/serkor1/SLmetrics/blob/main/data-raw/performance.R).

## Execution time: Computing a 2 x 2 Confusion Matrix

<img src="man/figures/README-performance-classification-1.png" width="100%" />

## Execution time: Computing the Root Mean Squared Error (RMSE)

<img src="man/figures/README-performance-regression-1.png" width="100%" />

In both cases the execution time is diverging in favor of {SLmetrics};
we promised speed and efficiency - and that is what you get.

> In all fairness, {yardstick} is more defensive in its implementation
> of some of its functions. However, the difference in the average
> runtime can’t be entirely attributed to this element.

</details>

Secondly, {SLmetrics} is *simple* and *flexible* to use; it is based on
`S3` and provides the most essential class-wise and aggregated metrics.

<details>

<summary> Showcase: simplicity and flexibility </summary>

Consider the classification problem below,

``` r
# 1) actual classes
actual <- factor(
  x = sample(x = 1:3, size = 100, replace = TRUE,prob = c(0.25,0.5,0.5)),
  levels = c(1:3),
  labels = letters[1:3]
)

# 2) predicted classes
predicted <- factor(
  x = sample(x = 1:3, size = 100, replace = TRUE,prob = c(0.5,0.25,0.25)),
  levels = c(1:3),
  labels = letters[1:3]
)
```

The `recall`, `precision` and `specificity` can be calculated as
follows,

``` r
# 1) recall
recall(actual, predicted)
#>         a         b         c 
#> 0.3333333 0.3939394 0.1162791

# 2) precision
precision(actual, predicted)
#>         a         b         c 
#> 0.1568627 0.4193548 0.2777778

# 3) specificity
specificity(actual, predicted)
#>         a         b         c 
#> 0.4342105 0.7313433 0.7719298
```

Each function returns the class-wise metric; there is no need to specify
the “positive” class - it just returns everything as defined by the
`factor()`-function. The overall `recall`, for example, can be computed
with a single `<[logical]>`-argument,

``` r
# 1) micro-averaged
# recall
recall(actual, predicted, micro = TRUE)
#> [1] 0.26

# 2) macro-averaged
# recall
recall(actual, predicted, micro = FALSE)
#> [1] 0.2811839
```

However, it is not efficient to loop through the entire range of the
`actual`- and `predicted`-vector to calculate three metrics; we could
just pass the functions a confusion matrix, and base the calculations
off of that as below,

``` r
# 0) confusion matrix
confusion_matrix <- cmatrix(
  actual,
  predicted
)

# 1) recall
recall(confusion_matrix)
#>         a         b         c 
#> 0.3333333 0.3939394 0.1162791

# 2) precision
precision(confusion_matrix)
#>         a         b         c 
#> 0.1568627 0.4193548 0.2777778

# 3) specificity
specificity(confusion_matrix)
#>         a         b         c 
#> 0.4342105 0.7313433 0.7719298
```

It is the same call and metric with slightly different arguments; this
is the power and simplicity of `S3`.

</details>

Thirdly, {SLmetrics} is *low level* and free of any
*{pkg}verse*-regimes; this provides the freedom to develop it further as
a part of your own {pkg}, or use it in any tidy, or untidy, pipeline you
would want to.

<details>

<summary> Showcase: Low level and (in)dependency </summary>

Currently {SLmetrics} depends on three {pkgs};
[{Rcpp}](https://github.com/RcppCore/Rcpp),
[{RcppEigen}](https://github.com/RcppCore/RcppEigen) and
[{lattice}](https://github.com/deepayan/lattice). Three incredibly
stable, flexible and efficient R packages. There is basically zero risk
of downstream breaking changes, {pkg} bloating and/or compatibility
issues.

The source code of {SLmetrics} are primarily made up of unrolled loops
and matrix algebra using
[{RcppEigen}](https://github.com/RcppCore/RcppEigen). There is, at most,
one conversion between `R` and `C++` compatible objects without
redundant type-checks, or various mapping functions; this makes
{SLmetrics} lightweight and ideal for high-speed computing.

</details>

Fourthly, {SLmetrics} has a *larger* repertoire of supervised machine
learning metrics; all of which has been battle tested with
[{scikit-learn}](https://github.com/scikit-learn/scikit-learn) and
[{pytorch}](https://github.com/pytorch/pytorch) against
[{yardstick}](https://github.com/tidymodels/yardstick),
[{mlr3measures}](https://github.com/mlr-org/mlr3measures) and
[{MLmetrics}](https://github.com/yanyachen/MLmetrics).

<details>

<summary> Showcase: repertoire and unit-testing </summary>

{SLmetrics} is build as the `R`-version of
[{scikit-learn}](https://github.com/scikit-learn/scikit-learn) but with
a larger focus on versatility, speed and the simplicity of `R`. All the
functions implemented in {SLmetrics} are tested using
[{scikit-learn}](https://github.com/scikit-learn/scikit-learn) and
[{pytorch}](https://github.com/pytorch/pytorch) as reference values.

</details>

## :information\_source: Basic usage

In its most basic form the functions can be used as-is without any
pipelines, data.frames or recipes. Below are two simple examples.

### :books: Regression

Below is an example evaluating the in-sample performance of a linear
regression on `mpg` from the `mtcars` data set,

``` r
# 1) run regression
model <- lm(
  formula = mpg ~ .,
  data    = mtcars
)

# 2) evaluate RMSE
rmse(
  actual    = mtcars$mpg,
  predicted = fitted(model)
)
#> [1] 2.146905
```

### :books: Classification

Below is an example evaluating the in-sample performance of a logistic
regression on `Species` from the `iris` data set,

``` r
# 1) recode iris
# to binary problem
iris$Species <- factor(
  x = as.numeric(
    iris$Species == "virginica"
  ),
  levels = c(1,0),
  labels = c("virginica", "others")
)

# 2) fit the logistic
# regression
model <- glm(
  formula = Species ~ Sepal.Length + Sepal.Width,
  data    = iris,
  family = binomial(
    link = "logit"
  )
)

# 3) generate predicted
# classes
predicted <- as.factor(
  ifelse(
    predict(model, type = "response") > 0.5,
    yes = "virginica",
    no  = "others"
  )
)
```

``` r
# 4) generate
# confusion matrix
summary(
  confusion_matrix <-  cmatrix(
    actual    = iris$Species,
    predicted = predicted
  )
)
#> Confusion Matrix (2 x 2) 
#> ================================================================================
#>           virginica others
#> virginica        35     15
#> others           14     86
#> ================================================================================
#> Overall Statistics (micro average)
#>  - Accuracy:          0.81
#>  - Balanced Accuracy: 0.78
#>  - Sensitivity:       0.81
#>  - Specificity:       0.81
#>  - Precision:         0.81
```

``` r
# 5) generate
# roc object
summary(
  roc <-  ROC(
    actual    = iris$Species,
    response  = predict(model, type = "response")
  )
)
#> Reciever Operator Characteristics 
#> ================================================================================
#> AUC
#>  - others: 0.883
#>  - virginica: 0.113

# 6) plot roc
# object
plot(roc)
```

<img src="man/figures/README-ROC-1.png" width="100%" />

<details>

<summary> Class-wise and aggregated metrics </summary>

**Classwise specificity**

``` r
sensitivity(
  confusion_matrix,
  micro = NULL
)
#> virginica    others 
#>      0.70      0.86
```

**Micro averaged specificity**

``` r
sensitivity(
  confusion_matrix,
  micro = TRUE
)
#> [1] 0.8066667
```

**Macro averaged specificity**

``` r
sensitivity(
  confusion_matrix,
  micro = FALSE
)
#> [1] 0.78
```

</details>

## :information\_source: Installation

### :shield: Stable version

``` r
## install stable release
devtools::install_github(
  repo = 'https://github.com/serkor1/SLmetrics@*release',
  ref  = 'main'
)
```

### :hammer\_and\_wrench: Development version

``` r
## install development version
devtools::install_github(
  repo = 'https://github.com/serkor1/SLmetrics',
  ref  = 'development'
)
```

## :information\_source: Code of Conduct

Please note that the {SLmetrics} project is released with a [Contributor
Code of
Conduct](https://contributor-covenant.org/version/2/1/CODE_OF_CONDUCT.html).
By contributing to this project, you agree to abide by its terms.
