add_library(MatrixGraph MatrixGraph.h MatrixGraph.cpp)
target_include_directories(MatrixGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(MatrixGraph PUBLIC IGraph)
