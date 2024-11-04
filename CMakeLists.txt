cmake_minimum_required(VERSION 3.17)
project(
		CS251Projects
		VERSION 0.1
		DESCRIPTION "CS251Projects"
)

# Set a default build type if none was specified
set(default_build_type "Release")

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
			STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
			"Debug" "Release")
endif ()

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
    set(DEBUG_STATUS NDEBUG)
elseif (CMAKE_BUILD_TYPE MATCHES "[Dd]ebug")
    set(DEBUG_STATUS _DEBUG)
endif ()

set(CMAKE_CXX_STANDARD 17)
# Options that control optimization: http://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html



set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# ------------------------------------------------------------------
# Project 1
# ------------------------------------------------------------------
file(GLOB LOCAL_PROJECTS_SOURCES "src/*.cpp")

add_library(project1 
	STATIC
	${LOCAL_PROJECTS_SOURCES}
	)

target_compile_definitions(project1
	PRIVATE
	NOMINMAX
	)
set(LOCAL_PROJECTS_INCLUDES
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
	)

target_include_directories(project1
	PUBLIC
	${LOCAL_PROJECTS_INCLUDES}
	)

# ------------------------------------------------------------------
# Program be used for testing
# ------------------------------------------------------------------
add_executable(queue-app
	"src/queue_app.cpp")

target_link_libraries(queue-app
	project1
	)
target_compile_definitions(queue-app
	PRIVATE
	NOMINMAX
	)
add_executable(maze-app
	"src/maze_app.cpp")

target_link_libraries(maze-app
	project1
	)
target_compile_definitions(maze-app
	PRIVATE
	NOMINMAX
	)