#' @title Obesity Dataset
#' 
#' @description 
#' This dataset contains information used to estimate obesity levels in individuals from Mexico, Peru, and Colombia, based on their eating habits and physical conditions. It comprises 2,111 records with 17 attributes, including demographic information, lifestyle habits, and obesity levels.
#' 
#' @usage
#' data(obesity, package = "SLmetrics")
#'
#' @format A [data.frame] with 2,111 rows and 17 variables:
#' \describe{
#'   \item{caec}{[factor] Consumption of food between meals: \code{no}, \code{sometimes}, \code{frequently}, \code{always}.}
#'   \item{calc}{[factor] Frequency of alcohol consumption: \code{no}, \code{sometimes}, \code{frequently}, \code{always}.}
#'   \item{mtrans}{[factor] Mode of transportation used: \code{automobile}, \code{motorbike}, \code{bike}, \code{public_transportation}, \code{walking}.}
#'   \item{family_history_with_overweight}{[integer] Binary indicator of family history with overweight (1 = Yes, 0 = No).}
#'   \item{favc}{[integer] Binary indicator of frequent consumption of high caloric food (1 = Yes, 0 = No).}
#'   \item{fcvc}{[numeric] Frequency of vegetable consumption: \code{low} = 1, \code{normal} = 2, \code{high} = 3.}
#'   \item{ncp}{[numeric] Number of main meals per day.}
#'   \item{smoke}{[integer] Binary indicator of smoking habits (1 = Yes, 0 = No).}
#'   \item{ch2o}{[numeric] Daily water consumption in liters.}
#'   \item{scc}{[integer] Binary indicator of calorie consumption monitoring (1 = Yes, 0 = No).}
#'   \item{faf}{[numeric] Frequency of physical activity per week.}
#'   \item{tue}{[numeric] Time spent on technology devices daily in hours.}
#'   \item{male}{[integer] Binary indicator of gender (1 = Male, 0 = Female).}
#'   \item{age}{[numeric] Age of the individual in years.}
#'   \item{height}{[numeric] Height of the individual in meters.}
#'   \item{class}{[factor] Obesity level: \code{Insufficient Weight}, \code{Normal Weight}, \code{Overweight Level I}, \code{Overweight Level II}, \code{Obesity Type I}, \code{Obesity Type II}, \code{Obesity Type III}.}
#'   \item{weight}{[numeric] Weight of the individual in kilograms.}
#' }
#'
#' @details
#' The dataset was collected to analyze the relationship between eating habits, physical conditions, and obesity levels. It includes both synthetically generated data (77%) using the Weka tool and the SMOTE filter, and real data (23%) collected directly from users through a web platform. The target variable, \code{class}, categorizes individuals into various obesity levels.
#'
#' @source
#' Mendoza Palechor, F., & De la Hoz Manotas, A. (2019). Dataset for estimation of obesity levels based on eating habits and physical condition in individuals from Colombia, Peru and Mexico. Data in Brief. \doi{10.1016/j.dib.2019.104344}
#'
#' UCI Machine Learning Repository: Estimation of Obesity Levels Based On Eating Habits and Physical Condition. \url{https://archive.ics.uci.edu/dataset/544/estimation+of+obesity+levels+based+on+eating+habits+and+physical+condition}
"obesity"
