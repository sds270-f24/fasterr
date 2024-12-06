test_that("rcpp full seq gives the same output as tidyr full seq on a small sequence", {
  seq <- c(1, 3, 8)
  step <- 1
  expect_equal(tidyr::full_seq(seq, step), fasterr:::full_seq(seq, step))
})

test_that("rcpp full seq gives the same output as tidyr full seq on a second small sequence", {
  seq <- c(1, 5, 7, 9, 17)
  step <- 2
  expect_equal(tidyr::full_seq(seq, step), fasterr:::full_seq(seq, step))
})

test_that("rcpp full seq gives the same output as tidyr full seq on a large sequence", {
  seq <- sample(1:1000, size = 500, replace = TRUE)
  step <- 1
  expect_equal(tidyr::full_seq(seq, step), fasterr:::full_seq(seq, step))
})

test_that("rcpp full seq gives an error if the step size is negative", {
  seq <- c(1, 5, 7, 9, 17)
  step <- -2
  expect_error(fasterr:::full_seq(seq, step), "must be positive")
})

test_that("rcpp full seq gives an error if the inputted sequence is not regular", {
  seq <- c(0, 3, 11)
  step <- 3
  expect_error(fasterr:::full_seq(seq, step), "regular sequence")
})

test_that("skipping benchmark tests", {
  skip('skip')
  seq <- sample(1:1000, size = 500, replace = TRUE)
  step <- 1
  bench::mark(
    tidyr::full_seq(seq, step),
    fasterr:::full_seq(seq, step)
  )
  system.time(replicate(1000, tidyr::full_seq(seq, step)))
  system.time(replicate(1000, fasterr:::full_seq(seq, step)))
})