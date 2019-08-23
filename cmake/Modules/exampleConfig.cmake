INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_EXAMPLE example)

FIND_PATH(
    EXAMPLE_INCLUDE_DIRS
    NAMES example/api.h
    HINTS $ENV{EXAMPLE_DIR}/include
        ${PC_EXAMPLE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    EXAMPLE_LIBRARIES
    NAMES gnuradio-example
    HINTS $ENV{EXAMPLE_DIR}/lib
        ${PC_EXAMPLE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/exampleTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EXAMPLE DEFAULT_MSG EXAMPLE_LIBRARIES EXAMPLE_INCLUDE_DIRS)
MARK_AS_ADVANCED(EXAMPLE_LIBRARIES EXAMPLE_INCLUDE_DIRS)
