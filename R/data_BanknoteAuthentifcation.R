#' @title Banknote Authentication Dataset
#'
#' @description 
#' This dataset contains features extracted from images of genuine and forged banknotes, used to evaluate the performance of various classification algorithms in distinguishing between authentic and counterfeit currency.
#' 
#' @usage
#' data(banknote, package = "SLmetrics")
#'
#' @format A [data.frame] with 1,372 rows and 5 variables:
#' \describe{
#'   \item{variance}{[numeric] Variance of the Wavelet Transformed image.}
#'   \item{skewness}{[numeric] Skewness of the Wavelet Transformed image.}
#'   \item{curtosis}{[numeric] Curtosis (kurtosis) of the Wavelet Transformed image.}
#'   \item{entropy}{[numeric] Entropy of the image.}
#'   \item{class}{[factor] Authenticity of the banknote: \code{"authentic"} or \code{"inauthentic"}.}
#' }
#'
#' @details
#' Data were extracted from images taken from genuine and forged banknote-like specimens. For digitization, an industrial camera typically used for print inspection was utilized, capturing images with a resolution of about 400x400 pixels at 660 dpi. Wavelet Transform tools were employed to extract the features: variance, skewness, curtosis, and entropy. The \code{class} variable indicates the authenticity of the banknote, with \code{"authentic"} representing genuine banknotes and \code{"inauthentic"} representing forgeries.
#'
#' @source
#' Lohweg, V. (2012). Banknote Authentication Dataset. UCI Machine Learning Repository. \doi{10.24432/C55P57}
"banknote"

