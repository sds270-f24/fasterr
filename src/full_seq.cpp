#include <Rcpp.h>
using namespace Rcpp;

/**
 *  Takes in an incomplete sequence and a step size and fills in the rest of the sequence based on the step size
 *  Mimics functionality of tidyr::full_seq
 * 
 * @param x NumericVector normal sequence to be filled
 * @param step double step between items in the sequence
 * @return NumericVector filled sequence
 */
// [[Rcpp::export]]
NumericVector full_seq(NumericVector x, double step) {
  if (step <= 0) {
    stop("Step size must be positive.");
  }
  
  // sort input
  std::sort(x.begin(), x.end());
  
  // get max and min
  double min_val = x[0];
  double max_val = x[x.size() - 1];
  
  //check if the sequence can be filled
  for (int i=0; i<x.size(); i++){
    if (std::fmod(x[i] - min_val, step) != 0) {
      stop("Inputted vector is not a regular sequence");
    }
  }
  
  // initialize vector with correct size
  int n = static_cast<int>((max_val - min_val) / step) + 1;
  NumericVector result(n);
  
  // fill vector
  for (int i = 0; i < n; ++i) {
    result[i] = min_val + i * step;
  }
  
  return result;
}