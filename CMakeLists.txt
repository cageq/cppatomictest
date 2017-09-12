cmake_minimum_required (VERSION 2.6)
project (atomic)
# The version number.
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h

include_directories("rapidjson/include")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -o2 -DNDEBUG ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g -DNDEBUG ")

link_libraries(boost_system)
link_libraries(boost_thread)
 
# add the executable
set(SRC_LIST  test.cpp ) 
add_executable(atomic ${SRC_LIST})
add_executable(queue queue.cpp)
add_executable(stlqueue stlqueue.cpp)
add_executable(follyqueue follyqueue.cpp)
add_executable(spscqueue spscqueue.cpp)
add_executable(boostqueue boostqueue.cpp)




