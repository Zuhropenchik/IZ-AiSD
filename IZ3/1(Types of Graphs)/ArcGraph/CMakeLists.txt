add_library(ArcGraph ArcGraph.h ArcGraph.cpp)
target_include_directories(ArcGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ArcGraph PUBLIC IGraph)
