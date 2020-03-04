


cmake_minimum_required(VERSION 3.8)
project(xeus-clasp)

set(XEUS_CLASP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Versioning
# ==========

file(STRINGS "${XEUS_CLASP_INCLUDE_DIR}/xeus-clasp/xeus_clasp_config.hpp" xclasp_version_defines
  REGEX "#define XCLASP_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xclasp_version_defines})
  if (ver MATCHES "#define XCLASP_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
    set(XCLASP_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
  endif()
endforeach()
set(${PROJECT_NAME}_VERSION
  ${XCLASP_VERSION_MAJOR}.${XCLASP_VERSION_MINOR}.${XCLASP_VERSION_PATCH})
message(STATUS "Building xeus-clasp v${${PROJECT_NAME}_VERSION}")

# Configuration
# =============

include(GNUInstallDirs)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels/xclasp/kernel.json.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels/xclasp/kernel.json"
  )

################
# Dependencies #
################

set(xeus_REQUIRED_VERSION 0.23.3)
set(cppzmq_REQUIRED_VERSION 4.3.0)
# TODO
#set(pybind11_REQUIRED_VERSION 2.2.4) TODO: cl-bind
 
find_package(xeus ${xeus_REQUIRED_VERSION} REQUIRED)
find_package(cppzmq ${cppzmq_REQUIRED_VERSION} REQUIRED)
# TODO
#find_package(pybind11 ${pybind_11_REQUIRED_VERSION} REQUIRED)

#########
# flags #
#########

include(CheckCXXCompilerFlag)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251 /wd4141")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4018 /wd4267 /wd4715 /wd4146 /wd4129")
endif()

OPTION(DISABLE_ARCH_NATIVE "disable -march=native flag" OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter -Wextra -Wreorder")
    if (DISABLE_ARCH_NATIVE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=generic")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()

    CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)

    if (HAS_CPP14_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        message(FATAL_ERROR "Unsupported compiler -- xeus requires C++14 support!")
    endif()
endif()
  
###################
# Target and link #
###################

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib; ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

set(XEUS_CLASP_SRC
  #src/xcomm.cpp
  #src/xcomm.hpp
  src/xdebugger.cpp
  src/xdebugger.hpp
  # TODO
  #src/xdisplay.cpp
  #src/xdisplay.hpp
  #src.xinput.cpp
  #src/xinput.hpp
  #src/xinspect.cpp
  #src/xinspect.hpp
  src/xinterpreter.cpp
  #src/xis_complete.cpp
  #src/xis_complete.hpp
  #src/xptvsd_client.cpp
  #src/xptvsd_client.hpp
  #src/xpythonhome.cpp
  #src/xstream.cpp
  #src/xtream.hpp
  #src/xtraceback.cpp
  #src/xtraceback.hpp
  src/xutils.cpp
  src/xutils.hpp
  )

set(XEUS_CLASP_HEADERS
  include/xeus-clasp/xinterpreter.hpp
  include/xeus-clasp/xeus_clasp_config.hpp
  # TODO
  #include/xeus-python/xpythonhome.hpp
  )

# xeus-clasp is the target for the library
add_library(xeus-clasp SHARED ${XEUS_CLASP_SRC} ${XEUS_CLASP_HEADERS})

# xclasp is the target for the kernel executable
add_executable(xclasp src/main.cpp)
set_target_properties(xclasp PROPERTIES ENABLE_EXPORTS 1)
# TODO
#target_link_libraries(xclasp PRIVATE pybind11::pybind11 xeus-clasp)
target_link_libraries(xclasp PRIVATE xeus-clasp)

if (APPLE)
  set_target_properties(xclasp xeus-clasp PROPERTIES
    MACOSX_RPATH ON
    )
else()
  set_target_properties(xclasp xeus-clasp PROPERTIES
    BUILD_WITH_INSTALL_RPATH 1
    SKIP_BUILD_RPATH FLASE
    )
endif()

set_target_properties(xclasp xeus-clasp PROPERTIES
  INSTALL_RPATH_USE_LINK_PATH TRUE
)

target_include_directories(xeus-clasp
  PUBLIC
  # TODO
  #${PYTHON_INCLUDE_DIRS}
  $<BUILD_INTERFACE:${XEUS_CLASP_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>)

# TODO
#target_link_libraries(xeus-clasp PUBLIC pybind11::embed xeus)
target_link_libraries(xeus-clasp PUBLIC xeus)

set_target_properties(xeus-clasp PROPERTIES
  PUBLIC_HEADER "${XEUS_CLASP_HEADERS}"
  PREFIX ""
  VERSION ${${PROJECT_NAME}_VERSION}
  SOVERSION ${XCLASP_VERSION_MAJOR}
  OUTPUT_NAME "libxeus-clasp")

# TODO
#target_compile_definitions(xeus-clasp PUBLIC "XEUS_CLASP_EXPORTS" XEUS_PYTHONHOME="${PYTHON_PREFIX}")
target_compile_definitions(xeus-clasp PUBLIC "XEUS_CLASP_EXPORTS")

#########
# Tests #
#########

OPTION(BUILD_TESTS "xeus-clasp test suite" OFF)
OPTION(DOWNLOAD_GTEST "build gtest from downloaded sources" OFF)

if(DOWNLOAD_GTEST OR GTEST_SRC_DIR)
  set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
  add_subdirectory(test)
endif()

################
# Installation #
################

include(CMakePackageConfigHelpers)

set(XEUS_CLASP_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install apth for xeus-claspConfig.cmake")

# Install xeus-clasp and xclasp
install(TARGETS xeus-clasp
  EXPORT ${PROJECT_NAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xeus-clasp)
install(TARGETS xclasp
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Configuration and data directories for jupyter and xeus-python
set(XJUPYTER_DATA_DIR "share/jupyter" CACHE STRING "Jupyter data directory")

# Install Jupyter kernelspecs
set(XCLASP_KERNELSPEC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/share/jupyter/kernels)
install(DIRECTORY ${XCLASP_KERNELSPEC_DIR}
  DESTINATION ${XJUPYTER_DATA_DIR}
  PATTERN "*.in" EXCLUDE)

# Extra path for installing Jupyter kernelspec
if (XEXTRA_JUPYTER_DATA_DIR)
  install(DIRECTORY ${XCLASP_KERNELSPEC_DIR}
    ESTINATION ${XEXTRA_JUPYTER_DATA_DIR}
    PATTERN "*.in" EXCLUDE)
endif(XEXTRA_JUPYTER_DATA_DIR)

# MAkes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

# Configure 'xeus-claspConfig.cmake' for a build tree
set(XEUS_CLASP_CONFIG_CODE "####### Expanded from \@XEUS_CLASP_CONFIG_CODE\@ #######\n")
set(XEUS_CLASP_CONFIG_CODE "${XEUS_CLASP_CONFIG_CODE}set(CMAKE_MODULE_PATH \"${CMAKE_CURRENT_SOURCE_DIR}/cmake;\${CMAKE_MODULE_PATH}\")\n")
set(XEUS_CLASP_CONFIG_CODE "${XEUS_CLASP_CONFIG_CODE}##################################################")
configure_package_config_file(${PROJECT_NAME}Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${PROJECT_BINARY_DIR})

# Configure 'xeus-claspConfig.cmake' for an install tree
set(XEUS_CLASP_CONFIG_CODE "")
configure_package_config_file(${PROJECT_NAME}Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION ${XEUS_CLASP_CMAKECONFIG_INSTALL_DIR})

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${XEUS_CLASP_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}Targets.cmake
  DESTINATION ${XEUS_CLASP_CMAKECONFIG_INSTALL_DIR})
