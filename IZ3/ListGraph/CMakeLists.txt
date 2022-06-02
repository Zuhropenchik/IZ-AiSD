add_library(ListGraph ListGraph.h ListGraph.cpp)
target_include_directories(ListGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ListGraph PUBLIC IGraph)