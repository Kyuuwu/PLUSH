cmake_minimum_required(VERSION 3.0.0)
project(PLUSH VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include(CTest)
enable_testing()

# OPEN GL libraries include

add_library(OPENGL_libraries 
OPENGL_libraries/glad.c
)

target_include_directories(OPENGL_libraries PUBLIC OPENGL_libraries/include)

target_link_libraries(OPENGL_libraries -lglfw)
target_link_libraries(OPENGL_libraries -lGL)
target_link_libraries(OPENGL_libraries -lX11)
target_link_libraries(OPENGL_libraries -lpthread)
target_link_libraries(OPENGL_libraries -lXrandr)
target_link_libraries(OPENGL_libraries -lXi)
target_link_libraries(OPENGL_libraries -ldl)

#Plush helpers include

add_library(PLUSH_helpers
PLUSH_helpers/Helpers.cpp
)

target_include_directories(PLUSH_helpers PUBLIC PLUSH_helpers/include)
target_link_libraries(PLUSH_helpers PUBLIC OPENGL_libraries)

#OPEN GL backend include

add_library(OPENGL_management 
OPENGL_management/WindowSetup.cpp
OPENGL_management/Window.cpp
OPENGL_management/WindowRendering.cpp
OPENGL_management/Shader.cpp
OPENGL_management/ShaderUniforms.cpp
OPENGL_management/ShaderGeneration.cpp
OPENGL_management/ShaderLibrary.cpp
OPENGL_management/Model.cpp
OPENGL_management/ModelGeneration.cpp
OPENGL_management/ModelLibrary.cpp
OPENGL_management/Texture2D.cpp
OPENGL_management/TextureLibrary.cpp
)

target_include_directories(OPENGL_management PUBLIC OPENGL_management/include)

target_link_libraries(OPENGL_management PUBLIC OPENGL_libraries)
target_link_libraries(OPENGL_management PUBLIC PLUSH_helpers)

#PLUSH core include

add_library(PLUSH_core
PLUSH_core/Entity.cpp
PLUSH_core/RotationHandler.cpp
PLUSH_core/TileGrid.cpp
PLUSH_core/TileGridLayer.cpp
PLUSH_core/WindowHandler.cpp
PLUSH_core/Drawable.cpp
)

target_include_directories(PLUSH_core PUBLIC PLUSH_core/include)

target_link_libraries(PLUSH_core PUBLIC OPENGL_management)
target_link_libraries(PLUSH_core PUBLIC PLUSH_helpers)

#Setup executable 

add_executable(PLUSH main.cpp
PLUSH_game/Example_Tile_Game.cpp
)
target_include_directories(PLUSH PUBLIC PLUSH_game/include)

#Copy shaders, textures, and models

add_custom_target(COPY_SHADERS ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/amongus.h)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/amongus.h COMMAND cmake -E echo)

add_custom_command(TARGET COPY_SHADERS POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:PLUSH>/shaders)

add_custom_command(TARGET COPY_SHADERS POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/models $<TARGET_FILE_DIR:PLUSH>/models)

                       add_custom_command(TARGET COPY_SHADERS POST_BUILD
                                          COMMAND ${CMAKE_COMMAND} -E copy_directory
                                              ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:PLUSH>/textures)


target_link_libraries(PLUSH PUBLIC OPENGL_management)
target_link_libraries(PLUSH PUBLIC OPENGL_libraries)
target_link_libraries(PLUSH PUBLIC PLUSH_core)
target_link_libraries(PLUSH PUBLIC PLUSH_helpers)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

message(${CMAKE_CXX_FLAGS_RELEASE})
message(${CMAKE_CXX_FLAGS_DEBUG})