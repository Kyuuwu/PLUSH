ADD_LIBRARY(PlushGraphics_src 
src/PlushGraphicsOpenGL.cpp
src/ShaderSpec.cpp
src/Shader.cpp 
src/Window.cpp
src/ShaderUniformValue.cpp
)

target_link_libraries(PlushGraphics_src PUBLIC OPENGL_libraries)
target_link_libraries(PlushGraphics_src PUBLIC PlushUtil_src)

target_include_directories(PlushGraphics_src PUBLIC ../OpenGL/include)
target_include_directories(PlushGraphics_src PUBLIC ../PlushUtil/include)
target_include_directories(PlushGraphics_src PUBLIC ../PlushGraphics/include)