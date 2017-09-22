cmake_minimum_required (VERSION 2.6)
project (atomic)
# The version number.
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h

#include_directories("rapidjson/include")
include_directories("libs")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -o2 -DNDEBUG ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g ")

link_libraries(boost_system)

if(APPLE)
link_libraries(boost_thread-mt)
elseif(UNIX)
link_libraries(boost_thread)
else()
link_libraries(boost_thread)
endif()
 

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# add the executable
#set(SRC_LIST  test.cpp ) 
#add_executable(atomic ${SRC_LIST})
add_executable(queue spsc/queue.cpp)
add_executable(stlqueue spsc/stlqueue.cpp)
add_executable(follyqueue spsc/follyqueue.cpp)
add_executable(spscqueue spsc/spscqueue.cpp)
add_executable(boostqueue spsc/boostqueue.cpp)




