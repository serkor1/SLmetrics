# 1) load data from
# ext data
DT <- data.table::fread(
  input = "inst/extdata/obesity.csv"
)

# 2) recode column names
# to lower
data.table::setnames(
  x   = DT,
  old = colnames(DT),
  new = tolower(
    colnames(
      DT
    )
  )
)

# 3) create class variable
# (target)
DT[
  ,
  class := factor(
    x = nobeyesdad,
    levels = sort(unique(DT$nobeyesdad))
  )
  ,
][
  ,
  nobeyesdad := NULL
  ,
]

# 4) set all character
# cells to lower

# 4.1) locate all characters
# and convert
idx <- which(
  sapply(X = DT, FUN = inherits, "character")
)

DT[
  ,
  (idx) := lapply(.SD, tolower)
  ,
  .SDcols = idx
]

# 5) convert all variable
# to binary where possible
DT[
  ,
  `:=`(
    male = as.integer(gender == "male"),
    favc = as.integer(favc == "yes"),
    family_history_with_overweight = as.integer(
      family_history_with_overweight == "yes"
    ),
    smoke = as.integer(smoke == "yes"),
    scc = as.integer(scc == "yes")

  )
  ,
][
  ,
  `:=`(
    gender = NULL
  )
  ,
]

# 6) recode remaining
# character variable as 
# factors
idx <- which(
  sapply(X = DT, FUN = inherits, "character")
)

DT[
  , 
  (idx) := lapply(.SD, function(x) {
    factor(x, levels = sort(unique(x)))
   }
  )
, 
.SDcols = idx
]

# 7) reorder columns

# 7.1) locate factors
factor_cols <- names(DT)[sapply(DT, is.factor)]

# 7.2) locate numeric and integers
integer_cols <- names(DT)[sapply(DT, inherits, c("integer"))]
numeric_cols <- names(DT)[sapply(DT, inherits, c("numeric"))]

# 7.3) store new order
new_order <- c(factor_cols, integer_cols, numeric_cols)

# 7.4) set new column order
data.table::setcolorder(DT, new_order)
data.table::setcolorder(DT, c("class", "weight"), after = ncol(DT))

# 8) convert to data.frame
obesity <- as.data.frame(
  DT
)

# 8.1) store data
usethis::use_data(
  obesity,
  internal  = FALSE,
  overwrite = TRUE
)