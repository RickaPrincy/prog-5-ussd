cmake_minimum_required(VERSION 3.18)

project(ussd_tools VERSION 0.0.1)

# c++ 17 by default
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# deps
find_package(rcli REQUIRED VERSIONS 2.0.22)

set(USSD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(USSD_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(USSD_IS_MAIN_PROJECT ON)
endif()

# target names
set(USSD_CLI_NAME ussd)
set(USSD_CLI_VERSION 0.0.1)
set(USSD_CLI_VERSION_MAJOR 0)
set(USSD_VERSION ${PROJECT_VERSION})
set(USSD_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

# list of options
option(USSD_CLI_BUILD "Build ussd cli" ON)
option(USSD_CLI_INSTALL "Install ussd cli" ${USSD_IS_MAIN_PROJECT})

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
  configure_file(
    ${USSD_SOURCE_DIR}/.templates/${USSD_CLI_NAME}Config.hpp.in
    ${USSD_SOURCE_DIR}/include/${USSD_CLI_NAME}/${USSD_CLI_NAME}Config.hpp
    @ONLY)
endif()

add_subdirectory(sources)

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
  prog5 exercice
)
include(CPack)

# clang-format
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES
     "${USSD_SOURCE_DIR}/sources/*.cpp"
     "${USSD_SOURCE_DIR}/sources/*.hpp"
     "${USSD_SOURCE_DIR}/include/ussd/*.hpp")

  add_custom_target(format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format to format code"
  )

  add_custom_target(format-check
    COMMAND ${CLANG_FORMAT_EXECUTABLE} --dry-run --Werror -style=file ${ALL_SOURCE_FILES}
    COMMENT "Checking code format (clang-format) - will fail if formatting issues"
  )
else()
  message(WARNING "clang-format not found. Format targets will NOT be available.")
endif()

# clang-tidy
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
  if(NOT ALL_SOURCE_FILES)
    file(GLOB_RECURSE ALL_SOURCE_FILES
       "${USSD_SOURCE_DIR}/sources/*.cpp"
       "${USSD_SOURCE_DIR}/sources/*.hpp"
       "${USSD_SOURCE_DIR}/include/ussd/*.hpp")
  endif()
  
  add_custom_target(lint
    COMMAND ${CLANG_TIDY_EXECUTABLE} -p ${CMAKE_CURRENT_BINARY_DIR} ${ALL_SOURCE_FILES}
    COMMENT "Running clang-tidy"
  )
else()
  message(WARNING "clang-tidy not found. clang-tidy target will NOT be available.")
endif()
