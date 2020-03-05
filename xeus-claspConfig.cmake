

# xeus-clasp cmake module
# This module sets the following variables in your project::
#
#   xeus-clasp_FOUND - true if xeus-clasp found on the system
#   xeus-clasp_INCLUDE_DIRS - the directory containing xeus-clasp headers
#   xeus-clasp_LIBRARY - the library for dynamic linking


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was xeus-claspConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../usr/local" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR};${CMAKE_MODULE_PATH}")



include(CMakeFindDependencyMacro)
find_dependency(xeus 0.23.3)
find_dependency(cppzmq 4.3.0)
# TODO
#find_dependency(pybind11 )

if(NOT TARGET xeus-clasp)
  include("${CMAKE_CURRENT_LIST_DIR}/xeus-claspTargets.cmake")

  get_target_property(xeus-clasp_INCLUDE_DIR xeus-clasp INTERFACE_INCLUDE_DIRECTORIES)
  get_target_property(xeus-clasp_LIBRARY xeus-clasp LOCATION)
endif()
