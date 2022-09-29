# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT latency_manager_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT latency_manager_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND latency_manager_python_files
    latency_manager_python.cc
    tag_to_msg_python.cc
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(latency_manager
   ../../..
   gr::latency_manager
   "${latency_manager_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET latency_manager_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:latency_manager_python>
    ${CMAKE_BINARY_DIR}/test_modules/gnuradio/latency_manager/
)

install(TARGETS latency_manager_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/latency_manager COMPONENT pythonapi)
