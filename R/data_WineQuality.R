#' @title Wine Quality Dataset
#'
#' @description
#' This dataset contains various chemical properties of white wines, along with their quality ratings and classifications.
#' 
#' @usage
#' #' data(wine_quality, package = "SLmetrics")
#'
#' @format A [data.frame] with 4898 rows and 13 variables:
#' \describe{
#'   \item{fixed_acidity}{[numeric] Fixed acidity of the wine.}
#'   \item{volatile_acidity}{[numeric] Volatile acidity of the wine.}
#'   \item{citric_acid}{[numeric] Citric acid content.}
#'   \item{residual_sugar}{[numeric] Residual sugar content.}
#'   \item{chlorides}{[numeric] Chloride content.}
#'   \item{free_sulfur_dioxide}{[numeric] Free sulfur dioxide content.}
#'   \item{total_sulfur_dioxide}{[numeric] Total sulfur dioxide content.}
#'   \item{density}{[numeric] Density of the wine.}
#'   \item{pH}{[numeric] pH level of the wine.}
#'   \item{sulphates}{[numeric] Sulfate content.}
#'   \item{alcohol}{[numeric] Alcohol percentage.}
#'   \item{quality}{Integer. Quality rating of the wine (0-10).}
#'   \item{class}{Factor w/ 3 levels "High Quality", "Medium Quality", "Low Quality". Wine quality classification based on the quality rating: \code{High Quality} (quality >= 7), \code{Low Quality} (quality <= 4), and \code{Medium Quality} otherwise.}
#' }
#' 
#' @details
#' 
#' The dataset was processed as follows:
#' 
#' \enumerate{
#'   \item Classified wine quality into three categories based on the quality rating:
#'     \itemize{
#'       \item \code{High Quality}: quality >= 7
#'       \item \code{Low Quality}: quality <= 4
#'       \item \code{Medium Quality}: otherwise
#'     }
#' }
#' 
#' @references \url{https://archive.ics.uci.edu/ml/datasets/Wine+Quality}
"wine_quality"