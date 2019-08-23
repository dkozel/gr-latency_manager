/* -*- c++ -*- */

#define EXAMPLE_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "example_swig_doc.i"

%{
#include "example/basis_change.h"
%}

%include "example/basis_change.h"
GR_SWIG_BLOCK_MAGIC2(example, basis_change);
