
<!-- README.md is generated from README.Rmd. Please edit that file -->

# fasterr <img src='data-raw/fasterr.png' align="right" height="139"/>

<!-- badges: start -->

[![R-CMD-check](https://github.com/sds270-f24/fasterr/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/sds270-f24/fasterr/actions/workflows/R-CMD-check.yaml)
![Lifecycle:
Stable](https://img.shields.io/badge/lifecycle-stable-brightgreen)
![CRAN
Status](https://img.shields.io/badge/cran-not%20yet%20accepted-lightgrey)

<!-- badges: end -->

## Summary

This package optimizes three commonly used R functions by rewriting them
in C++ for better performance using `Rcpp`. The C++ implementations are
faster, especially when working with large datasets or vectors, while
keeping the functionality consistent with the original R functions. This
package is designed to make workflows faster without changing the
functionality of functions.

## Installation

The current version of `fasterr` can be installed by:

``` r
remotes::install_github("sds270-f24/fasterr")
```

You can load this package by:

``` r
library(fasterr)
```

## Original Functions

-   [`tidyr::full_seq()`](https://tidyr.tidyverse.org/reference/full_seq.html)
    -   what does this do?
-   [`tidyr::fill()`](https://tidyr.tidyverse.org/reference/fill.html)
    -   This function cleans an inputted `data.frame` by filling `NA`
        values. It takes in a direction as input, with the default being
        “down.” Our `fasterr` version does not take in a direction,
        using the default, meaning `NA` values are filled with the last
        valid non `NA` value as you move down the `data.frame`.
-   [`stats::na.omit()`](https://www.rdocumentation.org/packages/data.table/versions/1.16.2/topics/na.omit.data.table)
    -   This function cleans an inputted `data.frame`, removing rows
        with `NA` values. The function stores information about which
        rows have been removed in an attribute of the cleaned
        `data.frame`.

## Optimized Functions

Example usage and time demonstrations.The times are measured in
microseconds.

### full_seq()

``` r
seq <- c(1, 5, 7, 9, 17)
step <- 2
    
full_seq_results <- microbenchmark::microbenchmark(
    tidyr_full_seq = tidyr::full_seq(seq, step),
    fasterr_full_seq = fasterr:::full_seq(seq, step),
    times = 100
  )

summary(full_seq_results)
#>               expr    min      lq       mean median      uq        max neval
#> 1   tidyr_full_seq 30.865 31.8840 4926.25004 32.713 33.2025 489230.075   100
#> 2 fasterr_full_seq  2.353  2.6675    8.97584  3.746  4.0060    543.471   100
ggplot2::autoplot(full_seq_results)
```

<img src="man/figures/README-full-seq-1.png" width="100%" />

### fill_forward()

``` r
fill_results <- microbenchmark::microbenchmark(
    tidyr_fill = tidyr::fill(airquality, "Ozone", "Solar.R"),
    fasterr_fill_forward = fasterr:::fill_forward(airquality,c("Ozone", "Solar.R")),
    times = 100
  )

summary(fill_results)
#>                   expr      min       lq       mean    median       uq
#> 1           tidyr_fill 6299.547 6521.974 8119.05797 6904.6345 8829.179
#> 2 fasterr_fill_forward    6.412    7.654   17.22815   13.2055   19.206
#>         max neval
#> 1 30753.347   100
#> 2   286.735   100
ggplot2::autoplot(fill_results)
```

<img src="man/figures/README-fill_forward-1.png" width="100%" />

### omit_na()

``` r
omit_na_results <- microbenchmark::microbenchmark(
    stats_na.omit = stats::na.omit(airquality),
    fasterr_omit_na = omit_na(airquality),
    times = 100
  )

summary(omit_na_results)
#>              expr     min       lq     mean   median       uq     max neval
#> 1   stats_na.omit 134.890 147.8000 153.2393 150.7025 153.9625 220.966   100
#> 2 fasterr_omit_na  86.229  94.8345 100.9101  97.6380 100.5295 254.960   100
ggplot2::autoplot(omit_na_results)
```

<img src="man/figures/README-omit_na-1.png" width="100%" />

## Contributors

-   [Emma Ruckle](https://github.com/emruckle)
-   [Molly Daniel](https://github.com/mollyd13)
