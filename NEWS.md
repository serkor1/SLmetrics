

> Version 0.3-4 is considered pre-release of {SLmetrics}. We do not
> expect any breaking changes, unless a major bug/issue is reported and
> its nature forces breaking changes.

# :bookmark: Version 0.3-4

This update has been focused on two three things:

1.  Optimization of the back-end by using Armadillo instead of Eigen.
2.  Streamlining and extending the documentation
3.  Making functions more flexible

As an example on the increased flexibility is the introduction of the
`estimator`-argument in classification metrics - the new approach
enables new additions of aggregation methods as the field evolves. The
“old” approach were limited to three values `NULL`, `TRUE` and `FALSE`.
Furthermore the function signatures of the generics have been made more
flexible - this will enable possible wrapping packages to freely
implement argument names off the generic.

## :sparkles: Improvements

- **Armadillo backend:** All functions have been ported to the C++
  Armadillo library, and are heavily templated and Object Oriented. The
  functions are 5-20x faster than before.
- **Streamlined documentation:** All documentation have been reworked,
  and are now using generic {roxygen2} templates. The new structure of
  the documentation is focused on shared documentation and therefore
  equal metrics like `recall` and `sensitivity` are aliased, and
  referenced differently - as a result there should be less noise in the
  documentation. The *creating factor* has been removed, and all
  examples are simplified.
- **Efficient multi-metric evaluation:** The Precision-Recall and
  Receiver Operator Characteristics functions now accepts an `indices`
  argument. The indices takes an `integer`-matrix of corresponding to
  the sorted probabilities column-wise. See below:

``` r
## Classes and
## seed
set.seed(1903)
classes <- c("Kebab", "Falafel")

## Generate actual classes
## and response probabilities
actual_classes <- factor(
    x = sample(
      x = classes, 
      size = 1e2, 
      replace = TRUE, 
      prob = c(0.7, 0.3)
    )
)

response_probabilities <- ifelse(
    actual_classes == "Kebab", 
    rbeta(sum(actual_classes == "Kebab"), 2, 5), 
    rbeta(sum(actual_classes == "Falafel"), 5, 2)
)

## Construct response
## matrix
probability_matrix <- cbind(
    response_probabilities,
    1 - response_probabilities
)

## Calculate Precision-Recall
stopifnot(
    all.equal(
        target  = SLmetrics::pr.curve(actual_classes, probability_matrix),
        current = SLmetrics::pr.curve(actual_classes, probability_matrix, indices = SLmetrics::preorder(probability_matrix, TRUE))
    )
)
```

Depending on the system and data, there is a 3x gain in speed. This
approach is highly efficient for cases where multiple AUC or curves are
to be computed as it avoids sorting the same probability matrix more
than once.

## :bug:-fixes

- **Relative Root Mean Squared Error:** Normalizing the `RMSE` using the
  `range`, the `range` is always calculated by the distance between
  `max(actual) - min(actual)` instead of the weighted distance.

### :rocket: New features

- **Hamming Loss:** The fraction of the wrong labels to the total number
  of labels, i.e. , where is the target, is the prediction, and is the
  “Exclusive, or” operator that returns zero when the target and
  prediction are identical and one otherwise. The interface to
  `hammingloss()` is given below:

``` r
set.seed(1903)

## classes
classes <- c("Kebab", "Falafel")

## actual and
## predicted classes
actual    <- factor(sample(classes, 10, TRUE))
predicted <- factor(sample(classes, 10, TRUE))
w         <- runif(n = 10)

## calculate hamming
## loss (weighted and unweighted)
SLmetrics::hammingloss(
    actual,
    predicted
)
#> [1] 1

SLmetrics::weighted.hammingloss(
    actual,
    predicted,
    w = w
)
#> [1] 1
```

- **Tweedie Deviance:** The interface to `tweedie.deviance()` is given
  below:

``` r
## Generate actual
## and predicted values
actual_values <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)

predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)

## Evaluate performance
SLmetrics::deviance.tweedie(
   actual_values, 
   predicted_values
)
#> [1] 0.9976545
```

- **Gamma Deviance:** The interface to `gamma.deviance()` is given
  below:

``` r
## Generate actual
## and predicted values
actual_values <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)

predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)

## Evaluate performance
SLmetrics::deviance.gamma(
   actual_values, 
   predicted_values
)
#> [1] 0.9976545
```

