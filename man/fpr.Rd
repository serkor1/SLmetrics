% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R, R/S3_FalsePositiveRate.R
\name{fpr.factor}
\alias{fpr.factor}
\alias{fpr.cmatrix}
\alias{fallout.factor}
\alias{fallout.cmatrix}
\alias{fpr}
\alias{fallout}
\title{Compute the \eqn{\text{false}} \eqn{\text{positive}} \eqn{\text{rate}}}
\usage{
\method{fpr}{factor}(actual, predicted, micro = NULL, na.rm = TRUE, ...)

\method{fpr}{cmatrix}(x, micro = NULL, na.rm = TRUE, ...)

\method{fallout}{factor}(actual, predicted, micro = NULL, na.rm = TRUE, ...)

\method{fallout}{cmatrix}(x, micro = NULL, na.rm = TRUE, ...)

fpr(...)

fallout(...)
}
\arguments{
\item{actual}{A <\link{factor}>-vector of \link{length} \eqn{n}, and \eqn{k} levels.}

\item{predicted}{A <\link{factor}>-vector of \link{length} \eqn{n}, and \eqn{k} levels.}

\item{micro}{A <\link{logical}>-value of \link{length} \eqn{1}. \link{NULL} by default. If \link{TRUE} it returns the
micro average across all \eqn{k} classes, if \link{FALSE} it returns the macro average. Otherwise class wise performance evaluation.}

\item{na.rm}{A <\link{logical}>-value of \link{length} \eqn{1}. \link{FALSE} by default. If \link{TRUE} NA values will be removed from the computation.}

\item{...}{Arguments passed into other methods.}

\item{x}{A confusion matrix created by \code{\link[=table]{table()}} or \code{\link[=cmatrix]{cmatrix()}}}
}
\value{
If \code{aggregate} is \link{FALSE} (the default), a named <\link{numeric}>-vector of \link{length} k

If \code{aggregate} is \link{TRUE}, a <\link{numeric}>-vector of \link{length} 1
}
\description{
The \code{\link[=fpr]{fpr()}}-function computes the \href{https://en.wikipedia.org/wiki/False_positive_rate}{False Positive Rate} (FPR), also known as the fall-out (\code{\link[=fallout]{fallout()}}), between
two vectors of predicted and observed \code{\link[=factor]{factor()}} values.

When \code{aggregate = TRUE}, the function returns the micro-average FPR across all classes \eqn{k}.
By default, it returns the class-wise FPR.
}
\details{
Consider a classification problem with three classes: \code{A}, \code{B}, and \code{C}. The actual vector of \code{\link[=factor]{factor()}} values is defined as follows:

\if{html}{\out{<div class="sourceCode r">}}\preformatted{## set seed
set.seed(1903)

## actual
factor(
  x = sample(x = 1:3, size = 10, replace = TRUE),
  levels = c(1, 2, 3),
  labels = c("A", "B", "C")
)
#>  [1] B A B B A C B C C A
#> Levels: A B C
}\if{html}{\out{</div>}}

Here, the values 1, 2, and 3 are mapped to \code{A}, \code{B}, and \code{C}, respectively. Now, suppose your model does not predict any \code{B}'s. The predicted vector of \code{\link[=factor]{factor()}} values would be defined as follows:

\if{html}{\out{<div class="sourceCode r">}}\preformatted{## set seed
set.seed(1903)

## predicted
factor(
  x = sample(x = c(1, 3), size = 10, replace = TRUE),
  levels = c(1, 2, 3),
  labels = c("A", "B", "C")
)
#>  [1] C A C C C C C C A C
#> Levels: A B C
}\if{html}{\out{</div>}}

In both cases, \eqn{k = 3}, determined indirectly by the \code{levels} argument.
}
\section{Calculation}{


The metric is calculated for each class \eqn{k} as follows,

\deqn{
  \frac{\#FP_k}{\#FP_k + \#TN_k}
}

Where \eqn{\#FP_k} and \eqn{\#TN_k} represent the number of false positives and true negatives, respectively, for each class \eqn{k}.

When \code{aggregate = TRUE}, the micro-average is calculated across all classes,

\deqn{
  \frac{\sum_{k=1}^k \#FP_k}{\sum_{k=1}^k \#FP_k + \sum_{k=1}^k \#TN_k}
}

The FPR is the complement of specificity, such that \eqn{\text{FPR} = 1 - \text{Specificity}}.
}

\examples{
# 1) recode Iris
# to binary classification
# problem
iris$species_num <- as.numeric(
  iris$Species == "virginica"
)

# 2) fit the logistic
# regression
model <- glm(
  formula = species_num ~ Sepal.Length + Sepal.Width,
  data    = iris,
  family  = binomial(
    link = "logit"
  )
)

# 3) generate predicted
# classes
predicted <- factor(
  as.numeric(
    predict(model, type = "response") > 0.5
  ),
  levels = c(1,0),
  labels = c("Virginica", "Others")
)

# 3.1) generate actual
# classes
actual <- factor(
  x = iris$species_num,
  levels = c(1,0),
  labels = c("Virginica", "Others")
)

# 4) evaluate performance
# 4.1) by class
fpr(
  actual    = actual,
  predicted = predicted
)

# 4.2) macro-average
fpr(
  actual    = actual,
  predicted = predicted,
  micro     = FALSE
)

# 4.3) micro-average
fpr(
  actual    = actual,
  predicted = predicted,
  micro     = TRUE
)
}
\seealso{
Other classification: 
\code{\link{ROC.factor}()},
\code{\link{accuracy.factor}()},
\code{\link{baccuracy.factor}()},
\code{\link{ckappa.factor}()},
\code{\link{cmatrix}()},
\code{\link{dor.factor}()},
\code{\link{fbeta.factor}()},
\code{\link{fdr.factor}()},
\code{\link{fer.factor}()},
\code{\link{fmi.factor}()},
\code{\link{jaccard.factor}()},
\code{\link{mcc.factor}()},
\code{\link{nlr.factor}()},
\code{\link{npv.factor}()},
\code{\link{plr.factor}()},
\code{\link{prROC.factor}()},
\code{\link{precision.factor}()},
\code{\link{recall.factor}()},
\code{\link{specificity.factor}()},
\code{\link{zerooneloss.factor}()}
}
\concept{classification}
