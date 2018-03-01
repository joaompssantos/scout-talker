###
### CMakeLists for Scout Talker
###

######################################################################################
# CMake  functions
######################################################################################

cmake_minimum_required(VERSION 3.5.1)

# https://cmake.org/cmake/help/v3.8/module/FeatureSummary.html
#INCLUDE(FeatureSummary)
# https://cmake.org/cmake/help/v3.8/module/GNUInstallDirs.html?highlight=gnuinstalldirs
#INCLUDE(GNUInstallDirs)

######################################################################################
# Project Definition
######################################################################################

set(PROJECT_NAME "scout_talker")
project(${PROJECT_NAME})

set(SCOUTTALKER_VERSION_MAJOR "0")
set(SCOUTTALKER_VERSION_MINOR "1")
set(SCOUTTALKER_VERSION_PATCH "0")
set(SCOUTTALKER_VERSION "${SCOUTTALKER_VERSION_MAJOR}.${SCOUTTALKER_VERSION_MINOR}.${SCOUTTALKER_VERSION_PATCH}")
set(SCOUTTALKER_VERSION "Alpha")

######################################################################################
# Variables
######################################################################################

OPTION(USE_EXTRA_WARNINGS "Enable extra warnings" OFF)
OPTION(USE_WERROR "Warnings as errors" OFF)

### Examples
#OPTION( BUILD_APP               "Build GUI Application"                 ON  )
#OPTION( BUILD_TOOLS             "Build Command Line Application"        ON  )
#OPTION( BUILD_EXAMPLES          "Build Examples"                        OFF )
#OPTION( BUILD_DOC               "Build Documentation"                   OFF )
#OPTION( BUILD_TESTS             "Build Google Tests"                    ON  )
#
#OPTION( USE_FERVOR              "Add Fervor support"                    OFF )
#
#OPTION( USE_DYNLOAD             "Use dynamic load of modules"           ON  )
#OPTION( USE_SSE                 "Build with SSE support"                OFF )
#OPTION( USE_STATIC              "Use static libs"                       OFF )

######################################################################################
# Release configuration
######################################################################################

# To be switched on when releasing.
OPTION(RELEASE_BUILD "Remove Git revision from program version (use for stable releases)" ON)

# Get current version.

set(SCOUTTALKER_VERSION_STRING "${SCOUTTALKER_VERSION}")
if (NOT RELEASE_BUILD AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
    # Probably a Git workspace; determine the revision.
    FIND_PACKAGE(Git QUIET)
    if (GIT_FOUND)
        exec_program(${GIT_EXECUTABLE}
                ${CMAKE_CURRENT_SOURCE_DIR}
                ARGS "describe --tags"
                OUTPUT_VARIABLE SCOUTTALKER_GIT_REVISION
                RETURN_VALUE TAG_RESULT
                )
        # git describe --tags failed; maybe the repository was checked with depth=1.
        if (NOT ${TAG_RESULT} EQUAL 0)
            exec_program(${GIT_EXECUTABLE}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ARGS "describe --always"
                    OUTPUT_VARIABLE SCOUTTALKER_GIT_REVISION
                    )
        endif ()
        message(STATUS "Scout Talker Git revision: ${SCOUTTALKER_GIT_REVISION}")
        set(SCOUTTALKER_VERSION_STRING "${PLAYUVER_GIT_REVISION_VERSION} (rev. ${SCOUTTALKER_GIT_REVISION})")
    else ()
        message(STATUS "Scout Talker Git revision could not be determined")
    endif ()
endif ()

######################################################################################
# Dependencies
######################################################################################

######################################################################################
# CMake Definitions
######################################################################################

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

######################################################################################
# Configure targets
######################################################################################

# Define C++ standard 14
set(CMAKE_CXX_STANDARD 14)

# Define build type if not defined
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif ()

# Set compile flags
set(CMAKE_CXX_FLAGS "-funroll-loops -Wall -Wextra" CACHE STRING "compile flags" FORCE)

# Set extra warnigns
if (USE_EXTRA_WARNINGS)
    string(CONCAT CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align "
            "-Wstrict-prototypes -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code")
endif ()

# Set warnings as errors
if (USE_WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif ()

# Add optimisation flags for DEBUG and RELEASE
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Configure a header file to pass some of the CMake settings to the source code
configure_file("${PROJECT_SOURCE_DIR}/src/ScoutTalkerConfig.h.in" "${PROJECT_BINARY_DIR}/ScoutTalkerConfig.h")

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/dialog)

set(SCOUTTALKER_SRC
        src/main.cpp
        src/MainWindow.cpp
        src/MainWindow.h
        src/ScoutTalker.cpp
        src/ScoutTalker.h
        src/dialog/AboutDialog.cpp
        src/dialog/AboutDialog.h)

set(SCOUTTALKER_RCC
        src/resources/fonts.qrc
        src/resources/icons.qrc
        )

set(SCOUTTALKER_TS
        src/translations/ScoutTalker_en_UK.ts
        src/translations/ScoutTalker_pt_PT.ts
        )

# Find the QtWidgets library
find_package(Qt5LinguistTools)
find_package(Qt5 REQUIRED COMPONENTS Widgets PrintSupport)

qt5_add_resources(SCOUTTALKER_RCC ${SCOUTTALKER_RCC})

qt5_add_translation(SCOUTTALKER_QM ${SCOUTTALKER_TS})

# Prevents the windows consolo from showing
if(WIN32)
    SET( USE_STATIC ON )
    set(GUI_TYPE WIN32)
endif(WIN32)

add_executable(${PROJECT_NAME} ${GUI_TYPE} ${SCOUTTALKER_SRC} ${SCOUTTALKER_RCC} ${SCOUTTALKER_QM})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::PrintSupport)

######################################################################################
# Final information dump
######################################################################################
message("")
message(STATUS "${PROJECT_NAME} INFORMATION")
message(STATUS "Version: " "${SCOUTTALKER_VERSION_STRING}")
message(STATUS "Configuration:")
message(STATUS "    C++ Standard: " "${CMAKE_CXX_STANDARD}")
message(STATUS "    Build type: " "${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "    Build flags: " "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
else ()
    message(STATUS "    Build flags: " "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
endif ()
message("")