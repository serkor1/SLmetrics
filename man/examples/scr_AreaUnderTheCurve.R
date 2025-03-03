## 1) Ordered x and y pair
x <- seq(0, pi, length.out = 200)
y <- sin(x)

## 1.1) calculate area
ordered_auc <- auc(y = y,  x = x)

## 2) Unordered x and y pair
x <- sample(seq(0, pi, length.out = 200))
y <- sin(x)

## 2.1) calculate area
unordered_auc <- auc(y = y,  x = x)

## 2.2) calculate area with explicit
## ordering
unordered_auc_flag <- auc(
  y = y,
  x = x,
  presorted = FALSE
)

## 3) display result
cat(
  "AUC (ordered x and y pair)", ordered_auc,
  "AUC (unordered x and y pair)", unordered_auc,
  "AUC (unordered x and y pair, with unordered flag)", unordered_auc_flag,
  sep = "\n"
)