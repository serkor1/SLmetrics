# objective:
# create a lookup table that
# maps .Rd to appropriate titles
# script start;

# 1) create a data.table with 
# all .Rd files
DT_ <- data.table::data.table(
  rd_path  = list.files(
    path = "man",
    pattern = ".Rd",
    full.names = TRUE
  )
)

# 2) extact base-name
# of the path without extension
DT_[
  ,
  `:=`(
    name = gsub(".Rd", "", basename(rd_path))
  )
  ,
]

# 3) map to titles
# for the documenation
DT_[
  ,
  `:=`(
    title = data.table::fcase(
      default = NA_character_,
      name == "accuracy", "accuracy_c",
      name == "baccuracy", "balanced accuracy_c",
      name == "ccc", "concordance correlation coefficient_r",
      name == "ckappa", "cohens kappa_c",
      name == "cmatrix", "confusion matrix_c",
      name == "dor", "diagnostic odds ratio_c",
      name == "entropy", "entropy_c",
      name == "fbeta", "f-beta score_c",
      name == "fdr", "false discovery rate_c",
      name == "fer", "false omission rate_c"
    )
  )
  ,
][
  ,
  c("title", "type") := data.table::tstrsplit(title, "_")
  ,
]

# 4) subset such that only 
# mapped functions are available
DT <- DT_[
  !is.na(title)
]

# 4.1) stop the script if
# no functions have been 
# documented
if (nrow(DT) == 0) {
  stop(
    "No functions are documented - whats your plan here?",
    call. = FALSE
  )
}

# 4.2) document which functions
# missing
if (nrow(DT) != nrow(DT_)) {

  cat("Missing documentation:\n")
  cat("======================\n")
  
  print(
    data.table::fsetdiff(
      x = DT_[,.(rd_path),],
      y = DT[,.(rd_path),]
    )[]
  )
 

}
# script end;