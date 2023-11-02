CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(engine)

ADD_EXECUTABLE(main src/main.cpp)

add_library(load-shader src/load-shader.cpp src/load-shader.hpp)
target_include_directories(load-shader PUBLIC "${CMAKE_SOURCE_DIR}/include/")

add_library(engine src/engine.cpp src/engine.hpp)
target_include_directories(load-shader PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_link_libraries(engine PRIVATE opengl32 glew32s glfw3 load-shader)

target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_link_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/lib/")

target_link_libraries(main PRIVATE engine)

add_custom_target(CopyShaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders/ ${CMAKE_BINARY_DIR}/shaders/
    SOURCES ${CMAKE_SOURCE_DIR}/shaders/
)

add_dependencies(main CopyShaders)