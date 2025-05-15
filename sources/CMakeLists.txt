project(${USSD_CLI_NAME} VERSION ${USSD_CLI_VERSION} LANGUAGES CXX)

set(CLI_SOURCES main.cpp ussd.cpp)

add_executable(${USSD_CLI_NAME} ${CLI_SOURCES})

target_include_directories(${USSD_CLI_NAME}
                           PRIVATE ${USSD_SOURCE_DIR}/include)

target_link_libraries(${USSD_CLI_NAME} PRIVATE ${USSD_LIB_NAME})

set_target_properties(${USSD_CLI_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                    "${CMAKE_BINARY_DIR}/bin")

if(USSD_CLI_INSTALL)
  install(TARGETS ${USSD_CLI_NAME} DESTINATION bin)
endif()
