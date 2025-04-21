<div class="container">

<div role="main">

|                 |                 |
|-----------------|----------------:|
| preorder.matrix | R Documentation |

## Preorder Matrices

### Description

A generic S3 function for somehting long. This function dispatches to S3
methods in `preorder()` and performs no input validation. If you supply
NA values or vectors of unequal length (e.g. `length(x) != length(y)`),
the underlying `C++` code may trigger undefined behavior and crash your
`R` session.

#### Defensive measures

Because `preorder()` operates on raw pointers, pointer‑level faults
(e.g. from NA or mismatched length) occur before any `R`‑level error
handling. Wrapping calls in `try()` or `tryCatch()` will *not* prevent
`R`-session crashes.

To guard against this, wrap `preorder()` in a “safe” validator that
checks for NA values and matching length, for example:

<div class="sourceCode r">

    safe_preorder <- function(x, y, ...) {
      stopifnot(
        !anyNA(x), !anyNA(y),
        length(x) == length(y)
      )
      preorder(x, y, ...)
    }

</div>

### Usage

``` R
## S3 method for class 'matrix'
preorder(x, decreasing = FALSE, ...)
```

### Arguments

|              |                                     |
|--------------|-------------------------------------|
| `x`          | A \<matrix\> to be sorted           |
| `decreasing` | A \<logical\>                       |
| `...`        | Arguments passed into other methods |

### Value

A \<matrix\> of same dimensions as the input \<matrix\>

### See Also

Other Utilities: `presort()`

</div>

</div>
