test_that("remove NA with small sample df", {
  df <- data.frame(
    numeric_col = c(1.1, 2.2, NA, 4.4),
    integer_col = c(1L, NA, 3L, 4L),
    char_col = c("a", "b", NA, "d"),
    stringsAsFactors = FALSE
  )
  expect_equal(na.omit(df), omit_na(df))
})

test_that("remove NA with large df", {
  expect_equal(na.omit(airquality), omit_na(airquality))
})

test_that("remove NA with no NA in df", {
  expect_equal(na.omit(mtcars), omit_na(mtcars))
})

test_that("skipping benchmark tests", {
  skip('skip')
  bench::mark(
    na.omit(mtcars),
    omit_na(mtcars)
  )
  bench::mark(
    na.omit(airquality),
    omit_na(airquality)
  )
  system.time( replicate(10000, na.omit(airquality)))
  system.time( replicate(10000, omit_na(airquality)))
})