add_library(SetGraph SetGraph.h SetGraph.cpp)
target_include_directories(SetGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SetGraph PUBLIC IGraph)
