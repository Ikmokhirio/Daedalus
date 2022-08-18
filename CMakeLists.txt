cmake_minimum_required(VERSION 3.15)
project(Daedalus)

add_compile_definitions(DAEDALUS_PLATFORM_WINDOWS)


# DON'T TOUCH IT :)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(ENABLE_CMAKE_MESSAGES ON)
#

# YOU CAN INSTALL DIRECTX SDK FROM URL :
set(DXSDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")

# IF SET TO 'ON' DAEDALUS WILL BE BUILD AS SHARED LIBRARY
set(DAEDALUS_SHARED OFF)


file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/static/${PROJECT_NAME})
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/shared/${PROJECT_NAME})
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/static/imgui)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/shared/imgui})
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/static/spdlog)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/shared/spdlog})

if (DAEDALUS_SHARED)
    add_compile_definitions(DAEDALUS_BUILD_DLL)
else ()
    add_compile_definitions(DAEDALUS_STATIC_BUILD)
endif ()

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

add_library(${PROJECT_NAME} ${BUILD_OPTION} include/Daedalus.h src/EntryPoint.h src/Logger.cpp src/Logger.h src/Core.h src/Window/Window.h src/Window/ImGuiBackends/imgui_impl_dx9.cpp src/Window/ImGuiBackends/imgui_impl_dx9.h src/Window/ImGuiBackends/imgui_impl_win32.cpp src/Window/ImGuiBackends/imgui_impl_win32.h src/Window/Window.cpp src/Themes/ImGuiTheme.h src/Themes/ImGuiTheme.cpp src/Themes/ImGuiFont.cpp src/Themes/ImGuiFont.h src/Window/Win32Window.cpp src/Window/Win32Window.h src/Utils/Utils.h src/Utils/Easing/Easing.h src/Utils/Easing/Easing.cpp src/Utils/Utils.cpp src/Images/ImageLoader.cpp src/Images/ImageLoader.h src/Images/ImageDescriptor.h)

if (DAEDALUS_SHARED)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/shared/${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/shared/${PROJECT_NAME})
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/static/${PROJECT_NAME})
endif ()

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
    set_target_properties(imgui PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/shared/imgui)
    set_target_properties(imgui PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/shared/imgui)
else ()
    add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_PUBLIC_HEADERS}
            ${IMGUI_PRIVATE_HEADERS} ${PLATFORM_HEADERS} ${PLATFORM_SOURCE})
    set_target_properties(imgui PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/static/imgui)
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

if (DAEDALUS_SHARED)
    set_target_properties(spdlog PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/shared/spdlog)
    set_target_properties(spdlog PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/shared/spdlog)
    set_target_properties(spdlog PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/shared/spdlog)
else ()
    set_target_properties(spdlog PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/static/spdlog)
endif ()

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/ThirdParty/spdlog/spdlogd.lib ${CMAKE_BINARY_DIR}/spdlogd.lib)

#========FINAL===========

target_include_directories(${PROJECT_NAME} PUBLIC ${ROOT})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${DXSDK_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/spdlog/include)

if (DAEDALUS_SHARED)
    target_link_libraries(${PROJECT_NAME} imgui spdlog d3d9)
endif ()