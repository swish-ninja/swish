cmake_minimum_required(VERSION 2.8)


############################################
# General Environment configuration
############################################


# Root directory for our project headers
include_directories(./src)


# Include the boost headers and libs
# update according to your system
IF(WIN32)
	include_directories(D:/usr/local/include)
	link_directories(D:/usr/local/lib64/boost)
ELSE()
	include_directories(/usr/local/include)
	link_directories(/usr/local/lib)
ENDIF()


#Main "solution"
project(swish)


#For GCC we need to set a few things like c++11 support, 64 bit arch
#On windows we just need to use the appropriate generator for cmake
if(CMAKE_COMPILER_IS_GNUCC)
	# Initialize CXXFLAGS.
	set (PROJECT_TYPE "CXX")
	set(CMAKE_CXX_FLAGS "-std=c++11 -m64")
endif()

###############################################
#Main projects
###############################################

# common project
file(GLOB COMMON_SOURCE src/common/*.*) 
add_library(common STATIC ${COMMON_SOURCE})
install(TARGETS common DESTINATION lib)

# controller project
file(GLOB CONTROLLER_SOURCE src/controller/*.*) 
add_library(controller STATIC ${CONTROLLER_SOURCE})
install(TARGETS controller DESTINATION lib)

# model project
file(GLOB MODEL_SOURCE src/model/*.*) 
add_library(model STATIC ${MODEL_SOURCE})
install(TARGETS model DESTINATION lib)

# net project
file(GLOB NET_SOURCE src/net/*.*) 
add_library(net STATIC ${NET_SOURCE})
install(TARGETS net DESTINATION lib)

# common project
file(GLOB PATTERN_SOURCE src/pattern/*.*) 
add_library(pattern STATIC ${PATTERN_SOURCE})
install(TARGETS pattern DESTINATION lib)

# common project
file(GLOB MAIN_SOURCE src/main/*.*) 
add_library(swish SHARED ${MAIN_SOURCE})
if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(swish common libboost_system.a)
else()
	target_link_libraries(swish common net pattern model controller)
endif()
install(TARGETS swish DESTINATION bin)


#########################################
#test projects
#########################################

# common test harness
file(GLOB TEST_COMMON_SOURCE test/common/*.*) 
add_executable(test_common ${TEST_COMMON_SOURCE})
if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(test_common common libboost_system.a libboost_test_exec_monitor.a)
else()
	target_link_libraries(test_common common)
endif()
install(TARGETS test_common DESTINATION bin)


# net test harness
file(GLOB TEST_NET_SOURCE test/net/*.*) 
add_executable(test_net ${TEST_NET_SOURCE})
if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(test_net common net libboost_system.a libboost_test_exec_monitor.a)
else()
	target_link_libraries(test_net common net)
endif()
install(TARGETS test_net DESTINATION bin)




# main test harness
file(GLOB TEST_MAIN_SOURCE test/main/*.*) 
add_executable(test_swish ${TEST_MAIN_SOURCE})
if(CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries(test_swish)
else()
	target_link_libraries(test_swish)
endif()
install(TARGETS test_swish DESTINATION bin)
