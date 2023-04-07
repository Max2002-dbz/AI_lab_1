add_subdirectory(cell)

add_library(chess chess.cpp chess.ui)

target_link_libraries(chess cell vidpal MyAlgorithm)

target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})