# Re-render README
rmarkdown::render(
  input = "README.Rmd",
  output_format = "github_document",
  clean = TRUE
)

# Re-render NEWS
rmarkdown::render(
  input = "NEWS.Rmd",
  output_format = "github_document",
  clean = TRUE
)