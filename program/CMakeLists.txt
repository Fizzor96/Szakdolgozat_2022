cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)
project(Szakdolgozat)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc -s -Wunused-but-set-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
# set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
# set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")

file(GLOB App_SRC
		"src/*.cpp"
		"src/Components/*.cpp"
		"src/Components/Core/*.cpp"
		"src/Components/Objects/*.cpp"
		"src/Components/Objects/NPC/*.cpp"
		"src/Components/Objects/Decor/*.cpp"
		"src/Components/UI/*.cpp"
		"src/Controllers/*.cpp"
		"src/Views/*.cpp"		
		"src/*.h"
		"src/Components/*.h"
		"src/Components/Core/*.h"
		"src/Components/Objects/*.h"
		"src/Components/Objects/NPC/*.h"
		"src/Components/Objects/Decor/*.h"
		"src/Components/UI/*.h"
		"src/Controllers/*.h"
		"src/Views/*.h"
		)
		
IF (WIN32 AND NOT MSVC)
	add_compile_options(-O3 -g -Wall)
	set(SFML_STATIC_LIBRARIES TRUE)
	set(SFML_DIR "deps/win/SFML-2.5.1/lib/cmake/SFML")
	find_package (SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
	add_executable(${CMAKE_PROJECT_NAME} ${App_SRC})
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "cmake_modules/SFML/include")
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Components)
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Views)
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Controllers)
	target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)
ENDIF()

IF(NOT WIN32)
	add_compile_options(-O3 -g -Wall)
	set(SFML_DIR "deps/linux/SFML-2.5.1/lib/cmake/SFML")
	find_package (SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
	add_executable(${CMAKE_PROJECT_NAME} ${App_SRC})
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "cmake_modules/SFML/include")
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Components)
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Views)
	target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src/Controllers)
	target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-system sfml-audio sfml-window)
ENDIF()
