% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R, R/S3_AreaUnderTheCurve.R
\name{auc.numeric}
\alias{auc.numeric}
\alias{auc}
\title{AUC}
\usage{
\method{auc}{numeric}(y, x, method = 0L, presorted = TRUE, ...)

## Generic S3 method
auc(
 y,
 x,
 method = 0,
 presorted = TRUE,
 ...
)
}
\arguments{
\item{y}{A <\link{numeric}> vector of \link{length} \eqn{n}.}

\item{x}{A <\link{numeric}> vector of \link{length} \eqn{n}.}

\item{method}{A <\link{numeric}> value (default: \eqn{0}). Defines the underlying method of calculating the area under the curve. If \eqn{0} it is calculated using the \code{trapezoid}-method, if \eqn{1} it is calculated using the \code{step}-method.}

\item{presorted}{A <\link{logical}>-value \link{length} 1 (default: \link{FALSE}). If \link{TRUE} the input will not be sorted by threshold.}

\item{...}{Arguments passed into other methods.}
}
\value{
A <\link{numeric}>  vector  of \link{length} 1
}
\description{
The \code{\link[=auc]{auc()}}-function calculates the area under the curve.
}
\section{Definition}{


\strong{Trapezoidal rule}

The \strong{trapezoidal rule} approximates the integral of a function \eqn{f(x)} between
\eqn{x = a} and \eqn{x = b} using trapezoids formed between consecutive points. If
we have points \eqn{x_0, x_1, \ldots, x_n} (with \eqn{a = x_0 < x_1 < \cdots < x_n = b})
and corresponding function values \eqn{f(x_0), f(x_1), \ldots, f(x_n)}, the area under
the curve \eqn{A_T} is approximated by:

\deqn{
  A_T \approx \sum_{k=1}^{n} \frac{f(x_{k-1}) + f(x_k)}{2} \bigl[x_k - x_{k-1}\bigr].
}

\strong{Step-function method}

The \strong{step-function (rectangular) method} uses the value of the function at one
endpoint of each subinterval to form rectangles. With the same partition
\eqn{x_0, x_1, \ldots, x_n}, the rectangular approximation \eqn{A_S} can be written as:

\deqn{
  A_S \approx \sum_{k=1}^{n} f(x_{k-1}) \bigl[x_k - x_{k-1}\bigr].
}
}

\examples{
## 1) Ordered x and y pair
x <- seq(0, pi, length.out = 200)
y <- sin(x)

## 1.1) calculate area
ordered_auc <- auc(y = y,  x = x)

## 2) Unordered x and y pair
x <- sample(seq(0, pi, length.out = 200))
y <- sin(x)

## 2.1) calculate area
unordered_auc <- auc(y = y,  x = x)

## 2.2) calculate area with explicit
## ordering
unordered_auc_flag <- auc(
  y = y,
  x = x,
  presorted = FALSE
)

## 3) display result
cat(
  "AUC (ordered x and y pair)", ordered_auc,
  "AUC (unordered x and y pair)", unordered_auc,
  "AUC (unordered x and y pair, with unordered flag)", unordered_auc_flag,
  sep = "\n"
)
}
\seealso{
Other Tools: 
\code{\link{cov.wt.matrix}()},
\code{\link{preorder}()},
\code{\link{presort}()}
}
\concept{Tools}
