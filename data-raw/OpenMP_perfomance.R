# script start;

# 1) prelims

# 1.1) clear environment
# and garbage collection
rm(list = ls()); gc();

# 1.2) load DT list
DT <- SLmetrics:::DT

# 2) conduct OpenMP
# test on Entropy

# 2.1) define common test
# parameters
rand.sum <- function(n){
  x <- sort(runif(n-1))
  c(x,1) - c(0,x)
}

# 2.2) conduct test with
# and without OpenMP enabled

# 2.2.1) stage the testing
# ground
set.seed(1903)
pk <- t(replicate(200,rand.sum(1e6)))

# 2.2.2) Test without
# OpenMP and store
gc()
SLmetrics::openmp.off()

DT$OpenMP$FALSE_ <- bench::mark(
  SLmetrics::entropy(pk),
  min_iterations = 100
)

# 2.2.3) Test with
# OpenMP and store
gc()
SLmetrics::openmp.on()

DT$OpenMP$TRUE_ <- bench::mark(
  SLmetrics::entropy(pk),
  min_iterations = 100
)

# 3) write back to 
# DT
usethis::use_data(
  DT,
  internal  = TRUE,
  overwrite = TRUE
)

# script end;
