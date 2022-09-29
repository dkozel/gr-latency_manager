find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_ANALOG gnuradio-analog)

FIND_PATH(
    GR_ANALOG_INCLUDE_DIRS
    NAMES gnuradio/analog/api.h
    HINTS $ENV{ANALOG_DIR}/include
        ${PC_ANALOG_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_ANALOG_LIBRARIES
    NAMES gnuradio-analog
    HINTS $ENV{ANALOG_DIR}/lib
        ${PC_ANALOG_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-analogTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_ANALOG DEFAULT_MSG GR_ANALOG_LIBRARIES GR_ANALOG_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_ANALOG_LIBRARIES GR_ANALOG_INCLUDE_DIRS)
