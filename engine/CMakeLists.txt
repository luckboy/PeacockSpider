include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" engine_sources)

add_library(peacockspider_engine STATIC ${engine_sources})
