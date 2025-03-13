# objective: Test ordering and
# sorting functions
testthat::test_that(
  desc = "Test that the `presort()` and `preorder()` functions works as expected", code = {

    # 1) generate a 4x4 matrix
    # to be sorted
    sort_me <- matrix(
      data = cbind(16:1),
      nrow = 4
    )

    # 2) test sorting algorithms
    # by decreasing and increasing
    for (decreasing in c(TRUE, FALSE)) {

      # 2.1) sort the matrix 
      # using base R
      sorted <- apply(
        X = sort_me,
        MARGIN = 2,
        FUN = function(x) {
          sort(
            x,
            decreasing = decreasing
          )
        }
      )

      # 2.2) sort using `presort`
      presorted <- presort(
        x = sort_me,
        decreasing = decreasing 
      )

      # 2.3) expect equal
      testthat::expect_equal(
        sorted,
        presorted
      )
    }

    # 3) test ordering algorithms
    # by decreasing and increasing
    for (decreasing in c(TRUE, FALSE)) {

      # 3.1) sort the matrix 
      # using base R
      ordered <- apply(
        X = sort_me,
        MARGIN = 2,
        FUN = function(x) {
          order(
            x,
            decreasing = decreasing
          )
        }
      )

      # 3.2) sort using `preorder`
      preordered <- preorder(
        x = sort_me,
        decreasing = decreasing 
      )

      # 3.3) expect equal
      testthat::expect_equal(
        ordered,
        preordered
      )
    }
    

  }
)


