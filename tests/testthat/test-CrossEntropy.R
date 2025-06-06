# objective: test that the metric
# implemented in {SLmetrics} is aligned
# with target functions

testthat::test_that(desc = "Test `cross.entropy()`-function", code ={

  testthat::skip_on_cran()

  ## 0) matrix generator
  ## for the tests
  rand.sum <- function(n){
    x <- sort(runif(n-1))
    c(x,1) - c(0,x)
  }

  ## 1) generate values
  ## for the tests
  pk <- t(replicate(10,rand.sum(3)))
  qk <- t(replicate(10,rand.sum(3)))

  ## 2) conduct tests
  ## against {scipy}
  for (dim in c(0L, 1L, 2L)) {
    for (normalize in c(FALSE, TRUE)) {

      ## 2.1) calculate shannon
      ## entropy
      score <- cross.entropy(
        pk        = pk,
        qk        = qk,
        dim       = dim,
        normalize = normalize
      )

      ## 2.2) calculate shannon
      ## entropy reference
      reference <- py_cross_entropy(
        pk  = pk,
        qk  = qk,
        dim = dim 
      )

      ## 2.2.1) normalize
      ## reference value
      if (normalize) {
        if (dim == 0 | dim == 1) reference <- reference / dim(pk)[1]
        if (dim == 2) reference <- reference / dim(pk)[2]
      }

      ## 2.3) test for equality
      ## in values
      testthat::expect_true(
        object = set_equal(
          as.numeric(score),
          as.numeric(reference)
        ),
        info = paste(
          "dim =", dim,
          "normalize = ", normalize
        )
      )

    }
  }

}
)