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
      name == "accuracy", "Accuracy_c",
      name == "baccuracy", "Balanced Accuracy_c",
      name == "ckappa", "Cohen's Kappa Statistic_c",
      name == "cmatrix", "Confusion Matrix_c",
      name == "dor", "Diagnostic Odds Ratio_c",
      name == "entropy", "Entropy_c",
      name == "fbeta", "F-beta Score_c",
      name == "fdr", "False Discovery Rate_c",
      name == "fer", "False Omission Rate_c",
      name == "fmi", "Fowlkes-Mallows Index_c",
      name == "fpr", "False Positive Rate_c",
      name == "jaccard", "Jaccard Score_c",
      name == "logloss", "Log Loss_c",
      name == "mpe", "Mean Percentage Error_c",
      name == "nlr", "Negative Likelihood Ratio_c",
      name == "npv", "Negative Predictive Value_c",
      name == "plr", "Positive Likelihood Ratio_c",
      name == "precision", "Precision_c",
      name == "prROC", "Precision-Recall Curve_c",
      name == "recall", "Recall_c",
      name == "rsq", "Coefficient of Determination_c",
      name == "ROC", "Receiver Operator Characteristics_c",
      name == "specificity", "Specificity_c",
      name == "zerooneloss", "Zero-One loss_c",

      # regression functions
      name == "huberloss", "Huber Loss Function_r",
      name == "mae", "Mean Absolute Error_r",
      name == "mape", "Mean Absolute Percentage error_r",
      name == "mcc", "Matthews Correlation Coefficient_r",
      name == "pinball", "Pinball Loss_r",
      name == "rae", "Relative Absolute Error_r",
      name == "rmse", "Root Mean Squared Error_r",
      name == "rmsle", "Root Mean Squared Logarithmic Error_r",
      name == "rrmse", "Relative Root Mean Squared Error_r",
      name == "rrse", "Root Relative Squared Error_r",
      name == "smape", "Symmetric Mean Absolute Percentage Error_r",
      name == "ccc", "Concordance Correlation Coefficient_r",
      name == "mse", "Mean Squared Error_r",

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
  !is.na(title) & type != "u"
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