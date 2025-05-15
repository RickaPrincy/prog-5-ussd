cmake_minimum_required(VERSION 3.18)

project(ussd_tools VERSION 0.0.1)

# c++ 17 by default
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# deps
#find_package(rcli REQUIRED)

set(USSD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(USSD_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(USSD_IS_MAIN_PROJECT ON)
endif()

# target names
set(USSD_LIB_NAME ussd)
set(USSD_LIB_VERSION 0.0.1)
set(USSD_LIB_VERSION_MAJOR 0)
set(USSD_VERSION ${PROJECT_VERSION})
set(USSD_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

# list of options
option(BUILD_SHARED_LIBS "Build rcli as a shared library"
       ${USSD_IS_MAIN_PROJECT})
option(USSD_LIB_BUILD "Build ussd lib" ON)
option(USSD_LIB_INSTALL "Install ussd lib" ${USSD_IS_MAIN_PROJECT})

# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(WIN32)
  add_compile_options(WIN32)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(USSD_TEST OFF)
endif()

if(USSD_IS_MAIN_PROJECT)
  configure_file(${USSD_SOURCE_DIR}/.templates/PKGBUILD.in
                 ${USSD_SOURCE_DIR}/PKGBUILD @ONLY)

  configure_file(${USSD_SOURCE_DIR}/.templates/install.sh.in
                 ${USSD_SOURCE_DIR}/install.sh @ONLY)

  configure_file(${USSD_SOURCE_DIR}/.templates/create-release.sh.in
                 ${USSD_SOURCE_DIR}/create-release.sh @ONLY)

  configure_file(
    ${USSD_SOURCE_DIR}/.templates/${USSD_LIB_NAME}Config.hpp.in
    ${USSD_SOURCE_DIR}/include/${USSD_LIB_NAME}/${USSD_LIB_NAME}Config.hpp
    @ONLY)
endif()

add_subdirectory(sources)

# clang-format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES "${USSD_SOURCE_DIR}/sources/*.cpp"
       "${USSD_SOURCE_DIR}/include/ussd/*.hpp")
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format")
else()
  message(
    WARNING "clang-format not found. Clang-format target will not be available."
  )
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    prog5 exercice
)
include(CPack)
