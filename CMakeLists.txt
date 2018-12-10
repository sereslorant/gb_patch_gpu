cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

ExternalProject_Add(libsdl2
                    URL https://libsdl.org/release/SDL2-2.0.7.tar.gz
                    INSTALL_DIR ${PROJECT_BINARY_DIR}
                    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
                    )

find_package(OpenGL)

include_directories(${PROJECT_BINARY_DIR}/include ${OPENGL_INCLUDE_DIRS} ./)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(patch_loader PatchLoader.cpp)
target_link_libraries(patch_loader SDL2 ${OPENGL_LIBRARIES})
add_dependencies(patch_loader libsdl2)

add_executable(cpu Cpu.cpp)
target_link_libraries(cpu SDL2 ${OPENGL_LIBRARIES})
add_dependencies(cpu libsdl2)

add_executable(barycentric Barycentric.cpp)
target_link_libraries(barycentric SDL2 ${OPENGL_LIBRARIES})
add_dependencies(barycentric libsdl2)

add_executable(side_coords SideCoords.cpp)
target_link_libraries(side_coords SDL2 ${OPENGL_LIBRARIES})
add_dependencies(side_coords libsdl2)

add_executable(bezier_weights BezierWeights.cpp)
target_link_libraries(bezier_weights SDL2 ${OPENGL_LIBRARIES})
add_dependencies(bezier_weights libsdl2)

add_executable(main Main.cpp)
target_link_libraries(main SDL2 ${OPENGL_LIBRARIES})
add_dependencies(main libsdl2)

add_executable(main_shaded MainShaded.cpp)
target_link_libraries(main_shaded SDL2 ${OPENGL_LIBRARIES})
add_dependencies(main_shaded libsdl2)

add_subdirectory(Models)
