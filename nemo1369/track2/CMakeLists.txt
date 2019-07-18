cmake_minimum_required(VERSION 2.8.11)

cmake_policy(SET CMP0042 NEW)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0057 NEW)

list(APPEND CMAKE_MODULE_PATH
     "${CMAKE_CURRENT_LIST_DIR}/libs/vdf/cmake"
     "${CMAKE_CURRENT_LIST_DIR}/libs/vdf/cmake/packages"
     "${CMAKE_CURRENT_LIST_DIR}/libs/vdf/cmake/modules/share/modules/cmake")

include(CMConfig)
include(CMDeploy)
include(CMSetupVersion)

if(NOT CMAKE_WORKSPACE_NAME OR NOT ${CMAKE_WORKSPACE_NAME} STREQUAL crypto3)
    cm_workspace(crypto3)
endif()

macro(cm_find_package NAME)
    if(NOT "${NAME}" MATCHES "^${CMAKE_WORKSPACE_NAME}_.*$" AND NOT "${NAME}" STREQUAL CM)
        find_package(${ARGV})
    else()
        set(${ARGV0}_FOUND ON CACHE BOOL "")
    endif()
endmacro()

cm_find_package(CM)

add_subdirectory(libs/vdf)

if((NOT GMP_FOUND) OR (NOT GMPXX_FOUND) OR (NOT FLINT_FOUND) OR (NOT MPFR_FOUND) OR (NOT MPIR_FOUND) OR (NOT
    MPIRXX_FOUND))
    if(NOT BUILD_SHARED_LIBS)
        if(UNIX OR APPLE)
            set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" ".la" ${CMAKE_FIND_LIBRARY_SUFFIXES})
        elseif(WIN32)
            set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ${CMAKE_FIND_LIBRARY_SUFFIXES})
        endif()
        cm_find_package(MPFR REQUIRED)
    endif()

    if(CRYPTO3_VDF_MPIR)
        cm_find_package(MPIR REQUIRED)
        cm_find_package(MPIRXX REQUIRED)
    elseif(CRYPTO3_VDF_GMP)
        cm_find_package(GMP REQUIRED)
        cm_find_package(GMPXX REQUIRED)
    elseif(CRYPTO3_VDF_FLINT)
        cm_find_package(GMP REQUIRED)
        cm_find_package(FLINT REQUIRED)
    endif()
endif()

cm_project(chia_vdf_test LANGUAGES ASM C CXX)

# Workaround for interface ASM sources support for CMake <= 3.7
if(NOT CMAKE_ASM_COMPILE_OBJECT)
    enable_language(C CXX ASM)
endif()

list(APPEND ${CURRENT_PROJECT_NAME}_PUBLIC_HEADERS
     )

list(APPEND ${CURRENT_PROJECT_NAME}_HEADERS
     ${${CURRENT_PROJECT_NAME}_PUBLIC_HEADERS}
     )

list(APPEND ${CURRENT_PROJECT_NAME}_SOURCES
     src/main.cpp
     )

cm_setup_version(VERSION 0.1.0 PREFIX ${CURRENT_PROJECT_NAME})

add_executable(${CURRENT_PROJECT_NAME}
               ${${CURRENT_PROJECT_NAME}_HEADERS}
               ${${CURRENT_PROJECT_NAME}_SOURCES})

set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
                      LINKER_LANGUAGE CXX
                      EXPORT_NAME ${CURRENT_PROJECT_NAME}
                      CXX_STANDARD 14)

target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:-O3;-fno-rtti>")

target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>"

                           ${GMPXX_INCLUDE_DIR}
                           ${MPIRXX_INCLUDE_DIR}
                           ${MPFR_INCLUDE_DIR}
                           ${FLINT_INCLUDE_DIR})

if(CRYPTO3_VDF_MPIR)
    target_link_libraries(${CURRENT_PROJECT_NAME} PUBLIC crypto3::vdf
                          ${MPIR_LIBRARIES} ${MPIRXX_LIBRARIES}
                          ${FLINT_LIBRARIES} ${MPFR_LIBRARIES})
else()
    target_link_libraries(${CURRENT_PROJECT_NAME} PUBLIC crypto3::vdf
                          ${GMP_LIBRARIES} ${GMPXX_LIBRARIES}
                          ${MPIR_LIBRARIES} ${MPIRXX_LIBRARIES}
                          ${FLINT_LIBRARIES} ${MPFR_LIBRARIES})
endif()