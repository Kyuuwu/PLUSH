cmake_minimum_required(VERSION 3.10.0)
project(PLUSH VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")

message("CMAKE CXX FLAGS: ${CMAKE_CXX_FLAGS}")
message("CMAKE CXX FLAGS RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE CXX FLAGS DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

#OpenGL folder

add_subdirectory(OpenGL)

#PlushUtil folder

add_subdirectory(PlushUtil)

#PlushGraphics layer

add_subdirectory(PlushGraphics)

#PlushEngine layer

add_subdirectory(PlushEngine)

#Setup executable 

add_executable(PLUSH main.cpp)

include_directories(PLUSH PlushUtil/include)
include_directories(PLUSH PlushGraphics/include)
include_directories(PLUSH PlushEngine/include)

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


target_link_libraries(PLUSH PUBLIC PlushUtil_src)
target_link_libraries(PLUSH PUBLIC PlushGraphics_src)
target_link_libraries(PLUSH PUBLIC PlushEngine_src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)