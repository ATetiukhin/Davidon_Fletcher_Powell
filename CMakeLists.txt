cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# Project settings
set(PROJECT_NAME Optimization)
set(APP_NAME Davidon_Fletcher_Powell)
project(${PROJECT_NAME})

############################################################################################

# OS settings
if (WIN32 OR APPLE)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build/install CACHE STRING "" FORCE)
endif(WIN32 OR APPLE)

############################################################################################

# BOOST
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(BOOST_COMPONENTS)

find_package(Boost COMPONENTS ${BOOST_COMPONENTS} QUIET REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

############################################################################################

set(ALL_FILES
    Davidon_Fletcher_Powell.hpp
    main.cpp
    )

############################################################################################

add_executable(${APP_NAME} ${ALL_FILES})
target_link_libraries(${APP_NAME} ${Boost_LIBRARIES})
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_DEBUG "${APP_NAME}d")
set_target_properties(${APP_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${APP_NAME})

############################################################################################

# Project settings
if (MSVC)

    source_group("Source Files" FILES ${ALL_FILES})

    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS                "/EHsc /W4 /nologo /wd4127" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG          "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS_MINSIZEREL     "/MD /O1 /Ob1 /D NDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE        "/MD /O2 /Ob2 /D NDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /O2 /Ob1 /D NDEBUG")

    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS " /DYNAMICBASE:NO /FIXED")

elseif (CMAKE_COMPILER_IS_GNUCXX)

    # Setting directory
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIRECTORY} CACHE STRING "" FORCE)

    # Compiler flags
    set(CMAKE_CXX_FLAGS " -std=c++11 -Wall " CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG " -g -O0 " CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE " -O2 " CACHE STRING "" FORCE)

    # Linker flags
    set(CMAKE_EXE_LINKER_FLAGS " -static-libgcc -static-libstdc++ -static " CACHE STRING "" FORCE)
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" CACHE STRING "" FORCE) # remove dynamic for CXX
    set(BUILD_SHARED_LIBS OFF)

endif (MSVC)

############################################################################################