- **Poisson Deviance:** The interface to `poisson.deviance()` is given
  below:

``` r
## Generate actual
## and predicted values
actual_values <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)

predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)

## Evaluate performance
SLmetrics::deviance.poisson(
   actual_values, 
   predicted_values
)
#> [1] 0.3980706
```

- **Mean Arctangent Absolute Error:** The metric can be calculated as
  follows:

``` r
## Generate actual
## and predicted values
actual_values <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)

predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)

## Evaluate performance
SLmetrics::maape(
   actual_values, 
   predicted_values
)
#> [1] 0.2499164
```

- **Geometric Mean Squared Error:** The function have been implemented
  with logs and antilogs and is robust to zero-valued vectors. The
  metric can be calculated as follows:

``` r
## Generate actual
## and predicted values
actual_values <- c(1.3, 0.4, 1.2, 1.4, 1.9, 1.0, 1.2)

predicted_values <- c(0.7, 0.5, 1.1, 1.2, 1.8, 1.1, 0.2)

## Evaluate performance
SLmetrics::gmse(
   actual_values, 
   predicted_values
)
#> [1] 0.03926918
```

## :bug: Bug-fixes

## :boom: Breaking changes

- **Area under the curve:** The new interface is given below:

``` r
## Generate x and y
## pair
x <- seq(0, pi, length.out = 200)
y <- sin(x)

## 1.1) calculate area
SLmetrics::auc.xy(y = y,  x = x)
#> [1] 1.999958
```

- **Receiver Operating Characteristics:** The new interface is given
  below:

``` r
## define classes
## and response probabilities
actual   <- factor(c("Class A", "Class B", "Class A"))
response <- matrix(cbind(
    0.2, 0.8,
    0.8, 0.2,
    0.7, 0.3
),nrow = 3, ncol = 2)

## receiver operating curve
SLmetrics::roc.curve(
    actual,
    response
)
#>    threshold level   label fpr tpr
#> 1        Inf     1 Class A 0.0 0.0
#> 2        0.8     1 Class A 1.0 0.0
#> 3        0.8     1 Class A 1.0 0.5
#> 4        0.2     1 Class A 1.0 1.0
#> 5       -Inf     1 Class A 1.0 1.0
#> 6        Inf     2 Class B 0.0 0.0
#> 7        0.7     2 Class B 0.0 1.0
#> 8        0.3     2 Class B 0.5 1.0
#> 9        0.2     2 Class B 1.0 1.0
#> 10      -Inf     2 Class B 1.0 1.0

## area under the receiver operating
## curve
SLmetrics::auc.roc.curve(
    actual,
    response,
    estimator = 0 # 0: class-wise, 1: micro average, 2: macro average 
)
#> Class A Class B 
#>       0       1
```

- **Precision-Recall Curve:** The new interface is given below:

``` r
## define classes
## and response probabilities
actual   <- factor(c("Class A", "Class B", "Class A"))
response <- matrix(cbind(
    0.2, 0.8,
    0.8, 0.2,
    0.7, 0.3
),nrow = 3, ncol = 2)

## precision-recall curve
SLmetrics::pr.curve(
    actual,
    response
)
#>    threshold level   label recall precision
#> 1        Inf     1 Class A    0.0     1.000
#> 2        0.8     1 Class A    0.0     0.000
#> 3        0.8     1 Class A    0.5     0.500
#> 4        0.2     1 Class A    1.0     0.667
#> 5       -Inf     1 Class A    1.0     0.667
#> 6        Inf     2 Class B    0.0     1.000
#> 7        0.7     2 Class B    1.0     1.000
#> 8        0.3     2 Class B    1.0     0.500
#> 9        0.2     2 Class B    1.0     0.333
#> 10      -Inf     2 Class B    1.0     0.333

## area under the precision-recall
## curve
SLmetrics::auc.pr.curve(
    actual,
    response,
    estimator = 0 # 0: class-wise, 1: micro average, 2: macro average 
)
#>   Class A   Class B 
#> 0.4166667 1.0000000
```

- **Entropy:** `entropy()` has been renamed to `shannon.entropy()`. The
  new interface to `shannon.entropy()` is given below:

``` r
## Observed probabilities
pk <- matrix(
  cbind(1/2, 1/2),
  ncol = 2
)

## Shannon Entropy
SLmetrics::shannon.entropy(pk)
#> [1] 0.6931472
```

