#include <Rcpp.h>
using namespace Rcpp;

/**
 *  Iterates over columns in a DataFrame identifying NA values, and replacing the NA values with the last non NA value seen in the column
 *  Mimics functionality of tidyr::fill with default direction (down)
 * 
 * @param df DataFrame to be cleaned
 * @param column_names CharacterVector columns to be filled
 * @return DataFrame Cleaned DataFrame with NA rows is designated columns filled
 */
// [[Rcpp::export]]
DataFrame fill_forward(DataFrame df, CharacterVector column_names) {
  int rows = df.nrows(); // get number of rows in df
  
  for (int i = 0; i < column_names.size(); i++) { // iterate through columns in column names
    String col_name = column_names[i]; // get name of current column
    SEXP column = df[col_name]; // SEXP = generic R object
    
    if (Rf_isLogical(column)) { // if column is logical
      LogicalVector col = as<LogicalVector>(column); // cast column as logical vector
      int last_valid = NA_LOGICAL; // init last_valid to NA_LOGICAL (NA for logical type)
      for (int j = 0; j < rows; j++) { // iterate through rows in column
        if (LogicalVector::is_na(col[j])) { // if row is NA
          col[j] = last_valid; // fill with last_valid
        }
        else {
          last_valid = col[j]; // otherwise, update last valid
        }
      }
      df[col_name] = col; // put updated column in df
    }
    else if (Rf_isNumeric(column)) { // if column is numeric
      NumericVector col = as<NumericVector>(column); // cast column as numeric vector
      double last_valid = NA_REAL; // init last_valid to NA
      for (int j = 0; j < rows; j++) { // iterate through rows in column
        if (NumericVector::is_na(col[j])) { // if NA, update with last_valid
          col[j] = last_valid;
        }
        else {
          last_valid = col[j]; // otherwise, update last_valid
        }
      }
      df[col_name] = col;
    }
    else if (Rf_isFactor(column)) { // if column is factor
      IntegerVector col = as<IntegerVector>(column);
      int last_valid = NA_INTEGER;
      for (int j = 0; j < rows; j++) {
        if (col[j] == NA_INTEGER) {
          col[j] = last_valid;
        } else {
          last_valid = col[j];
        }
      }
      df[col_name] = col;
    }
    else if (Rf_isString(column)) { // if column is character
      CharacterVector col = as<CharacterVector>(column);
      String last_valid = NA_STRING;
      for (int j = 0; j < rows; j++) {
        if (CharacterVector::is_na(col[j])) {
          col[j] = last_valid;
        } else {
          last_valid = col[j];
        }
      }
      df[col_name] = col;
    }
  }
  return df; // return updated df
}