// ========================================================================= //
// dependencies

// STL
#include <stdexcept>

#include <iostream>
#include <sstream>
#include <iomanip>

#include <string>
  using namespace std::string_literals;
#include <vector>
#include <complex>
  using namespace std::complex_literals;

#include <functional>
#include <cmath>
#include <numeric>
  
// own
 #include "Matrix.hpp"

// ========================================================================= //
// local macro

#define THROWTEXT(msg) ("RUNTIME EXCEPTION IN "s + (__PRETTY_FUNCTION__) + "\n"s + msg)

#define MATRIXHEIGHT (this->data->size1)
#define MATRIXWIDTH  (this->data->size2)
  
#define INBOUNDS(row , col ) ( \
    (row >= 0) && (static_cast<size_t>(row) < MATRIXHEIGHT) && \
    (col >= 0) && (static_cast<size_t>(col) < MATRIXWIDTH )    \
)
#define      COORDINATESTRING(row , col ) ("(" + std::to_string(row)  + ", " + std::to_string(col) + ")")
#define       DIMENSIONSTRING(rows, cols) (      std::to_string(rows) + "x"  + std::to_string(cols)     )
#define MATRIXDIMENSIONSTRING DIMENSIONSTRING(MATRIXHEIGHT, MATRIXWIDTH) 

#define MATRIXEL(row, col) (*reinterpret_cast<complex_d_t *>(gsl_matrix_complex_ptr(this->data, row, col)))

// ========================================================================= //
// CTor, DTor

Matrix::Matrix(const int rows, const int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(THROWTEXT(
      "    Only nonzero, positive arguments can be used as Matrix dimensions\n"
      "    Attempted to create matrix of dimension " + std::to_string(rows) + "x" + std::to_string(cols) + "\n"
    ));
  }
  
  data = gsl_matrix_complex_calloc(rows, cols);
}


Matrix::~Matrix() {
  gsl_matrix_complex_free(data);
  if (LU) {gsl_matrix_complex_free(LU);}
}


// ========================================================================= //
// getters/setters

int Matrix::getRows() const {return this->data->size1;}
// ......................................................................... //
int Matrix::getCols() const {return this->data->size2;}
// ------------------------------------------------------------------------- //
gsl_matrix_complex const * Matrix::getData() const {return this->data;}
// // ......................................................................... //
void                       Matrix::setData(gsl_matrix_complex * data) {
  gsl_matrix_complex_free(this->data);
  this->data = data;
  
  if (LU) {
    gsl_matrix_complex_free(LU);
    LU   = nullptr;
  }
}
// ------------------------------------------------------------------------- //
complex_d_t & Matrix::matrixEl(const int row, const int col) const {
  if (!INBOUNDS(row, col)) {
    throw std::out_of_range(THROWTEXT(
      "    Invalid row/column ID\n"
      "    Matrix is of dimension " + MATRIXDIMENSIONSTRING + "\n"
      "    but referenced cell ID was " + COORDINATESTRING(row, col) + "\n"
    ));
  }
  
  return MATRIXEL(row, col);
}
// ------------------------------------------------------------------------- //
std::vector<complex_d_t> Matrix::getRow(const int row) const {
  if (!INBOUNDS(row, 0)) {
    throw std::out_of_range(THROWTEXT(
      "    Invalid row/column ID\n"
      "    Matrix is of dimension " + MATRIXDIMENSIONSTRING + "\n"
      "    but referenced row ID was " + std::to_string(row) + "\n"
    ));
  }
  
  auto view_start = reinterpret_cast<complex_d_t *>(gsl_matrix_complex_ptr(this->data, row, 0)),
       view_end   = view_start + MATRIXWIDTH;
  return std::vector<complex_d_t> (view_start, view_end);
}
// ......................................................................... //
std::vector<complex_d_t> Matrix::getCol(const int col) const {
  if (!INBOUNDS(0, col)) {
    throw std::out_of_range(THROWTEXT(
      "    Invalid column ID\n"
      "    Matrix is of dimension " + MATRIXDIMENSIONSTRING + "\n"
      "    but referenced column ID was " + std::to_string(col) + "\n"
    ));
  }
     
  // no STL copy with stride available -- do manually
  std::vector<complex_d_t> reVal = std::vector<complex_d_t>(MATRIXHEIGHT);
  
  for (auto i=0u; i<MATRIXHEIGHT; ++i) {
    reVal[i] = MATRIXEL(i, col);
  }
  
  return reVal;
}
// // ------------------------------------------------------------------------- //
// int         Matrix::getPrecision() const {return precision;}
// void        Matrix::setPrecision(int val) {
//   if (val < 0) {throw std::invalid_argument("precision needs to be non-negative!");}
//   else         {precision = val;}
// }
// // ......................................................................... //
// std::string Matrix::getSeparator() const {return separator;}
// void        Matrix::setSeparator(const std::string & val) {separator = val;}
// // ......................................................................... //
// bool        Matrix::getBrackets () const {return brackets;}
// void        Matrix::setBrackets (bool val) {brackets = val;}
