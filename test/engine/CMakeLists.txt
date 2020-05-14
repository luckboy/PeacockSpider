include_directories("${CPPUNIT_INCLUDE_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(../../engine)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" engine_test_sources)

list(APPEND engine_test_libraries ps_engine)
list(APPEND engine_test_libraries ${CPPUNIT_LIBRARIES})

add_executable(testengine "" ${engine_test_sources})
target_link_libraries(testengine ${engine_test_libraries})
add_test(engine_test "${CMAKE_CURRENT_BINARY_DIR}/testengine${CMAKE_EXECUTABLE_SUFFIX}")
