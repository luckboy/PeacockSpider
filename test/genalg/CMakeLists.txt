include_directories("${CPPUNIT_INCLUDE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(../../engine)
include_directories(../../genalg)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" genalg_test_sources)

list(APPEND genalg_test_libraries ps_engine)
list(APPEND genalg_test_libraries ps_genalg)
list(APPEND genalg_test_libraries ${CPPUNIT_LIBRARIES})

add_executable(testgenalg "" ${genalg_test_sources})
target_link_libraries(testgenalg ${genalg_test_libraries})
add_test(genalg_test "${CMAKE_CURRENT_BINARY_DIR}/testgenalg${CMAKE_EXECUTABLE_SUFFIX}")
