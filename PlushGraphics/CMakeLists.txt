ADD_LIBRARY(PlushGraphics_src 
src/PlushGraphicsOpenGL.cpp
src/ShaderSpec.cpp
src/Shader.cpp 
src/Window.cpp
src/ShaderUniformPayload.cpp
src/OpenGL_Type.cpp
src/OpenGL_Value.cpp
src/ModelData.cpp
src/ModelInstance.cpp
src/Texture2D.cpp
src/Drawable.cpp
src/ManagedShader.cpp
src/DrawableIdentifier.cpp
src/GraphicsLayer.cpp
src/GraphicsLayerIdentifier.cpp
src/PlushGraphicsException.cpp
)

target_link_libraries(PlushGraphics_src PUBLIC OPENGL_libraries)
target_link_libraries(PlushGraphics_src PUBLIC PlushUtil_src)

target_include_directories(PlushGraphics_src PUBLIC ../OpenGL/include)
target_include_directories(PlushGraphics_src PUBLIC ../PlushUtil/include)
target_include_directories(PlushGraphics_src PUBLIC ../PlushGraphics)
target_include_directories(PlushGraphics_src PUBLIC ../PlushGraphics/include)