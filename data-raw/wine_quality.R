# 1) load data from
# extdata
DT <- data.table::fread(
  input = "inst/extdata/winequality-white.csv"
)

# 2) replace whitespace
# with subscripts
data.table::setnames(
  x = DT,
  old = colnames(DT),
  new = gsub(
    pattern = "\\s",
    replacement = "_",
    colnames(DT)
  )
)

# 3) classify quality
# as:
#    High Quality: quality >= 7
#    Low Quality: quality <= 4
#    Medium Quality otherwise
DT[
  ,
  class := data.table::fcase(
    default = "Medium Quality",
    quality >= 7, "High Quality",
    quality <= 4, "Low Quality"
  )
  ,
][
  ,
  class := factor(
    x = class,
    levels  = c("High Quality", "Medium Quality", "Low Quality")
  )
  ,
]

# 4) store data
# as wine_quality

# 4.1) convert to data.frame
wine_quality <- list(
  features = as.data.frame(DT[,-c("class", "quality")]),
  target   = list(
    regression = DT$quality,
    class      = DT$class
  )
)

# 4.2) store
usethis::use_data(
  wine_quality,
  internal = FALSE,
  overwrite = TRUE
)
