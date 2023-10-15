CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(engine)

ADD_EXECUTABLE(engine src/engine.cpp)

target_include_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_link_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/lib/")

target_link_libraries(engine PRIVATE opengl32 glew32s glfw3)