The entropy functions have had the `base`-argument removed, and a new
argument has been introduced: `normalize`. The `normalize`-parameter
averages the calculated entropy across the desired dimensions.

- **Aggregation in classification metrics:** The aggregation flag in the
  classification functions `micro` have been replaced with the
  `integer`-argument `estimator` which falls back to class-wise
  evaluation if misspecified. The new interface is given below and is
  applicable to all functions that has this argument:

``` r
set.seed(1903)

## classes
classes <- c("Kebab", "Falafel")

## actual and
## predicted classes
actual    <- factor(sample(classes, 10, TRUE))
predicted <- factor(sample(classes, 10, TRUE))

## recall: class-wise
SLmetrics::recall(
    actual,
    predicted,
    estimator = 0
)
#> Falafel   Kebab 
#>       0       0

## recall: micro-averaged
SLmetrics::recall(
    actual,
    predicted,
    estimator = 1
)
#> [1] 0

## recall: macro-averaged
SLmetrics::recall(
    actual,
    predicted,
    estimator = 1
)
#> [1] 0
```

- **Poisson Logloss:** The `logloss()` for count data
  `logloss.integer()` were taking a `matrix` of probabilities. This has
  been changed to a `vector` of probabilities.

# :bookmark: Version 0.3-3

## :sparkles: Improvements

- **Initial CRAN release:** The R-package has (finally) been submitted
  to CRAN and was released on 2025-03-18 with the classic “Thanks, on
  its way to CRAN” message.

- **S3 signatures:** All S3-methods now have a generic signature, making
  it easier to navigate the functions argument-wise.

- **Exported Data:** Three new datasets have been introduced to the
  package; the Wine Quality-, Obesity- and Banknote Authentication
  datasets. Each dataset is comes in named `list` where features and
  targets are stored separately. Below is an example from the Obesity
  dataset:

``` r
## 1) summarise the
## list
summary(SLmetrics::obesity)
#>          Length Class      Mode
#> features 15     data.frame list
#> target    2     -none-     list

## 2) head the featues
head(SLmetrics::obesity$features)
#>        caec       calc                mtrans family_history_with_overweight
#> 1 sometimes         no public_transportation                              1
#> 2 sometimes  sometimes public_transportation                              1
#> 3 sometimes frequently public_transportation                              1
#> 4 sometimes frequently               walking                              0
#> 5 sometimes  sometimes public_transportation                              0
#> 6 sometimes  sometimes            automobile                              0
#>   favc smoke scc male age height fcvc ncp ch2o faf tue
#> 1    0     0   0    0  21   1.62    2   3    2   0   1
#> 2    0     1   1    0  21   1.52    3   3    3   3   0
#> 3    0     0   0    1  23   1.80    2   3    2   2   1
#> 4    0     0   0    1  27   1.80    3   3    2   2   0
#> 5    0     0   0    1  22   1.78    2   1    2   0   0
#> 6    1     0   0    1  29   1.62    2   3    2   0   0

## 3) head target
## variables
head(SLmetrics::obesity$target$class)
#> [1] Normal_Weight       Normal_Weight       Normal_Weight      
#> [4] Overweight_Level_I  Overweight_Level_II Normal_Weight      
#> 7 Levels: Insufficient_Weight Normal_Weight Obesity_Type_I ... Overweight_Level_II
head(SLmetrics::obesity$target$regression)
#> [1] 64.0 56.0 77.0 87.0 89.8 53.0
```

### :rocket: New features

#### New metrics

- **Poisson LogLoss:** The logloss for count data has been implemented.
  This metric shares the method of logloss and can be used as follows:

``` r
## 1) define observed integers
## and response probabilities
actual   <- as.integer(factor(c("Class A", "Class B", "Class A")))
weights  <- c(0.3,0.9,1) 
response <- matrix(cbind(
    0.2, 0.8,
    0.8, 0.2,
    0.7, 0.3
),nrow = 3, ncol = 2)

## 2) weighted
## and unweighted poisson
## distributed log-loss
cat(
    "Unweighted Poisson Log Loss:",
    SLmetrics::logloss(
        actual,
        response
    ),
    "Weighted Poisson Log Loss:",
    SLmetrics::weighted.logloss(
        actual   = actual,
        response = response,
        w        = weights
    ),
    sep = "\n"
)
#> Unweighted Poisson Log Loss:
#> 1.590672
#> Weighted Poisson Log Loss:
#> 1.505212
```

