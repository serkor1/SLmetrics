# script: Build MD
# author: Serkan Korkmaz
# date: 2025-04-19
# objective: Convert .Rd files to Markdown
# via Pandoc and Rd2HTML from {tools}
# script start;

# 1) list all .RD files
#    in man/ by task and
#    remove those with "documentation"
all_files <- grep(
  pattern = "documentation",
  # List all files
  x = list.files(
    path = "man",
    pattern = "classification_|regression_",
    full.names = TRUE
  ), # list.files end
  invert = TRUE,
  value = TRUE
)

# 1.1) split file names
#      by "_"
parts <- strsplit(
  x = basename(all_files), 
  split = "_", 
  fixed = TRUE
)

# 1.2) extract the task
#      from the parts
tasks <- vapply(
  X = parts, 
  FUN = `[`, 
  1, 
  FUN.VALUE = character(1)
)


# 1.3) split the files
#      by task
all_files <- split(all_files, tasks)

# 2) extract all
#    common functions; accuracy, rmse etc
all_metrics <- lapply(all_files, function(x){

  metrics <- unique(gsub(
    pattern = "classification_|regression_|weighted\\.|\\.factor|\\.numeric|\\.matrix|\\.cmatrix|\\.Rd",
    replacement = "",
    basename(x)
  ))
  
  metrics <- metrics[metrics != ""]
  
  metrics

})

# 2.2) split files by task and
#      metrics. Note, we do this
#      as .meta/DOCUMENTATION/gitbook organizes everything
#      by folders
files_by_task_and_metric <- mapply(
  FUN = function(paths, metrics) {
    # for this task, build a named list of length(metrics)
    setNames(
      lapply(metrics, function(m) {
        # pick out any path whose basename contains “_metric” right before a dot
        paths[grepl(paste0("_", m, "\\."), basename(paths))]
      }),
      metrics
      
    )
  },
  paths   = all_files,
  metrics = all_metrics,
  SIMPLIFY = FALSE
)

# 2.2.1) Rename each element
#        to task metrics - this will be displayed 
#        properly by .meta/DOCUMENTATION/Gitbook

files_by_task_and_metric$classification <- setNames(
    object = files_by_task_and_metric$classification,
    nm = sapply(files_by_task_and_metric$classification, function(x){
        as.character(Filter(function(x) attr(x, "Rd_tag")== "\\title", tools::parse_Rd(x[1]))[[1]])
    })
)

files_by_task_and_metric$regression <- setNames(
    object = files_by_task_and_metric$regression,
    nm = sapply(files_by_task_and_metric$regression, function(x){
        as.character(Filter(function(x) attr(x, "Rd_tag")== "\\title", tools::parse_Rd(x[1]))[[1]])
    })
)

names(files_by_task_and_metric) <- tools::toTitleCase(
    text = paste(names(files_by_task_and_metric), "metrics")
)



# 3) Write the HTML files
#    to a temporary location
out_base <- tempdir()
for (task in names(files_by_task_and_metric)) {
  
  for (metric in names(files_by_task_and_metric[[task]])) {
    
    # build the output directory for this task/metric
    out_dir <- file.path(out_base, task, metric)
    if (!dir.exists(out_dir)) {
      dir.create(out_dir, recursive = TRUE)
    }
    
    # for each Rd in this group, render to HTML
    for (rd_path in files_by_task_and_metric[[task]][[metric]]) {
      html_name <- sub("\\.Rd$", ".html", basename(rd_path))
      out_file  <- file.path(out_dir, html_name)
      
      # convert and write
      tools::Rd2HTML(rd_path, out = out_file)
    }
  }
}

# 3.1) get all temporary files
#      and convert to markdown
html_files <- list.files(
  path       = out_base, 
  recursive  = TRUE,
  pattern    = "*.html",
  full.names = TRUE
)


# 3.2) convert to markdown
#      and store
for (html in html_files) {
    rel <- sub(out_base, "", html)
    md  <- file.path(".meta/documentation/gitbook", sub("\\.html$", ".md", rel))
    md  <- gsub("[a-z]*_", "", md)
    
    # make sure the directory exists
    dir.create(dirname(md), recursive = TRUE, showWarnings = FALSE)
    
    # call pandoc
    system2("pandoc", args = c(
      "-f", "html",
      "-t", "gfm+raw_html",
      "--wrap=auto",
      shQuote(html),
      "-o", shQuote(md)
    ))
  }

# 3.3) execute shell script
#      NOTE: it might be more consistent
#      to call this separately
system2(
  ".meta/development_tools/scripts/build_toc.sh"
)

# 4) move relevant files
#    to documentation
file_list <- list.files(
  path       = ".meta/documentation",
  pattern    = "*.md",
  full.names = TRUE 
)

# 4.1) move NEWS from project 
#      root. 
#      NOTE: Has to be a folder at some point
file_list <- c(file_list, "NEWS.md")

# 4.2) remove the original summary
#      file
file_list <- grep(
  pattern = "summary",
  x       = file_list,
  ignore.case = TRUE,
  invert  = TRUE,
  value   = TRUE  
)

# 4.3) copy files to gitbook
#      folder
for (file in file_list) {
  file.copy(
    from = file,
    to   = paste0(".meta/documentation/gitbook/", basename(file)),
    overwrite = TRUE
  )
}

# script end;