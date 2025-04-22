<div class="container">

<div role="main">

|                |                 |
|----------------|----------------:|
| presort.matrix | R Documentation |

## Presort Matrices

### Description

A generic S3 function for somehting long. This function dispatches to S3
methods in `presort()` and performs no input validation. If you supply
NA values or vectors of unequal length (e.g. `length(x) != length(y)`),
the underlying `C++` code may trigger undefined behavior and crash your
`R` session.

#### Defensive measures

Because `presort()` operates on raw pointers, pointer‑level faults (e.g.
from NA or mismatched length) occur before any `R`‑level error handling.
Wrapping calls in `try()` or `tryCatch()` will *not* prevent `R`-session
crashes.

To guard against this, wrap `presort()` in a “safe” validator that
checks for NA values and matching length, for example:


{% code overflow="wrap" lineNumbers="true" %}

``` R

    safe_presort <- function(x, y, ...) {
      stopifnot(
        !anyNA(x), !anyNA(y),
        length(x) == length(y)
      )
      presort(x, y, ...)
    }

```
{% endcode %} 


### Usage

``` R
## S3 method for class 'matrix'
presort(x, decreasing = FALSE, ...)
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

Other Utilities: `preorder()`

```
{% endcode %} 


```
{% endcode %} 