- **Area under the Curve:** A new set of functions have been introduced
  which calculates the weighted and unweighted area under the
  Precision-Recall and Receiver Operator Characteristics curve. See
  below:

``` r
## 1) define observed integers
## and response probabilities
actual   <- factor(c("Class A", "Class B", "Class A"))
weights  <- c(0.3,0.9,1) 
response <- matrix(cbind(
    0.2, 0.8,
    0.8, 0.2,
    0.7, 0.3
),nrow = 3, ncol = 2)

## 2) area under
## the precision-recall curve
SLmetrics::pr.auc(
    actual   = actual,
    response = response
)
#>   Class A   Class B 
#> 0.4166667 1.0000000
```

#### Metric tools

A new family of `Tools`-functions are introduced with this update. This
addition introduces unexported functions for constructing fast and
memory efficient proprietary metrics. These functions are rewritten
built-in functions from {stats} and family.

- **Covariance Matrix:** A re-written `stats::cov.wt()`, using `Rcpp`.
  Example usage:

``` r
## 1) actual and
## predicted values
actual    <- c(1.2,  0.3, 0.56, 0.11, 1.01)
predicted <- c(0.9, 0.22, 0.76, 0.21, 1.1) 

## 2) covariance
## matrix 
SLmetrics:::cov.wt(
    cbind(actual, predicted)
)
#> $cov
#>             actual predicted
#> actual    0.213330  0.169215
#> predicted 0.169215  0.163720
#> 
#> $center
#>    actual predicted 
#>     0.636     0.638 
#> 
#> $n.obs
#> [1] 5
```

- **Area under the curve (AUC):** The function calculates the area under
  the plot for bivariate curves for ordered and unordered `x` and `y`
  pairs. The function assumes that values are ordered and calculates the
  AUC directly - to control this behaviour use the `ordered`-argument in
  the function. Below is an example:

``` r
## 0) seed
set.seed(1903)

## 1) Ordered x and y pair
x <- seq(0, pi, length.out = 200)
y <- sin(x)

## 1.1) calculate area
ordered_auc <- SLmetrics::auc(y = y,  x = x)

## 2) Unordered x and y pair
x <- sample(seq(0, pi, length.out = 200))
y <- sin(x)

## 2.1) calculate area
unordered_auc <- SLmetrics::auc(y = y,  x = x)

## 2.2) calculate area with explicit
## ordering
unordered_auc_flag <- SLmetrics::auc(
  y = y,
  x = x,
  ordered = FALSE
)

## 3) display result
cat(
  "AUC (ordered x and y pair)", ordered_auc,
  "AUC (unordered x and y pair)", unordered_auc,
  "AUC (unordered x and y pair, with unordered flag)", unordered_auc_flag,
  sep = "\n"
)
#> AUC (ordered x and y pair)
#> 1.999958
#> AUC (unordered x and y pair)
#> -1.720771
#> AUC (unordered x and y pair, with unordered flag)
#> -1.720771
```

- **Sorting algorithms:** A set of sorting and ordering algorithms
  applicable to matrices have been implemented. The use-case is
  currently limited to `auc.foo`, `ROC` and `prROC` functions. The
  algorithms can be used as follows:

``` r
## 1) generate a 4x4 matrix
## with random values to be sorted
set.seed(1903)
X <- matrix(
  data = cbind(sample(16:1)),
  nrow = 4
)

## 2) sort matrix
## in decreasing order
SLmetrics::presort(X)
#>      [,1] [,2] [,3] [,4]
#> [1,]    3    2    6    1
#> [2,]    4    5   10    7
#> [3,]    9    8   15   11
#> [4,]   13   14   16   12

## 3) get indices 
## for sorted matrix
SLmetrics::preorder(X)
#>      [,1] [,2] [,3] [,4]
#> [1,]    1    1    2    4
#> [2,]    2    3    3    2
#> [3,]    3    2    1    1
#> [4,]    4    4    4    3
```

## :boom: Breaking changes

- **Logloss:** The argument `pk` has been replaced by `response`.

# :bookmark: Version 0.3-2

## :sparkles: Improvements

