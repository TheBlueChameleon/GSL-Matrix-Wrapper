/* TODO: File descrption
 * 
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

// ========================================================================== //
// dependencies

// STL

#include <complex>
#include <vector>
#include <string>

#include <functional>


// libgsl
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>


// own
#include "gslWrapper.hpp"

// ========================================================================== //
// type alias

typedef std::complex<double> complex_d_t;

// ========================================================================== //
// class

class Matrix {
  
private:
  // ........................................................................ //
  // data features
  
  gsl_matrix_complex * data = nullptr;
  gsl_matrix_complex * LU   = nullptr;
  
  // ........................................................................ //
  // to_string features
  
  int         precision = 2;        // number of decimal places
  std::string separator = "  ";     // output between two matrix elements
  bool        brackets  = true;     // do or do not draw brackets around matrix representation
  
public:
  // ------------------------------------------------------------------------ //
  // CTor, DTor
  
  Matrix() = delete;
  Matrix(const int rows, const int cols);                                       // creates a NULL matrix
  Matrix(const int rows, const int cols, complex_d_t z);                        // creates a matrix where each cell holds value z
  Matrix(const std::vector<complex_d_t> & source, int rows = -1, int cols = -1);
    /* On the default arguments:
     * value of (rows, cols)      returned matrix
     *  (-1, -1)                    column vector of shape (source.size(), 1)
     *  (-1,  1)                    dito
     *  ( 1, -1)                    row vector of shape (1, source.size())
     *  other negative values       throws an exception
     *    of r, c
     *  ( r,  c)                    matrix of shape (r, c), if possible with data from source.
     *                                Assumes source is given in row-major, i.e. [a, b, c, d] ~> [[a, b], [c, d]]
     *                                Throws an invalid argument exception otherwise
     *  ( r, -1)                    matrix of shape (r, source.size() / r), if possible with data from source.
     *                                Otherwise same behaviour as above.
     *  (-1,  c)                    matrix of shape (source.size() / c, c), if possible with data from source.
     *                                Otherwise same behaviour as above.
     */
  
  Matrix(const Matrix&  source);              // copy CTor
  Matrix(      Matrix&& source) = default;    // move CTor
  
  ~Matrix();
  
  // ----------------------------------------------------------------------- //
  // getters/setters
  // ....................................................................... //
  // data features
  
  int getRows() const;
  int getCols() const;
  
  gsl_matrix_complex const *                getData() const;
  void                                      setData(gsl_matrix_complex * data);
  
  complex_d_t & matrixEl(const int row, const int col) const;                   // permits read/write access with boundary check
  
  std::vector<complex_d_t> getRow(const int row) const;                         // constructs a copy of the relevant data in a new memory location
  std::vector<complex_d_t> getCol(const int col) const;                         // constructs a copy of the relevant data in a new memory location
  
  // ....................................................................... //
  // to_string features
  
  int         getPrecision() const;
  void        setPrecision(int         val);
  
  std::string getSeparator() const;
  void        setSeparator(const std::string & val);
  
  bool        getBrackets () const;
  void        setBrackets (bool        val);
};

#endif
