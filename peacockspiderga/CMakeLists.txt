include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(../engine)
include_directories(../genalg)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" peacockspiderga_sources)

list(APPEND peacockspiderga_libraries ps_engine)
list(APPEND peacockspiderga_libraries ps_genalg)

add_executable(peacockspiderga "" ${peacockspiderga_sources})
target_link_libraries(peacockspiderga ${peacockspiderga_libraries})
