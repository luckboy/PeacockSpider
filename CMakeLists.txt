cmake_minimum_required(VERSION 2.6)
project(peacockspider)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

add_subdirectory(engine)

if(BUILD_TESTING)
	enable_testing()

	find_package(CPPUNIT REQUIRED)

	add_subdirectory(test)
endif(BUILD_TESTING)
