cmake_minimum_required(VERSION 3.15)
project(DaedalusExample)

set(CMAKE_CXX_STANDARD 20)
set(DAEDALUS_SHARED 0)

add_compile_definitions(DAEDALUS_PLATFORM_WINDOWS)
add_compile_definitions(DAEDALUS_STATIC_BUILD)

set(DAEDALUS_BUILD_DIR ${PROJECT_SOURCE_DIR}/../cmake-build-debug)

add_executable(${PROJECT_NAME} WIN32 src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../ThirdParty/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../ThirdParty/spdlog/include)

target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} Daedalus imgui spdlogd d3d9)

add_custom_command(TARGET ${PROJECT_NAME} PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy ${DAEDALUS_BUILD_DIR}/imgui.lib ${CMAKE_BINARY_DIR}/imgui.lib)
add_custom_command(TARGET ${PROJECT_NAME} PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy ${DAEDALUS_BUILD_DIR}/Daedalus.lib ${CMAKE_BINARY_DIR}/Daedalus.lib)
add_custom_command(TARGET ${PROJECT_NAME} PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy ${DAEDALUS_BUILD_DIR}/ThirdParty/spdlog/spdlogd.lib ${CMAKE_BINARY_DIR}/spdlogd.lib)
