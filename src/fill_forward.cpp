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
  
  for (int i = 0; i < column_names.size(); i++) { // iterate through columns to fill
    String col_name = column_names[i]; // get the name of the column to fill
    SEXP column = df[col_name]; // find that column in the df
    
    if (Rf_isNumeric(column) || Rf_isFactor(column)) { // if column is numeric or factor
      IntegerVector col = as<IntegerVector>(column); // cast column as integer vector
      int last_valid = (Rf_isLogical(column)) ? NA_LOGICAL : // if column is logical, last_valid = NA_LOGICAL
        (Rf_isNumeric(column)) ? NA_REAL : NA_INTEGER; // if column is NOT logical, if column is numeric last_valid = NA_REAL, if not numeric last_valid = NA_INTEGER (this is for factors)
      for (int j = 0; j < rows; j++) { // iterate through rows in column
        if (ISNA(col[j])) { // if row is NA, fill with last valid value
          col[j] = last_valid;
        }
        else { // otherwise update last valid value
          last_valid = col[j]; 
        }
      }
      df[col_name] = col; // set column in df equal to updated column
    } 
    else if (Rf_isLogical(column)) { // check if column is logical
      LogicalVector col = as<LogicalVector>(column); // cast as logical vector
      int last_valid = NA_LOGICAL; // init last valid value to NA
      for (int j = 0; j < rows; j++) { // iterate through rows in column
        if (LogicalVector::is_na(col[j])) { // // if value is NA
          col[j] = last_valid; // replace NA with last valid value
        }
        else {
          last_valid = col[j]; // otherwise, update last_valid value
        }
      }
      df[col_name] = col; // assign modified column to old columns location in df
    }
    else if (Rf_isString(column)) { // if column is string 
      CharacterVector col = as<CharacterVector>(column); // cast as char vector
      String last_valid = NA_STRING; // set last_valid = NA
      for (int j = 0; j < rows; j++) { // iterate through columns
        if (CharacterVector::is_na(col[j])) { // check if NA
          col[j] = last_valid; // set row to last_valid
        }
        else { // otherwise update last_valid
          last_valid = col[j];
        }
      }
      df[col_name] = col; // assign modified column to old columns loc in df
    }
  }
  return df;
}