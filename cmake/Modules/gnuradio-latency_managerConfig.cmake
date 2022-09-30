find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_LATENCY_MANAGER gnuradio-latency_manager)

FIND_PATH(
    GR_LATENCY_MANAGER_INCLUDE_DIRS
    NAMES gnuradio/latency_manager/api.h
    HINTS $ENV{LATENCY_MANAGER_DIR}/include
        ${PC_LATENCY_MANAGER_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_LATENCY_MANAGER_LIBRARIES
    NAMES gnuradio-latency_manager
    HINTS $ENV{LATENCY_MANAGER_DIR}/lib
        ${PC_LATENCY_MANAGER_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-latency_managerTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_LATENCY_MANAGER DEFAULT_MSG GR_LATENCY_MANAGER_LIBRARIES GR_LATENCY_MANAGER_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_LATENCY_MANAGER_LIBRARIES GR_LATENCY_MANAGER_INCLUDE_DIRS)
