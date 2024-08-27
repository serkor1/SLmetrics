# script: zzz
# author: Serkan Korkmaz
# objective: Write a package startup message
# date: 2024-08-27
# start of script; ###

.onAttach <- function(
    libname,
    pkgname,
    ...) {

  packageStartupMessage(
    paste0(
      # startup
      "Loading {SLmetrics} v",

      # version
      utils::packageVersion(pkgname)
    )
  )
}

# end of script; ###
