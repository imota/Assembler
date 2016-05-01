cmake_minimum_required(VERSION 2.8)

project(Tradutor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

#########################################################
# INCLUDE DIRECTORIES
#########################################################
include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/include 
)

#########################################################
# INCLUDE FILES
#########################################################
set(SOURCES 
	source/PreProcessor.cpp
	source/FirstPass.cpp
	source/instruction.cpp
	source/token.cpp
	)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
