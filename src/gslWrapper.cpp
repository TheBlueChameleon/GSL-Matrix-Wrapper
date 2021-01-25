// ========================================================================== //
// dependencies

// STL
#include <stdexcept>

#include <iostream>

#include <complex>
#include <string>


// libgsl
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_errno.h>


// own
#include "gslWrapper.hpp"

// ========================================================================== //
// local definitions

typedef std::complex<double> complex_t;

// ========================================================================== //
// globals

bool                  gslWrapper_initialized    = false;
gsl_error_handler_t * gsl_error_handler_default = nullptr;
gsl_error_handler_t * gsl_error_handler_current = nullptr;
gsl_error_handler_t * gsl_error_handler_last    = nullptr;

// auto old_handler = gsl_set_error_handler (unitTest_GSL_errorHandler_UT);

// ========================================================================== //
// init

void gslWrapper_init() {
  if (gslWrapper_initialized) {throw std::runtime_error("gslWrapper had already been initialized!");}
  
  gsl_error_handler_default = gsl_set_error_handler(gsl_errorHandler_throw);
  gsl_error_handler_current =                       gsl_errorHandler_throw ;
  gsl_error_handler_last    =                       gsl_errorHandler_throw ;
  
  gslWrapper_initialized = true;
}

// ========================================================================== //
// error handlers

// -------------------------------------------------------------------------- //
// getters, setters

gsl_error_handler_t * gslWrapper_get_error_handler() {
  if (!gslWrapper_initialized) {throw std::runtime_error("gslWrapper not initialized!");}
  return gsl_error_handler_current;
}
// .......................................................................... //
void gslWrapper_set_error_handler(gsl_error_handler_t handler) {
  if (!gslWrapper_initialized) {throw std::runtime_error("gslWrapper not initialized!");}
  gsl_error_handler_last    = gsl_set_error_handler(handler);
  gsl_error_handler_current = handler;
}
// .......................................................................... //
void gslWrapper_set_default_error_handler() {
  if (!gslWrapper_initialized) {throw std::runtime_error("gslWrapper not initialized!");}
  gslWrapper_set_error_handler(gsl_error_handler_default);
}
// .......................................................................... //
void gslWrapper_set_last_error_handler() {
  if (!gslWrapper_initialized) {throw std::runtime_error("gslWrapper not initialized!");}
  gslWrapper_set_error_handler(gsl_error_handler_last);
}

// -------------------------------------------------------------------------- //
// handlers

void gsl_errorHandler_skip (const char * reason,
              const char * file,
              int line,
              int gsl_errno
) {
  std::cout << "custom handler called" << std::endl;
  std::cout << "\treason      : " << reason << std::endl;
  std::cout << "\tfile        : " << file << std::endl;
  std::cout << "\tline        : " << line << std::endl;
  std::cout << "\terror number: " << gsl_errno << std::endl;
}
// .......................................................................... //
void gsl_errorHandler_throw (                  const char * reason,
                                               const char * file,
                              [[maybe_unused]] int          line,
                                               int          gsl_errno
) {
  std::string msg = "GSL SUBSYSTEM ERROR\n";
  msg += "\tthrow reason:"; msg += reason; msg += "\n";
  msg += "\toccured in file;"; msg += file; msg += "\n";
  msg += "\terror code:"; msg += std::to_string(gsl_errno); msg += "\n";
  
  std::cout << msg << std::endl;
}

// ========================================================================== //
// conversion funcs

// -------------------------------------------------------------------------- //
// to string

std::string gsl_complex_to_string(gsl_complex z) {
  std::string reVal = "(";
  
  reVal += std::to_string(z.dat[0]);
  reVal += ", ";
  reVal += std::to_string(z.dat[1]);
  reVal += ")";
  
  return reVal;
}
// .......................................................................... //


// -------------------------------------------------------------------------- //
// generic
