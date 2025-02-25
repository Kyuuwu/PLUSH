# OPEN GL libraries include

add_library(OPENGL_libraries 
glad.c
)

target_include_directories(OPENGL_libraries PUBLIC include)

target_link_libraries(OPENGL_libraries -lglfw)
target_link_libraries(OPENGL_libraries -lGL)
target_link_libraries(OPENGL_libraries -lX11)
target_link_libraries(OPENGL_libraries -lpthread)
target_link_libraries(OPENGL_libraries -lXrandr)
target_link_libraries(OPENGL_libraries -lXi)
target_link_libraries(OPENGL_libraries -ldl)