# objective: test that the metric
# implemented in {SLmetrics} is aligned
# with target functions

testthat::test_that(desc = "Test `cross.entropy()`-function", code ={

  # 0) matrix generator
  # for the tests
  rand.sum <- function(n){
    x <- sort(runif(n-1))
    c(x,1) - c(0,x)
  }

  # 1) generate values
  # for the tests
  pk <- t(replicate(10,rand.sum(1e3)))
  qk <- t(replicate(10,rand.sum(1e3)))

  # 2) test with and without
  # parallel processing
  for (lgl in c(TRUE, FALSE)) {
    # 2.1) test by MARGIN
    # In scipy - 0: column, 1: row, NULL: total
    # In SLmetrics - 0: total, 1: row, 2: column
    for (axis in c(0, 1, 2)) {
      for (base in c(NA,2, 10)) {

        # 2.1.1) set OpenMP flags
        invisible({ setUseOpenMP(lgl) })
      
        # 2.1.2) calculate scores
        score <- cross.entropy(pk, qk, axis = axis, base = if (is.na(base)) {-1} else {base})
        
        # Map SLmetrics axis to scipy axis:
        # SLmetrics: axis = 0 -> scipy: NULL
        # SLmetrics: axis = 1 -> scipy: 0
        # SLmetrics: axis = 2 -> scipy: 1
        py_axis <- if (axis == 0) NULL else as.integer(axis - 1)
        py_score <- ref_entropy(pk, qk, type = 2, axis = py_axis, base = if (is.na(base)) {NULL} else {base})
        
        # 2.1.3) verify equivalence
        testthat::expect_true(
          set_equal(
            as.numeric(score),
            as.numeric(py_score)
          ),
          info = paste(
            "OpenMP = ", lgl,
            "axis =", axis,
            "base =", base
          )
        )

      }
      
      
    }
  }
  

})