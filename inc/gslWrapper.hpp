/* TODO: File descrption
 * 
 */

#ifndef GSLWRAPPER_HPP
#define GSLWRAPPER_HPP

// ========================================================================== //
// dependencies

// STL
#include <iostream>


// libgsl
#include <gsl/gsl_complex.h>
#include <gsl/gsl_errno.h>


// own


// ========================================================================== //
// globals

extern bool gslWrapper_initialized;

extern gsl_error_handler_t * gsl_error_handler_default;
extern gsl_error_handler_t * gsl_error_handler_current;
extern gsl_error_handler_t * gsl_error_handler_last   ;

// ========================================================================== //
// init

void gslWrapper_init();

// ========================================================================== //
// error handlers

// -------------------------------------------------------------------------- //
// getters, setters

gsl_error_handler_t * gslWrapper_get_error_handler();
void                  gslWrapper_set_error_handler(gsl_error_handler_t handler);
void                  gslWrapper_set_default_error_handler();
void                  gslWrapper_set_last_error_handler();

// -------------------------------------------------------------------------- //
// handlers

void gsl_errorHandler_skip (const char * reason,
              const char * file,
              int line,
              int gsl_errno
);

void gsl_errorHandler_throw (const char * reason,
              const char * file,
              int line,
              int gsl_errno
);

// ========================================================================== //
// conversion funcs

// -------------------------------------------------------------------------- //
// to string

std::string gsl_complex_to_string(gsl_complex z);

// -------------------------------------------------------------------------- //
// generic


#endif
 
