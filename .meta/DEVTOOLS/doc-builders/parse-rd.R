# Function to convert HTML headers to Markdown headers
convert_headers <- function(text) {
  # Iterate from h6 to h1 to prevent nested replacements
  for (level in 6:1) {
    # Create regex pattern for the current header level
    pattern <- paste0("<h(", level, ")\\s*[^>]*>(.*?)</h\\1>")
    
    # Create replacement string with the appropriate number of '#'
    replacement <- paste0(stringi::stri_dup("#", level), " $2")
    
    # Perform the replacement
    text <- stringi::stri_replace_all_regex(
      text,
      pattern,
      replacement,
      vectorize_all = FALSE,
      case_insensitive = TRUE,
      dotall = TRUE
    )
  }
  return(text)
}


# Function to clean R code chunks by removing lines starting with '#>'
clean_r_code_chunks <- function(text) {
  # Regex pattern to match R code chunks
  # Captures the content inside ```{r} ... ```
  pattern <- "```\\{r\\}\\n([\\s\\S]*?)\\n```"
  
  # Find all matches
  matches <- stringi::stri_match_all_regex(text, pattern, omit_no_match = TRUE)[[1]]
  
  # If no matches found, return text as is
  if (nrow(matches) == 0) {
    return(text)
  }
  
  # Iterate through each match and clean the code chunk
  for (i in seq_len(nrow(matches))) {
    full_match <- matches[i, 1]  # Entire code chunk
    code_content <- matches[i, 2]  # Code inside the chunk
    
    # Split the code into individual lines
    lines <- stringi::stri_split_lines(code_content, omit_empty = FALSE)[[1]]
    
    # Remove lines that start with '#>'
    cleaned_lines <- lines[!stri_detect_regex(lines, "^#>")]
    
    # Rejoin the cleaned lines
    cleaned_code <- stringi::stri_c(cleaned_lines, collapse = "\n")
    
    # Reconstruct the cleaned code chunk
    cleaned_chunk <- stringi::stri_c("```{r, eval = FALSE}\n", cleaned_code, "\n```")
    
    # Replace the original chunk with the cleaned chunk in the text
    text <- stringi::stri_replace_first_fixed(text, full_match, cleaned_chunk)
  }
  
  return(text)
}


# New helper function to remove unwanted text and structure
clean_content <- function(text, title) {

  # 1) define all regex patterns
  # and their replacements
  lst_regex <- list(
    regex = c(
      # convert math
      "(?s)<p\\s+style=\"text-align:\\s*center;?\">\\s*<code\\s+class=\"reqn\">(.*?)</code>\\s*</p>",
      "(?s)<code\\s+class=\"reqn\">(.*?)</code>",
      "(&lt;[^&gt]+&gt;)",
      # convert >
      "&lt;",
      "&gt;",
      
      # convert inline code
      "<code>(.*?)</code>",
      # clean precode
      "<pre>\\s*<code\\s+class=['\"]language-R['\"]>\\s*([\\s\\S]*?)\\s*</code>\\s*</pre>",
      # convert divs to code chunks
      '<div\\s+class=["\']sourceCode\\s+r["\']>\\s*<pre>\\s*([\\s\\S]*?)\\s*</pre>\\s*</div>',
      # remove top-part of the HTML
      "<!DOCTYPE html[\\s\\S]*?<main>",
      "</main>[\\s\\S]*?</html>",
      # remove "creating factor"-section 
      "### Creating[\\s\\S]*?(?=### Examples)",
      # remove see also section
      "### See Also[\\s\\S]*?(?=### Examples)",
      "Other Classification:[\\s\\S]*?(?=###)"
    ),
    replacement = c(
      # $$ \n $$
      "\\$\\$$1\\$\\$",
      # $ $
      "\\$$1\\$",
      "`$1`",
      "<",
      ">",
      "`$1`",
      "```{r, eval = FALSE}\n$1\n```",
      "```{r}\n$1\n```",
      "",
      "",
      "",
      "",
      ""
    )
  )

  # 1.2) check if correctly
  # specified
  stopifnot(
    length(lst_regex$regex) == length(lst_regex$replacement)
  )

  # 2) replace all
  # text
  text <- text
  for (i in 1:length(lst_regex$regex)) {

    text <- stringi::stri_replace_all_regex(
      str = text,
      pattern = lst_regex$regex[i],
      replacement = lst_regex$replacement[i],
      vectorize_all = TRUE,
      case_insensitive = TRUE
    )

  }

  # 3) Add {.unnumbered}
  text <- stringi::stri_replace_first_regex( # was: stri_replace_all_regex
    text,
    pattern ="(?m)^(##\\s+)(.+)$",
    replacement = paste("##", title, "{.unnumbered}")
  )

  
  return(text)
}

process_html_to_markdown <- function(
  input_file, 
  output_file, 
  title) {
  
  if (!file.exists(input_file)) {
    stop("Input file does not exist: ", input_file)
  }
  
  html_content <- readLines(input_file, warn = FALSE, encoding = "UTF-8")
  markdown_text <- stringi::stri_c(html_content, collapse = "\n")
  

  markdown_text <- convert_headers(markdown_text)
  markdown_text <- clean_r_code_chunks(markdown_text)
  
  markdown_text <- clean_content(markdown_text, title)
  
  writeLines(markdown_text, output_file, useBytes = TRUE)
}

