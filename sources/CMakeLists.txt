project(${USSD_LIB_NAME} VERSION ${USSD_LIB_VERSION} LANGUAGES CXX)

set(LIB_SOURCES ussd.cpp)

# Create the library
if(BUILD_SHARED_LIBS)
  add_library(${USSD_LIB_NAME} SHARED ${LIB_SOURCES})
else()
  add_library(${USSD_LIB_NAME} STATIC ${LIB_SOURCES})
endif()

# Set include directories for the library
target_include_directories(
  ${USSD_LIB_NAME} PRIVATE $<BUILD_INTERFACE:${USSD_SOURCE_DIR}/include>)

# target_link
#target_link_libraries(${USSD_LIB_NAME} PUBLIC rcli)

# set properties
set_target_properties(
  ${USSD_LIB_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             SOVERSION ${USSD_LIB_VERSION_MAJOR}
             VERSION ${USSD_LIB_VERSION})

# lib install configuration
if(USSD_LIB_INSTALL)
  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${USSD_LIB_NAME}Version.cmake
    VERSION ${USSD_VERSION}
    COMPATIBILITY SameMajorVersion)

  include(GNUInstallDirs)
  install(DIRECTORY ${USSD_SOURCE_DIR}/include/${USSD_LIB_NAME}
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(
    TARGETS ${USSD_LIB_NAME}
    EXPORT ${USSD_LIB_NAME}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)

  # Install the Config and ConfigVersion files
  install(
    EXPORT ${USSD_LIB_NAME}Targets
    FILE ${USSD_LIB_NAME}Targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${USSD_LIB_NAME})

  configure_file(${USSD_SOURCE_DIR}/cmake/${USSD_LIB_NAME}Config.cmake.in
                 ${CMAKE_BINARY_DIR}/cmake/${USSD_LIB_NAME}Config.cmake @ONLY)
  # Install the Config, ConfigVersion, and custom Find module files
  install(FILES ${CMAKE_BINARY_DIR}/cmake/${USSD_LIB_NAME}Config.cmake
                ${CMAKE_BINARY_DIR}/cmake/${USSD_LIB_NAME}Version.cmake
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${USSD_LIB_NAME})
endif()
