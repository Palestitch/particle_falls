cmake_minimum_required(VERSION 3.7)
project(particle_falls)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp stb_image.hpp Color.cpp Color.hpp Image.cpp Image.hpp Waterfall.cpp Waterfall.hpp Particle.hpp Particle.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY})
