cmake_minimum_required(VERSION 3.20)

#--------------------------------------------------------------
# Project setup
set(PROJECT_NAME "hello-unikernel")
set(PROJECT_TARGET_NAME "hello-unikernel")

project(${PROJECT_NAME}
        DESCRIPTION "LibUV asynchronous TCP and json-c hello world unikernel example"
        VERSION 1.0
        LANGUAGES C)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD          11)

set(SOURCES 
    src/app/main.c 
    src/app/udp/udp-server-echo.h
    src/app/udp/udp-server-echo.c
    src/app/json/json-parser.h
    src/app/json/json-parser.c)

#--------------------------------------------------------------
# Build binary directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#--------------------------------------------------------------
# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules")

## LibUV
find_package(LibUV  REQUIRED)
find_package(JSON-C REQUIRED)

## Json-C

#--------------------------------------------------------------
# Target
add_executable(${PROJECT_TARGET_NAME} ${SOURCES})

target_include_directories(${PROJECT_TARGET_NAME} PUBLIC src/app)
target_include_directories(${PROJECT_TARGET_NAME} PUBLIC src/utils)

target_link_libraries(${PROJECT_TARGET_NAME} PUBLIC ${LIBUV_LIBRARIES})
target_link_libraries(${PROJECT_TARGET_NAME} PUBLIC ${JSON-C_LIBRARIES})
