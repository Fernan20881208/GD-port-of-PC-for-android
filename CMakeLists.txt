cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(PCFPSMOD VERSION 0.3.0)

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
        # setup_geode_mod uses the plain target_link_libraries signature,
        # so keep this call plain as well.
        target_link_libraries(${PROJECT_NAME} ${EGL_LIBRARY})
    else()
        message(FATAL_ERROR "Android EGL library not found; required for VSync control")
    endif()
endif()
