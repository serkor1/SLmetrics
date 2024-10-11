# script: Utilities
# date: 2024-09-27
# author: Serkan Korkmaz, serkor1@duck.com
# objective: A collection of utilities
# to make the programming easier
# script start;

# summary line
full_line <- function() {

  console_width <- getOption("width")

  separator <- paste(
    rep("=", console_width),
    collapse = ""
    )

  # Print the separator
  cat(separator, sep = "\n")

}

# script end;
