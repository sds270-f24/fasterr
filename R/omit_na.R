#' Removes rows with `NA` from a `data.frame`
#'
#' @param df A `data.frame`.
#' @return Cleaned `data.frame` with rows that contained `NA` removed
#' @details Removes rows with `NA` values from inputted `data.frame` and returns cleaned `data.frame`. Stores information about omitted rows in `na.action` attribute. Mimics the functionality of `na.omit()`, with a faster run time. This is useful for large data sets, or within functions that need to remove rows with `NA` values as a sub-step. 
#' @author Emma Ruckle
#' @examples
#' omit_na(airquality)
#' omit_na(mtcars)
#' 
#' @seealso [stats::na.omit()]
#' @useDynLib fasterr, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export
omit_na <- function(df) {
  # calls c++ function to get the LogicalVector indicating which rows to keep
  keep_rows <- index_rows_na(df)
  # identify omitted rows (row indices where keep_rows is FALSE)
  omitted_indices <- which(!keep_rows)
  # add the na.action attribute to the cleaned_df
  if (length(omitted_indices) > 0) {
    attr(df, "na.action") <- structure(omitted_indices, class = "omit", names = as.character(omitted_indices))
  }
  df[keep_rows, ] # return the cleaned data frame
}