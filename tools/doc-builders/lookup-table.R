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
)[
  !grepl("SLmetrics", x = rd_path)
]

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

      # classification functions
      name == "accuracy", "accuracy_c",
      name == "baccuracy", "balanced accuracy_c",
      name == "ckappa", "Cohen's kappa_c",
      name == "cmatrix", "confusion matrix_c",
      name == "dor", "diagnostic odds ratio_c",
      name == "entropy", "entropy_c",
      name == "fbeta", "F-beta score_c",
      name == "fdr", "false discovery rate_c",
      name == "fer", "false omission rate_c",
      name == "fmi", "Fowlkes-Mallows index_c",
      name == "fpr", "false positive rate_c",
      name == "jaccard", "Jaccard score_c",
      name == "logloss", "log loss_c",
      name == "mpe", "mean percentage error_c",
      name == "nlr", "negative likelihood ratio_c",
      name == "npv", "negative predictive value_c",
      name == "plr", "positive likelihood ratio_c",
      name == "precision", "precision_c",
      name == "prROC", "Precision-Recall curve_c",
      name == "recall", "recall_c",
      name == "rsq", "coefficient of determination_c",
      name == "ROC", "receiver operator characteristics_c",

      # regression functions
      name == "huberloss", "huber loss_r",
      name == "mae", "mean absolute error_r",
      name == "mape", "mean absolute percentage error_r",
      name == "mcc", "Matthews correlation coefficient_r",
      name == "pinball", "pinball loss_r",
      name == "rae", "relative absolute error_r",
      name == "rmse", "root mean squared error_r",
      name == "rmsle", "root mean squared logarithmic error_r",
      name == "rrmse", "relative root mean squared error_r",
      name == "rrse", "root relative squared error_r",
      name == "smape", "symmetric mean absolute percentage error_r",
      name == "specificity", "specificity_r",
      name == "zerooneloss", "zero-one loss_c",
      name == "ccc", "concordance correlation coefficient_r",
      name == "mse", "mean squared error_r",

      # utility functions
      name == "setNumberThreads", "set threads_u",
      name == "setUseOpenMP", "use OpenMP_u"
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