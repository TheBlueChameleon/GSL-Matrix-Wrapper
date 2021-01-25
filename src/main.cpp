/* TODO: File descrption
 * 
 */

// ========================================================================== //
// dependencies

// STL

// own
#include "gslWrapper.hpp"
#include "Matrix.hpp"

// ========================================================================== //
// proc

// -------------------------------------------------------------------------- //

// ========================================================================== //
// main

int main () {
  // The following lines describe invalid matrices and are blocked by the compiler or throw runtime exceptions.
  /*
  Matrix M;
  Matrix M(0,0);
  Matrix M(1,0);
  Matrix M(0,1);
  
  std::cout << M.matrixEl(-1,-1) << std::endl;
  */
  
  Matrix M(2, 2);
  
  std::cout << "Element (0, 0):" << std::endl;
  M.matrixEl(0, 0) = complex_d_t(-1, -1);
  std::cout << M.matrixEl(0, 0) << std::endl;
  std::cout << std::endl;
  
  
  for   (int r=0; r<2; r++) {
    for (int c=0; c<2; c++) {
      M.matrixEl(r, c) = std::complex<double>(r+1, c+1);
    }
  }
  
  
  std::cout << "Row 0:" << std::endl;
  for (auto & z : M.getRow(0)) {
    std::cout << z << "\t";
  }
  std::cout << std::endl;
  
  
  std::cout << "Col 0:" << std::endl;
  for (auto & z : M.getCol(0)) {
    std::cout << z << "\t";
  }
  std::cout << std::endl;
}
