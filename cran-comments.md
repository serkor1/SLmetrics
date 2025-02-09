## R CMD check results

0 errors ✔ | 0 warning ✖ | 4 notes ✖

❯ checking CRAN incoming feasibility ...Warning in url(sprintf("%s/src/contrib/PACKAGES.gz", u), "rb") :
    URL 'https://CRAN.R-project.org/src/contrib/PACKAGES.gz': Timeout of 60 seconds was reached
  NB: need Internet access to use CRAN incoming checks
   [5s/152s] NOTE
  Maintainer: ‘Serkan Korkmaz <serkor1@duck.com>’
  
  Possibly misspelled words in DESCRIPTION:
    scalability (14:199)
  
  Found the following (possibly) invalid URLs:
    URL: https://r-pkg.org/pkg/SLmetrics
      From: README.md
      Status: 500
      Message: Internal Server Error

❯ checking installed package size ... NOTE
    installed size is 15.7Mb
    sub-directories of 1Mb or more:
      libs  15.4Mb

❯ checking for future file timestamps ... NOTE
  unable to verify current time

❯ checking HTML version of manual ... NOTE
  Skipping checking HTML validation: no command 'tidy' found


* This is a new release and therefore package specific links are not available before CRAN release.
