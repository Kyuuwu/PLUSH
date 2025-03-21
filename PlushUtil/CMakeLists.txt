ADD_LIBRARY(PlushUtil_src
src/ReadFile.cpp
src/PlushUtilException.cpp
)

target_include_directories(PlushUtil_src PUBLIC ../PlushUtil)
target_include_directories(PlushUtil_src PUBLIC ../PlushUtil/include)