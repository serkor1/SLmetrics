#' @rdname data_wine.quality
#' 
#' @title Wine quality dataset
#'
#' @description
#' This dataset contains measurements of various chemical properties of white wines
#' along with their quality ratings and a quality classification. The dataset was
#' obtained from the UCI Machine Learning Repository.
#'
#' The data is provided as a list with two components:
#'
#' \describe{
#'   \item{features}{A data frame containing the chemical properties of the wines.
#'     The variables include:
#'     \describe{
#'       \item{fixed_acidity}{Fixed acidity (g/L).}
#'       \item{volatile_acidity}{Volatile acidity (g/L), mainly due to acetic acid.}
#'       \item{citric_acid}{Citric acid (g/L).}
#'       \item{residual_sugar}{Residual sugar (g/L).}
#'       \item{chlorides}{Chloride concentration (g/L).}
#'       \item{free_sulfur_dioxide}{Free sulfur dioxide (mg/L).}
#'       \item{total_sulfur_dioxide}{Total sulfur dioxide (mg/L).}
#'       \item{density}{Density of the wine (g/cm\eqn{^3}).}
#'       \item{pH}{pH value of the wine.}
#'       \item{sulphates}{Sulphates (g/L).}
#'       \item{alcohol}{Alcohol content (% by volume).}
#'     }
#'   }
#'   \item{target}{A list containing two elements:
#'     \describe{
#'       \item{regression}{A numeric vector representing the wine quality scores (used as the regression target).}
#'       \item{class}{A factor with levels \code{"High Quality"}, \code{"Medium Quality"}, and \code{"Low Quality"},
#'         where classification is determined as follows:
#'         \describe{
#'           \item{High Quality}{quality \eqn{\geq} 7.}
#'           \item{Low Quality}{quality \eqn{\leq} 4.}
#'           \item{Medium Quality}{for all other quality scores.}
#'         }
#'       }
#'     }
#'   }
#' }
#'
#' @docType data
#' @usage data(wine.quality)
#' @format A list with two components:
#' \describe{
#'   \item{features}{A data frame with 11 chemical property variables.}
#'   \item{target}{A list with two elements: \code{regression} (wine quality scores) and \code{class} (quality classification).}
#' }
#' 
#' @references
#' Cortez, Paulo, et al. "Modeling wine preferences by data mining from physicochemical properties." Decision support systems 47.4 (2009): 547-553.
#' 
#' @keywords datasets
"wine.quality"
