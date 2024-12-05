test_that("fill NA with small sample df", {
  df <- data.frame(
    num_col = c(1, NA, 3, NA, 5),              # Numeric column with NAs
    char_col = c("A", NA, "C", NA, "E"),       # Character column with NAs
    log_col = c(TRUE, NA, FALSE, NA, TRUE),    # Logical column with NAs
    factor_col = factor(c("low", NA, "high", NA, "medium")),  # Factor column with NAs
    stringsAsFactors = FALSE
  )
  expect_equal(tidyr::fill(df, "num_col", "char_col", "log_col", "factor_col"), fill_forward(df, c("num_col", "char_col", "log_col", "factor_col")))
})

test_that("fill NA with large df", {
  expect_equal(tidyr::fill(airquality, "Ozone", "Solar.R"), fill_forward(airquality,c("Ozone", "Solar.R")))
})

test_that("fill NA with large df with no NA", {
  expect_equal(tidyr::fill(mtcars, "disp", "hp"), fill_forward(mtcars,c("disp", "hp")))
})

test_that("skipping benchmark tests", {
  skip('skip')
  bench::mark(
    tidyr::fill(airquality, "Ozone", "Solar.R"),
    fill_forward(airquality,c("Ozone", "Solar.R"))
  )
  system.time(replicate(1000, tidyr::fill(airquality, "Ozone", "Solar.R")))
  system.time(replicate(1000, fill_forward(airquality,c("Ozone", "Solar.R"))))
})