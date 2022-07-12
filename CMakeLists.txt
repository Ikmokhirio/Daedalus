cmake_minimum_required(VERSION 3.15)
project(Daedalus)

add_compile_definitions(DAEDALUS_PLATFORM_WINDOWS)
add_compile_definitions(DAEDALUS_BUILD_DLL)

# YOU CAN INSTALL DIRECTX SDK FROM URL :
set(DXSDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")
# IF SET TO 'ON' DAEDALUS WILL BE BUILD AS SHARED LIBRARY
set(DAEDALUS_SHARED OFF)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(ENABLE_CMAKE_MESSAGES ON)

if (ENABLE_CMAKE_MESSAGES)
    message("DirectX9 SDK directory : ${DXSDK_DIR}")
    if (DAEDALUS_SHARED)
        message("Daedalus will be build as shared library")
    else ()
        message("Daedalus will be build as static library")
    endif ()
endif ()

#=====DAEDALUS BUILD==========
if (DAEDALUS_SHARED)
    set(BUILD_OPTION SHARED)
else ()
    set(BUILD_OPTION STATIC)
endif ()

add_library(${PROJECT_NAME} ${BUILD_OPTION} include/Daedalus.h src/EntryPoint.h src/Logger.cpp src/Logger.h src/Core.h src/Window/Window.h src/Window/ImGuiBackends/imgui_impl_dx9.cpp src/Window/ImGuiBackends/imgui_impl_dx9.h src/Window/ImGuiBackends/imgui_impl_win32.cpp src/Window/ImGuiBackends/imgui_impl_win32.h src/Window/Window.cpp src/Themes/ImGuiTheme.h src/Themes/ImGuiTheme.cpp src/Themes/ImGuiFont.cpp src/Themes/ImGuiFont.h)

#=====IMGUI BUILD==========
set(ROOT ${PROJECT_SOURCE_DIR}/ThirdParty/imgui)
set(IMGUI_PUBLIC_HEADERS ${ROOT}/imgui.h)
set(IMGUI_PRIVATE_HEADERS
        ${ROOT}/imgui_internal.h ${ROOT}/imconfig.h ${ROOT}/imstb_rectpack.h
        ${ROOT}/imstb_textedit.h ${ROOT}/imstb_truetype.h)
set(IMGUI_SOURCES ${ROOT}/imgui.cpp ${ROOT}/imgui_draw.cpp
        ${ROOT}/imgui_widgets.cpp ${ROOT}/imgui_demo.cpp ${ROOT}/imgui_tables.cpp)

#PLATFORM BACKENDS
set(PLATFORM_HEADERS src/Window/ImGuiBackends/imgui_impl_dx9.h src/Window/ImGuiBackends/imgui_impl_win32.h)
set(PLATFORM_SOURCE src/Window/ImGuiBackends/imgui_impl_dx9.cpp src/Window/ImGuiBackends/imgui_impl_win32.cpp)

if (DAEDALUS_SHARED)
    add_library(imgui SHARED ${IMGUI_SOURCES})
    target_include_directories(imgui PUBLIC ${ROOT})
else ()
    add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_PUBLIC_HEADERS}
            ${IMGUI_PRIVATE_HEADERS} ${PLATFORM_HEADERS} ${PLATFORM_SOURCE})
    target_include_directories(imgui PUBLIC ${ROOT})
endif ()

#=====SPDLOG BUILD==========
set(SPDLOG_BUILD_WARNINGS 1)
set(SPDLOG_NO_THREAD_ID ON)

if (DAEDALUS_SHARED)
    set(SPDLOG_BUILD_SHARED 1)
else ()
    set(SPDLOG_BUILD_SHARED 0)
endif ()

add_subdirectory(${PROJECT_SOURCE_DIR}/ThirdParty/spdlog)

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ThirdParty/spdlog/spdlogd.lib ${CMAKE_BINARY_DIR}/spdlogd.lib)

#========FINAL===========

target_include_directories(${PROJECT_NAME} PUBLIC ${ROOT})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/spdlog/include)

target_link_libraries(${PROJECT_NAME} imgui)