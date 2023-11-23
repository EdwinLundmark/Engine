CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(engine)

file(GLOB ENGINE_SOURCES src/*.cpp)
list(REMOVE_ITEM ENGINE_SOURCES "main.cpp")

file(GLOB ENGINE_HEADERS src/*.cpp)

ADD_LIBRARY(engine ${ENGINE_SOURCES})

target_include_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/include/")
target_link_directories(engine PUBLIC "${CMAKE_SOURCE_DIR}/lib/" )
target_link_libraries(engine opengl32 glew32s glfw3)

ADD_EXECUTABLE(main "src/main.cpp")
target_link_libraries(main engine)


add_custom_target(CopyShaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shaders/ ${CMAKE_BINARY_DIR}/shaders/
    SOURCES ${CMAKE_SOURCE_DIR}/shaders/
)

add_dependencies(main CopyShaders)