/* -*- c++ -*- */

#define EXAMPLE_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "example_swig_doc.i"

%{
#include "example/basis_change.h"
#include "example/tag_to_msg.h"
#include "example/latency_manager.h"
%}

%include "example/basis_change.h"
GR_SWIG_BLOCK_MAGIC2(example, basis_change);
%include "example/tag_to_msg.h"
GR_SWIG_BLOCK_MAGIC2(example, tag_to_msg);
%include "example/latency_manager.h"
GR_SWIG_BLOCK_MAGIC2(example, latency_manager);
