ADD_LIBRARY(PlushEngine_src src/Entity.cpp
src/EntityIdentifier.cpp
src/Scene.cpp
src/SceneIdentifier.cpp
src/DrawMod.cpp
src/ManagedEntity.cpp
)

target_link_libraries(PlushEngine_src PUBLIC PlushGraphics_src)
target_link_libraries(PlushEngine_src PUBLIC PlushUtil_src)

target_include_directories(PlushEngine_src PUBLIC ../PlushGraphics/include)
target_include_directories(PlushEngine_src PUBLIC ../PlushUtil/include)
target_include_directories(PlushEngine_src PUBLIC ../PlushEngine)
target_include_directories(PlushEngine_src PUBLIC ../PlushEngine/include)