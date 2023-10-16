CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(engine)

ADD_EXECUTABLE(engine src/engine.cpp)

add_library(load-shader src/load-shader.cpp src/load-shader.hpp)
target_include_directories(load-shader PUBLIC "${CMAKE_SOURCE_DIR}/include/")


target_include_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_link_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/lib/")

target_link_libraries(engine PRIVATE opengl32 glew32s glfw3 load-shader)

add_custom_command(TARGET engine PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/shaders/ $<TARGET_FILE_DIR:engine>)
