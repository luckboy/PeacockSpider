include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(../engine)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" peacockspider_sources)

list(APPEND peacockspider_libraries ps_engine)

add_executable(peacockspider "" ${peacockspider_sources})
target_link_libraries(peacockspider ${peacockspider_libraries})
