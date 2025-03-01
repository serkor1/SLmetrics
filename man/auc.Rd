% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R, R/S3_AreaUnderTheCurve.R
\name{auc.numeric}
\alias{auc.numeric}
\alias{auc}
\title{AUC}
\usage{
\method{auc}{numeric}(y, x, method = 0L, ordered = TRUE, ...)

## Generic S3 method
auc(
 y,
 x,
 method = 0,
 ordered = TRUE,
 ...
)
}
\arguments{
\item{y}{A <\link{numeric}> vector of \link{length} \eqn{n}.}

\item{x}{A <\link{numeric}> vector of \link{length} \eqn{n}.}

\item{method}{A <\link{numeric}> value (default: \eqn{0}). Defines the underlying method of calculating the area under the curve. If \eqn{0} it is calculated using the \code{trapezoid}-method, if \eqn{1} it is calculated using the \code{step}-method.}

\item{ordered}{A <\link{logical}> value (default: \link{TRUE}). If \link{FALSE} the \code{x} and \code{y} pair will be ordered before calculating the area under the curve.}

\item{...}{Arguments passed into other methods.}
}
\value{
A <\link{numeric}>  vector  of \link{length} 1
}
\description{
The \code{\link[=auc]{auc()}}-function calculates the area under the curve.
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
  ordered = FALSE
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
\code{\link{cov.wt.matrix}()}
}
\concept{Tools}
