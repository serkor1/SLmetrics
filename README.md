

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
[![R-hub](https://github.com/serkor1/SLmetrics/actions/workflows/rhub.yaml/badge.svg)](https://github.com/serkor1/SLmetrics/actions/workflows/rhub.yaml)
[![Gitbook](https://github.com/serkor1/SLmetrics/actions/workflows/online-docs.yaml/badge.svg)](https://github.com/serkor1/SLmetrics/actions/workflows/online-docs.yaml)
[![codecov](https://codecov.io/gh/serkor1/SLmetrics/branch/development/graph/badge.svg?token=X2osJDSRlN)](https://app.codecov.io/gh/serkor1/SLmetrics)
[![CodeFactor](https://www.codefactor.io/repository/github/serkor1/slmetrics/badge)](https://www.codefactor.io/repository/github/serkor1/slmetrics)
<!-- badges: end -->

[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) is a lightweight `R`
package written in `C++` and [{Rcpp}](https://github.com/RcppCore/Rcpp)
for *memory-efficient* and *lightning-fast* machine learning performance
evaluation; it’s like using a supercharged
[{yardstick}](https://github.com/tidymodels/yardstick) but without the
risk of soft to super-hard deprecations.
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) covers both
regression and classification metrics and provides (almost) the same
array of metrics as
[{scikit-learn}](https://github.com/scikit-learn/scikit-learn) and
[{PyTorch}](https://github.com/pytorch/pytorch) all without
[{reticulate}](https://github.com/rstudio/reticulate) and the Python
compile-run-(crash)-debug cycle.

Depending on the mood and alignment of planets
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) stands for
Supervised Learning metrics, or Statistical Learning metrics. If
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) catches on, the
latter will be the core philosophy and include unsupervised learning
metrics. If not, then it will remain a {pkg} for Supervised Learning
metrics, and a sandbox for me to develop my `C++` skills.

## :rocket: Gettting Started

Below you’ll find instructions to install
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) and get started with
your first metric, the Root Mean Squared Error (RMSE).

### :package: CRAN version

``` r
## install latest CRAN build
install.packages("SLmetrics")
```

### :books: Basic Usage

Below is a minimal example demonstrating how to compute both unweighted
and weighted RMSE.

``` r
library(SLmetrics)

actual    <- c(10.2, 12.5, 14.1)
predicted <- c(9.8, 11.5, 14.2)
weights   <- c(0.2, 0.5, 0.3)

cat(
  "Root Mean Squared Error", rmse(
    actual    = actual,
    predicted = predicted,
  ),
  "Root Mean Squared Error (weighted)", weighted.rmse(
    actual    = actual,
    predicted = predicted,
    w         = weights
  ),
  sep = "\n"
)
#> Root Mean Squared Error
#> 0.6244998
#> Root Mean Squared Error (weighted)
#> 0.7314369
```

That’s all! Now you can explore the rest of this README for in-depth
usage, performance comparisons, and more details about
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1).

## :information_source: Why?

Machine learning can be a complicated task; the steps from feature
engineering to model deployment require carefully measured actions and
decisions. One low-hanging fruit to simplify this process is
*performance evaluation*.

At its core, performance evaluation is essentially just comparing two
vectors - a programmatically and, at times, mathematically trivial step
in the machine learning pipeline, but one that can become complicated
due to:

1.  Dependencies and potential deprecations
2.  Needlessly complex or repetitive arguments  
3.  Performance and memory bottlenecks at scale

[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) solves these issues
by being:

1.  **Fast:** Powered by `C++` and
    [{Rcpp}](https://github.com/RcppCore/Rcpp)  
2.  **Memory-efficient:** Everything is structured around pointers and
    references
3.  **Lightweight:** Only depends on
    [{Rcpp}](https://github.com/RcppCore/Rcpp) and
    [{lattice}](https://github.com/deepayan/lattice)
4.  **Simple:** S3-based, minimal overhead, and flexible inputs

Performance evaluation should be plug-and-play and “just work” out of
the box - there’s no need to worry about *quasiquations*,
*dependencies*, *deprecations*, or variations of the same functions
relative to their arguments when using
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1).

## :zap: Performance Comparison

One, obviously, can’t build an `R`-package on `C++` and
[{Rcpp}](https://github.com/RcppCore/Rcpp) without a proper pissing
contest at the urinals - below is a comparison in execution time and
memory efficiency of two simple cases that any {pkg} should be able to
handle gracefully; computing a 2 x 2 confusion matrix and computing the
RMSE[^1].

### :fast_forward: Speed comparison

<img src=".meta/readme/README_files/figure-commonmark/plot%20speed-performance-1.png"
style="width:100.0%" />

As shown in the chart,
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) maintains
consistently low(er) execution times across different sample sizes.

### :floppy_disk: Memory-efficiency

Below are the results for garbage collections and total memory
allocations when computing a 2×2 confusion matrix (N = 1e7) and RMSE (N
= 1e7) [^2]. Notice that
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) requires no GC calls
for these operations.

|  | Iterations | Garbage Collections \[gc()\] | gc() pr. second | Memory Allocation (MB) |
|:---|---:|---:|---:|---:|
| {SLmetrics} | 100 | 0 | 0.00 | 0 |
| {yardstick} | 100 | 190 | 4.44 | 381 |
| {MLmetrics} | 100 | 186 | 4.50 | 381 |
| {mlr3measures} | 100 | 371 | 3.93 | 916 |

2 x 2 Confusion Matrix (N = 1e7)

|  | Iterations | Garbage Collections \[gc()\] | gc() pr. second | Memory Allocation (MB) |
|:---|---:|---:|---:|---:|
| {SLmetrics} | 100 | 0 | 0.00 | 0 |
| {yardstick} | 100 | 149 | 4.30 | 420 |
| {MLmetrics} | 100 | 15 | 2.00 | 76 |
| {mlr3measures} | 100 | 12 | 1.29 | 76 |

RMSE (N = 1e7)

In both tasks, [{SLmetrics}](https://slmetrics-docs.gitbook.io/v1)
remains extremely memory-efficient, even at large sample sizes.

> \[!IMPORTANT\]
>
> From [{bench}](https://github.com/r-lib/bench) documentation: *Total
> amount of memory allocated by R while running the expression. Memory
> allocated outside the R heap, e.g. by `malloc()` or new directly is
> not tracked, take care to avoid misinterpreting the results if running
> code that may do this.*

## :information_source: Basic usage

In its simplest form,
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1)-functions work
directly with pairs of `<numeric>` vectors (for regression) or
`<factor>` vectors (for classification). Below we demonstrate this on
two well-known datasets, `mtcars` (regression) and `iris`
(classification).

### :books: Regression

We first fit a linear model to predict `mpg` in the `mtcars` dataset,
then compute the in-sample RMSE:

``` r
## Evaluate a linear model on mpg (mtcars)
model <- lm(mpg ~ ., data = mtcars)
rmse(mtcars$mpg, fitted(model))
#> [1] 2.146905
```

### :books: Classification

Now we recode the `iris` dataset into a binary problem (“virginica”
vs. “others”) and fit a logistic regression. Then we generate predicted
classes, compute the confusion matrix and summarize it.

``` r
## 1) recode iris
## to binary problem
iris$species_num <- as.numeric(
  iris$Species == "virginica"
)

## 2) fit the logistic
## regression
model <- glm(
  formula = species_num ~ Sepal.Length + Sepal.Width,
  data    = iris,
  family  = binomial(
    link = "logit"
  )
)

## 3) generate predicted
## classes
predicted <- factor(
  as.numeric(
    predict(model, type = "response") > 0.5
  ),
  levels = c(1,0),
  labels = c("Virginica", "Others")
)

## 4) generate actual
## values as factor
actual <- factor(
  x = iris$species_num,
  levels = c(1,0),
  labels = c("Virginica", "Others")
)
```

``` r
## 4) generate
## confusion matrix
summary(
  confusion_matrix <- cmatrix(
    actual    = actual,
    predicted = predicted
  )
)
#> Confusion Matrix (2 x 2) 
#> ================================================================================
#>           Virginica Others
#> Virginica        35     15
#> Others           14     86
#> ================================================================================
#> Overall Statistics (micro average)
#>  - Accuracy:          0.81
#>  - Balanced Accuracy: 0.78
#>  - Sensitivity:       0.81
#>  - Specificity:       0.81
#>  - Precision:         0.81
```

## :information_source: Enable OpenMP

> \[!IMPORTANT\]
>
> OpenMP support in [{SLmetrics}](https://slmetrics-docs.gitbook.io/v1)
> is experimental. Use it with caution, as performance gains and
> stability may vary based on your system configuration and workload.

You can control OpenMP usage within
[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) using `openmp.on()`
and `openmp.off()` . Below are examples demonstrating how to enable and
disable OpenMP:

``` r
## enable OpenMP
SLmetrics::openmp.on()
#> OpenMP enabled!

## disable OpenMP
SLmetrics::openmp.off()
#> OpenMP disabled!
```

To illustrate the impact of OpenMP on performance, consider the
following benchmarks for calculating entropy on a 1,000,000 x 200 matrix
over 100 iterations[^3].

### :books: Entropy without OpenMP

| Iterations | Runtime (sec) | Garbage Collections \[gc()\] | gc() pr. second | Memory Allocation (MB) |
|---:|---:|---:|---:|---:|
| 100 | 0.86 | 0 | 0 | 0 |

1e6 x 200 matrix without OpenMP

### :books: Entropy with OpenMP

| Iterations | Runtime (sec) | Garbage Collections \[gc()\] | gc() pr. second | Memory Allocation (MB) |
|---:|---:|---:|---:|---:|
| 100 | 0.15 | 0 | 0 | 0 |

1e6 x 200 matrix with OpenMP

## :package: Install from source

### Github release

``` r
## install github release
pak::pak(
    pkg = "serkor1/SLmetrics@*release",
    ask = FALSE
)
```

### Nightly build

#### Clone repository with submodules

``` console
git clone --recurse-submodules https://github.com/serkor1/SLmetrics.git
```

#### Installing with build tools

``` console
make build
```

#### Installing with {pak}

``` r
## install nightly build
pak::pak(
    pkg = ".",
    ask = FALSE
)
```

## :information_source: Code of Conduct

Please note that the [{SLmetrics}](https://slmetrics-docs.gitbook.io/v1)
project is released with a [Contributor Code of
Conduct](https://contributor-covenant.org/version/2/1/CODE_OF_CONDUCT.html).
By contributing to this project, you agree to abide by its terms.

[^1]: The source code is available
    [here](https://github.com/serkor1/SLmetrics/blob/d9b6cdbc1fccbdb0d45364b0fc37ebe953df30b9/data-raw/classification_performance.R)
    and
    [here](https://github.com/serkor1/SLmetrics/blob/d9b6cdbc1fccbdb0d45364b0fc37ebe953df30b9/data-raw/regression_performance.R).

[^2]: The source code is available
    [here](https://github.com/serkor1/SLmetrics/blob/d9b6cdbc1fccbdb0d45364b0fc37ebe953df30b9/data-raw/memory_performance.R).

[^3]: The source code is available
    [here](https://github.com/serkor1/SLmetrics/blob/d9b6cdbc1fccbdb0d45364b0fc37ebe953df30b9/data-raw/OpenMP_perfomance.R).
