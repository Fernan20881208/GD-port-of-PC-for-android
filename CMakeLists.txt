cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(GDPCAndroid VERSION 0.2.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find the Geode SDK. Set GEODE_SDK first.")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})

if (ANDROID)
    find_library(EGL_LIBRARY EGL)
    if (EGL_LIBRARY)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${EGL_LIBRARY})
    else()
        message(FATAL_ERROR "Android EGL library not found; required for VSync control")
    endif()
endif()
