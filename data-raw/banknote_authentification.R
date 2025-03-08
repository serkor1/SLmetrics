# 1) load data from
# ext data
banknote <- data.table::fread(
  input = "inst/extdata/banknote-authentication.txt",
  col.names = c(
    "variance",
    "skewness",
    "curtosis",
    "entropy",
    "class"
  )
)

# 2) recode class
banknote[
  ,
  class := factor(
    x = class,
    levels = c(1,0),
    labels = c("inauthentic", "authentic")
  )
  ,
]

# 3) convert to data.frame
banknote <- as.data.frame(
  banknote
)

# 3.1) store data
usethis::use_data(
  banknote,
  internal  = FALSE,
  overwrite = TRUE
)