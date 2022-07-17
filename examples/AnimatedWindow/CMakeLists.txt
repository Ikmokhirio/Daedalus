cmake_minimum_required(VERSION 3.15)
project(DaedalusExample)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(DAEDALUS_PLATFORM_WINDOWS)
add_compile_definitions(DAEDALUS_STATIC_BUILD)

set(DAEDALUS_PATH ${PROJECT_SOURCE_DIR}/../../)

add_executable(${PROJECT_NAME} WIN32 main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${DAEDALUS_PATH}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${DAEDALUS_PATH}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${DAEDALUS_PATH}/ThirdParty/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${DAEDALUS_PATH}/ThirdParty/spdlog/include)

target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} Daedalus imgui spdlogd d3d9)