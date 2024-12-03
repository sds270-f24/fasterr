#include <Rcpp.h>
using namespace Rcpp;

/**
 *  Iterates over a DataFrame, identifying rows with NA values
 * 
 * @param df DataFrame to be cleaned
 * @return DataFrame Cleaned DataFrame with NA rows removed
 */
// [[Rcpp::export]]
LogicalVector index_rows_na(DataFrame df) {
  int rows = df.nrows(); // number of rows in df
  int cols = df.size(); // number of cols in df
  
  LogicalVector keep_row(rows, true); // initialize all rows to TRUE
  
  for (int i = 0; i < cols; i++) { // loop through each column
    SEXP current_col = df[i]; // get the current column as an SEXP (generic type)
    // Check if column is numeric
    if (Rf_isNumeric(current_col)) {
      NumericVector col = as<NumericVector>(current_col);
      for (int j = 0; j < rows; j++) {
        if (std::isnan(col[j])) {
          keep_row[j] = false; // set row to FALSE if NA found
        }
      }
    }
    else if (Rf_isString(current_col)) {
      CharacterVector col = as<CharacterVector>(current_col);
      for (int j = 0; j < rows; j++) {
        if (CharacterVector::is_na(col[j])) {
          keep_row[j] = false; // set row to FALSE if NA found
        }
      }
    }
  }
  return keep_row; // return LogicalVector of TRUE, FALSE values for each row
}