include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(../engine)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" genalg_sources)

list(APPEND ps_genalg_libraries ps_engine)

add_library(ps_genalg STATIC ${genalg_sources})
target_link_libraries(ps_genalg ${ps_genalg_libraries}) 
