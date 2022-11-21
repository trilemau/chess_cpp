cmake_minimum_required(VERSION 3.1)
project(Chess)
set(PROJECT_TESTS Tests${PROJECT_NAME})

# Configure compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wold-style-cast -o2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "/std:c++17 /permissive- /W4 /EHsc /O2")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(SOURCES
    bishop.cpp
    board.cpp
    game.cpp
    king.cpp
    knight.cpp
    pawn.cpp
    piece.cpp
    position.cpp
    queen.cpp
    renderer.cpp
    rook.cpp
    texture.cpp
    )

set(TEST_SOURCES
    test-chess.cpp
    test-main.cpp
    )

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

file(COPY "images" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/") #otherwise we get chess without images

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
add_executable(${PROJECT_TESTS} ${TEST_SOURCES} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_TESTS} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_TESTS} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARY})
target_link_libraries(${PROJECT_TESTS} ${SDL2_IMAGE_LIBRARY})