- **Regression metrics (See PR
  https://github.com/serkor1/SLmetrics/pull/64):** All regression
  metrics have had their back-end optimized and are now 2-10 times
  faster than prior versions.
- **LAPACK/BLAS Support
  (https://github.com/serkor1/SLmetrics/pull/65):** Added LAPACK/BLAS
  support for efficient matrix-operations.
- **OpenMP:** Enabling/disabling OpenMP is now handled on the `R`-side
  and obeys `suppressMessages()`. See below:

``` r
## suppress OpenMP messages
suppressMessages(
  SLmetrics::openmp.off()
)
```

### :rocket: New features

- **Available threads:** The available number of threads can be
  retrieved using the `openmp.threads()`. See below:

``` r
## number of available
## threads
SLmetrics::openmp.threads()
#> [1] 24
```

## :bug: Bug-fixes

- **Diagnostic Odds Ratio:** The `dor()` is now returning a single
  `<[numeric]>`-value instead of `k` number of identical
  `<[numeric]>`-values.

## :boom: Breaking Changes

- **OpenMP Interface:** The interface to enabling/disabling OpenMP
  support has been reworked and has a more natural flow. The new
  interface is described below:

``` r
## enable OpenMP
SLmetrics::openmp.on()
#> OpenMP enabled!
```

``` r
## disable OpenMP
SLmetrics::openmp.off()
#> OpenMP disabled!
```

To set the number of threads use the `openmp.threads()` as follows:

``` r
## set number of threads
SLmetrics::openmp.threads(3)
#> Using 3 threads.
```

# :bookmark: Version 0.3-1

## :sparkles: Improvements

- **OpenMP Support (PR https://github.com/serkor1/SLmetrics/pull/40):**
  {SLmetrics} now supports parallelization through OpenMP. The OpenMP
  can be utilized as follows:

``` r
set.seed(1903)

## 1) probability distribution
## function
rand.sum <- function(n){
    x <- sort(runif(n-1))
    c(x,1) - c(0,x)
  }

## 2) generate probability
## matrix
pk <- t(replicate(
    n = 100,
    expr = rand.sum(1e3)
    )
)

## 3) calulate entropy
## with and without OpenMP
SLmetrics::setUseOpenMP(TRUE)
#> OpenMP usage set to: enabled
system.time(SLmetrics::entropy(pk))
#>    user  system elapsed 
#>   0.010   0.003   0.001

SLmetrics::setUseOpenMP(FALSE)
#> OpenMP usage set to: disabled
system.time(SLmetrics::entropy(pk))
#>    user  system elapsed 
#>   0.001   0.000   0.001
```

- **Entropy with soft labels
  (https://github.com/serkor1/SLmetrics/issues/37):** `entropy()`,
  `cross.entropy()` and `relative.entropy()` have been introduced. These
  functions are heavily inspired by {scipy}. The functions can be used
  as follows:

``` r
## 1) Define actual
## and observed probabilities

## 1.1) actual probabilies
pk <- matrix(
  cbind(1/2, 1/2),
  ncol = 2
)

## 1.2) observed (estimated) probabilites
qk <- matrix(
  cbind(9/10, 1/10), 
  ncol = 2
)

## 2) calculate entropy
cat(
  "Entropy", SLmetrics::entropy(pk),
  "Relative Entropy", SLmetrics::relative.entropy(pk, qk),
  "Cross Entropy", SLmetrics::cross.entropy(pk, qk),
  sep = "\n"
)
#> Entropy
#> 0.6931472
#> Relative Entropy
#> 0.5108256
#> Cross Entropy
#> 1.203973
```

## :bug: Bug-fixes

- **Plot-method in ROC and prROC
  (https://github.com/serkor1/SLmetrics/issues/36):** Fixed a bug in
  `plot.ROC()` and `plot.prROC()` where if `panels = FALSE` additional
  lines would be added to the plot.

## :boom: Breaking changes

- **logloss:** The argument `response` have ben renamed to `qk` as in
  the `entropy()`-family to maintain some degree of consistency.
- **entropy.factor():** The function have been deleted and is no more.
  This was mainly due to avoid the documentation from being too large.
  The `logloss()`-function replaces it.

# :bookmark: Version 0.3-0

## :sparkles: Improvements

### New features

- **Relative Root Mean Squared Error:** The function normalizes the Root
  Mean Squared Error by a factor. There is no official way of
  normalizing it - and in {SLmetrics} the RMSE can be normalized using
  three options; mean-, range- and IQR-normalization. It can be used as
  follows,

``` r
## 1) define actual and
## predicted values
actual <- rnorm(50)
predicted <- actual + rnorm(50)

## 2) calculate rrse
## with normalization
## 0: mean
## 1: range
## 2: iqr
cat(
  "Mean Relative Root Mean Squared Error", SLmetrics::rrmse(
    actual        = actual,
    predicted     = predicted,
    normalization = 0
  ),
  "Range Relative Root Mean Squared Error", SLmetrics::rrmse(
    actual        = actual,
    predicted     = predicted,
    normalization = 1
  ),
  "IQR Relative Root Mean Squared Error", SLmetrics::rrmse(
    actual        = actual,
    predicted     = predicted,
    normalization = 2
  ),
  sep = "\n"
)
#> Mean Relative Root Mean Squared Error
#> -4.686365
#> Range Relative Root Mean Squared Error
#> 0.1943122
#> IQR Relative Root Mean Squared Error
#> 0.8692987
```

- **Log Loss:** Weighted and unweighted Log Loss, with and without
  normalization. The function can be used as follows,

``` r
## 1) define actual
## values and estimated
## probabilities
actual   <- factor(c("Class A", "Class B", "Class A"))
weights  <- c(0.3,0.9,1) 
response <- matrix(cbind(
    0.2, 0.8,
    0.8, 0.2,
    0.7, 0.3
),nrow = 3, ncol = 2)

## 2) weighted and unweighted
## log-loss
cat(
    "Unweighted Log Loss:",
    SLmetrics::logloss(
        actual,
        response
    ),
    "Weighted log Loss:",
    SLmetrics::weighted.logloss(
        actual,
        response,       
        weights
    ),
    sep = "\n"
)
#> Unweighted Log Loss:
#> 0.7297521
#> Weighted log Loss:
#> 0.4668102
```

- **Weighted Receiver Operator Characteristics:** `weighted.ROC()`, the
  function calculates the weighted True Positive and False Positive
  Rates for each threshold.

- **Weighted Precision-Recall Curve:** `weighted.prROC()`, the function
  calculates the weighted Recall and Precision for each threshold.

## :bug: Bug-fixes

- **Return named vectors:** The classification metrics when
  `micro == NULL` were not returning named vectors. This has been fixed.

## :boom: Breaking Changes

- **Weighted Confusion Matrix:** The `w`-argument in `cmatrix()` has
  been removed in favor of the more verbose weighted confusion matrix
  call `weighted.cmatrix()`-function. See below,

Prior to version `0.3-0` the weighted confusion matrix were a part of
the `cmatrix()`-function and were called as follows,

``` r
SLmetrics::cmatrix(
    actual    = actual,
    predicted = predicted,
    w         = weights
)
```

This solution, although simple, were inconsistent with the remaining
implementation of weighted metrics in {SLmetrics}. To regain consistency
and simplicity the weighted confusion matrix are now retrieved as
follows,

``` r
## 1) define actual
## and predicted values
## with sample weights
actual    <- factor(sample(letters[1:3], 50, replace = TRUE))
predicted <- factor(sample(letters[1:3], 50, replace = TRUE))
weights   <- runif(length(actual))

## 2) unweighted confusion
## matrix
SLmetrics::cmatrix(
    actual    = actual,
    predicted = predicted
)
#>   a b c
#> a 4 5 3
#> b 6 6 7
#> c 5 8 6

## 3) weighted confusion
## matrix
SLmetrics::weighted.cmatrix(
    actual    = actual,
    predicted = predicted,
    w         = weights
)
#>          a        b        c
#> a 2.551064 2.859906 2.205269
#> b 2.577943 1.947142 3.013536
#> c 1.935559 3.522135 4.064463
```

# :bookmark: Version 0.2-0

## :hammer_and_wrench: General

- **documentation:** The documentation has gotten some extra love, and
  now all functions have their formulas embedded, the details section
  have been freed from a general description of \[factor\] creation.
  This will make room for future expansions on the various functions
  where more details are required.

- **Unit-testing:** All functions are now being tested for edge-cases in
  balanced and imbalanced classification problems, and regression
  problems, individually. This will enable a more robust development
  process and prevent avoidable bugs.

## :sparkles: Improvements

- **weighted classification metrics:** The `cmatrix()`-function now
  accepts the argument `w` which is the sample weights; if passed the
  respective method will return the weighted metric. Below is an example
  using sample weights for the confusion matrix,

``` r
## 1) define actual and 
## predicted values with
## sample weights
actual    <- factor(sample(letters[1:3], 50, replace = TRUE))
predicted <- factor(sample(letters[1:3], 50, replace = TRUE))
weights   <- runif(length(actual))

## 2) compute weighted
## and unweighted confusion
## matrix
SLmetrics::cmatrix(
    actual    = actual,
    predicted = predicted
)
#>    a  b  c
#> a  8  4  6
#> b  4  3  5
#> c  4 10  6

SLmetrics::cmatrix(
    actual    = actual,
    predicted = predicted,
    w         = weights
)
#>          a        b        c
#> a 2.858602 2.064648 4.187036
#> b 1.598406 1.395218 3.285804
#> c 1.457663 4.459990 3.001868
```

Calculating weighted metrics using the `<factor>`- or
`<cmatrix>`-method,

``` r
## 1) weigthed confusion matrix
## and weighted accuray
confusion_matrix <- SLmetrics::cmatrix(
    actual    = actual,
    predicted = predicted,
    w         = weights
)

## 2) weighted accuracy
## using <cmatrix> method
SLmetrics::accuracy(
    confusion_matrix
)
#> [1] 0.2984745

## 2) weighted accuracy
## using <factor> method
SLmetrics::weighted.accuracy(
    actual    = actual,
    predicted = predicted,
    w         = weights
)
#> [1] 0.2984745
```

Please note, however, that it is not possible to pass `cmatrix()`-into
`weighted.accuracy()`. See below:

``` r
try(
    SLmetrics::weighted.accuracy(
        confusion_matrix
    )
)
#> Error in UseMethod(generic = "weighted.accuracy", object = ..1) : 
#>   no applicable method for 'weighted.accuracy' applied to an object of class "cmatrix"
```

## :bug: Bug-fixes

- **Floating precision:** Metrics would give different results based on
  the method used. This means that `foo.cmatrix()` and `foo.factor()`
  would produce different results (See Issue
  https://github.com/serkor1/SLmetrics/issues/16). This has been fixed
  by using higher precision `Rcpp::NumericMatrix` instead of
  `Rcpp::IntegerMatrix`.

- **Miscalculation of Confusion Matrix elements:** An error in how `FN`,
  `TN`, `FP` and `TP` were calculated have been fixed. No issue has been
  raised for this bug. This was not something that was caught by the
  unit-tests, as the total samples were too high to spot this error. It
  has, however, been fixed now. This means that all metrics that uses
  these explicitly are now stable, and produces the desired output.

- **Calculation Error in Fowlks Mallows Index:** A bug in the
  calculation of the `fmi()`-function has been fixed. The
  `fmi()`-function now correctly calculates the measure.

- **Calculation Error in Pinball Deviance and Concordance Correlation
  Coefficient:** See issue
  https://github.com/serkor1/SLmetrics/issues/19. Switched to unbiased
  variance calculation in `ccc()`-function. The `pinball()`-function
  were missing a weighted quantile function. The issue is now fixed.

- **Calculation Error in Balanced Accuracy:** See issue
  https://github.com/serkor1/SLmetrics/issues/24. The function now
  correctly adjusts for random chance, and the result matches that of
  {scikit-learn}

- **Calculation Error in F-beta Score:** See issue
  https://github.com/serkor1/SLmetrics/issues/23. The function werent
  respecting `na.rm` and `micro`, this has been fixed accordingly.

- **Calculation Error in Relative Absolute Error:** The function was
  incorrectly calculating means, instead of sums. This has been fixed.

## :boom: Breaking changes

- All regression metrics have had `na.rm`- and `w`-arguments removed.
  All weighted regression metrics have a separate function on the
  `weighted.foo()` to increase consistency across all metrics. The new
  function call is given below:

``` r
## 1) define actual and
## predicted values
actual    <- rnorm(n = 50)
predicted <- actual + rnorm(n = 50)
w         <- runif(n = 50)

## 2) weighted and unweighted
## root mean squared error
SLmetrics::rmse(actual, predicted)
#> [1] 0.9109375
SLmetrics::weighted.rmse(actual, predicted, w = w)
#> [1] 0.7965708
```

- The `rrmse()`-function have been removed in favor of the
  `rrse()`-function. This function was incorrectly specified and
  described in the package.

# :bookmark: Version 0.1-1

## :hammer_and_wrench: General

- **Backend changes:** All pair-wise metrics are moved from
  [{Rcpp}](https://github.com/RcppCore/Rcpp) to `C++`, this have reduced
  execution time by half. All pair-wise metrics are now faster.

## :sparkles: Improvements

- **NA-controls:** All pair-wise metrics that don’t have a
  `micro`-argument were handling missing values as according to C++ and
  {Rcpp} internals. See
  [Issue](https://github.com/serkor1/SLmetrics/issues/8). Thank you
  @EmilHvitfeldt for pointing this out. This has now been fixed so
  functions use an `na.rm`-argument to explicitly control for this. See
  below,

``` r
## 1) define actual and
## predicted classes
actual    <- factor(c("no", "yes", "yes"))
predicted <- factor(c(NA, "no", "yes"))

## 2) calculate
## accuracy with
## and without na.rm
SLmetrics::accuracy(
    actual    = actual,
    predicted = predicted,
    na.rm     = TRUE
)
#> [1] 0.5

SLmetrics::accuracy(
    actual    = actual,
    predicted = predicted,
    na.rm     = FALSE
)
#> [1] NaN
```

## :bug: Bug-fixes

- The `plot.prROC()`- and `plot.ROC()`-functions now adds a line to the
  plot when `panels = FALSE`. See Issue
  https://github.com/serkor1/SLmetrics/issues/9.

``` r
## 1) define actual classes
## and response probabilities
actual <- factor(
    sample(letters[1:3], size = 50, replace = TRUE)
)

response <- rbeta(
    n = 50,
    shape1 = 20,
    shape2 = 2
)

## 2) define ROC and
## prROC objects
roc_obj <- SLmetrics::ROC(
    actual   = actual,
    response = response 
)

pr_obj <- SLmetrics::prROC(
    actual   = actual,
    response = response 
)
```

``` r
## set plot grid
par(mfrow = c(1,2))

## plot data
## with panels = FALSE
plot(roc_obj, panels = FALSE)
```

<img src=".meta/changelog/src/v0.1-1_files/figure-commonmark/unnamed-chunk-4-1.png"
style="width:100.0%" />

``` r
plot(pr_obj, panels = FALSE)
```

<img src=".meta/changelog/src/v0.1-1_files/figure-commonmark/unnamed-chunk-4-2.png"
style="width:100.0%" />

# :package: [{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) Version 0.1-0

[{SLmetrics}](https://slmetrics-docs.gitbook.io/v1) is a collection of
Machine Learning performance evaluation functions for supervised
learning written in `C++` with
[{Rcpp}](https://github.com/RcppCore/Rcpp). Visit the online
documentation on [Github pages](https://slmetrics-docs.gitbook.io/v1).

## :information_source: Basic usage

### Classification metrics

``` r
## 1) define actual and
## predicted classes
actual <- factor(
    sample(letters[1:3], size = 10, replace = TRUE)
)

predicted <- factor(
    sample(letters[1:3], size = 10, replace = TRUE)
)

## 2) print values
print(actual)
#>  [1] a c a c a b c a a a
#> Levels: a b c
```

``` r
## 1) compute and summarise the
## the confusion matrix
summary(
    confusion_matrix <- SLmetrics::cmatrix(
        actual    = actual,
        predicted = predicted
    )
)
#> Confusion Matrix (3 x 3) 
#> ================================================================================
#>   a b c
#> a 2 2 2
#> b 0 0 1
#> c 1 1 1
#> ================================================================================
#> Overall Statistics (micro average)
#>  - Accuracy:          0.30
#>  - Balanced Accuracy: 0.22
#>  - Sensitivity:       0.30
#>  - Specificity:       0.65
#>  - Precision:         0.30
```

``` r
## 1) false positive rate
## using <cmatrix> method
SLmetrics::fpr(confusion_matrix)
#>         a         b         c 
#> 0.2500000 0.3333333 0.4285714

## 2) false positive rate
## using <factor> method
SLmetrics::fpr(
    actual    = actual, 
    predicted = predicted
)
#>         a         b         c 
#> 0.2500000 0.3333333 0.4285714
```

### Regression metrics

``` r
## 1) define actual and
## predicted values
actual <- rnorm(n = 10)
predicted <- actual + rnorm(n = 10)
```

``` r
## 1) calculate Huber Loss and
## Root Mean Squared Error
SLmetrics::huberloss(
    actual    = actual,
    predicted = predicted
)
#> [1] 0.4444274

SLmetrics::rmse(
    actual    = actual,
    predicted = predicted
)
#> [1] 1.026454
```
