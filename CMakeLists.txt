cmake_minimum_required(VERSION 4.2.2)
project(iMutsic VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FIND AND CHECK REQUIRED FFMPEG LIBRARY
find_package(PkgConfig REQUIRED)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)

include_directories(include 
    ${AVFORMAT_INCLUDE_DIRS} 
    ${AVCODEC_INCLUDE_DIRS} 
    ${AVUTIL_INCLUDE_DIRS}
)

file(GLOB SOURCES "src/*.cpp")
add_executable(iMutsic ${SOURCES})
include_directories(include)

# LINKING: PAIRING PROGRAMS USE FFMPEG AND LIBAVCODEC LIBRARY
target_link_libraries(iMutsic 
    PRIVATE 
    ${AVFORMAT_LIBRARIES} 
    ${AVCODEC_LIBRARIES} 
    ${AVUTIL_LIBRARIES}
)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # For C++ projects
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O0")
    endif()
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
        # For C projects
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb3 -O0")
    endif()
endif()
