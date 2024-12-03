library(Rcpp)
library(tidyr)
library(tidyverse)

cppFunction('NumericVector full_seq_rcpp(NumericVector x, double step) {
    if (step <= 0) {
        stop("Step size must be positive.");
    }
    
    // Sort the input vector
    std::sort(x.begin(), x.end());
    
    // Get the range of the sequence
    double min_val = x[0];
    double max_val = x[x.size() - 1];
    
    // Calculate the size of the result
    int n = static_cast<int>((max_val - min_val) / step) + 1;
    NumericVector result(n);
    
    // Fill the result vector
    for (int i = 0; i < n; ++i) {
        result[i] = min_val + i * step;
    }
    
    return result;
}')

x <- c(4, 3, 1)
step <- 1
full_seq_rcpp(x, step)

bench::mark(full_seq(x, step))
bench::mark(full_seq_rcpp(x, step))

x <- sample(1:100, size = 15, replace = TRUE)
step <- 1

assertthat::are_equal(full_seq(x, step), full_seq_rcpp(x, step))

# Benchmark
microbenchmark(
  rcpp = full_seq_rcpp(x, step),
  tidyr = full_seq(x, step),
  times = 10
)
