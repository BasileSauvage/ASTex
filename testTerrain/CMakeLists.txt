cmake_minimum_required(VERSION 3.0)
 
project(Terrain LANGUAGES CXX)

find_package(ASTex)

add_definitions(-DTEMPO_PATH=std::string\(\"${ASTEX_TEMPO_PATH}/\"\) )


add_executable(terrain "")
target_sources(terrain PRIVATE terrain.cpp)
target_link_libraries(terrain PRIVATE ASTex)



