cmake_minimum_required(VERSION 3.10)
project(TSP VERSION 1.0.0)

set(SOURCES
    src/AdjacencyMatrix.cpp
    src/FileHandler.cpp
    src/MenuHandler.cpp
    src/NearestNeighbour.cpp
    src/Path.cpp
    src/SimAnnealing.cpp
    src/TabuSearch.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} stdc++fs)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)