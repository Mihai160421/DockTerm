cmake_minimum_required(VERSION 3.10.0)
project(DockTerm VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(external/glfw)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

file(GLOB IMGUI_SOURCES
    external/imgui/*.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)


add_executable(DockTerm ${SRC_FILES} ${IMGUI_SOURCES})

target_include_directories(DockTerm PRIVATE external/imgui/ external/imgui/backends)
target_include_directories(DockTerm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

#Link Libraries

target_link_libraries(DockTerm PRIVATE glfw)

# OpenGL cross-platform
if(WIN32)
    target_link_libraries(DockTerm PRIVATE opengl32)
elseif(UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(DockTerm PRIVATE OpenGL::GL)
endif()