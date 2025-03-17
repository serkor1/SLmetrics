# objective: Convert all .Rd files
# .qmd - has to be in docs/references
# at a later (tm) point regression and classification will 
# be divided 
# script start;
rm(list = ls()); invisible(gc())

# 1) load look up table
# from file
source(".meta/DEVTOOLS/doc-builders/lookup-table.R")

# 1.1) load all functions
# from parse-rd.R
source(".meta/DEVTOOLS/doc-builders/parse-rd.R")


# 2) generate qmd-files
# based on the look-up table

N <- nrow(DT)
pb <- txtProgressBar(
  min = 0, 
  max = N, 
  style = 3
)  

for (i in seq_len(N)) {

  # 2.1) generate temporary 
  # html file
  html <- tempfile(
    pattern = "file", 
    tmpdir = tempdir(), 
    fileext = ".html"
  )

  # 2.2) convert .Rd to
  # HTML
  rd <- tools::Rd2HTML(
    tools::parse_Rd(DT$rd_path[i]),
    out = html
  )

  # 2.3) process the html
  # file and store in docs/references
  if (DT$type[i] == "r") {
    process_html_to_markdown(
      input_file = html,
      output_file = paste0(".meta/DOCUMENTATION/ref_regression/", DT$name[i] ,".qmd"),
      title = DT$title[i]
    )
  } else {
    process_html_to_markdown(
      input_file = html,
      output_file = paste0(".meta/DOCUMENTATION/ref_classification/", DT$name[i] ,".qmd"),
      title = DT$title[i]
    )
  }
  
  
   # Update progress bar
   setTxtProgressBar(pb, i)

}

close(pb)

# script end;
