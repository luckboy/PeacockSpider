include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(../engine)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" genalg_sources)

add_library(ps_genalg STATIC ${genalg_sources})
