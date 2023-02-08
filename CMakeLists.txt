cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

project("CLI" VERSION ${PROJECT_VERSION} LANGUAGES CXX)

message(NOTICE "${PROJECT_NAME}: ${PROJECT_VERSION}")

set(SUB_LIB_COUNT 2)

# Add Font library
set(FONT_LIBRARY "Font" )
add_subdirectory(${FONT_LIBRARY})
if (FONT_LIBRARY)
    message(NOTICE " - [1/${SUB_LIB_COUNT}] ${FONT_LIBRARY} found")
else()
    message(FATAL_ERROR " - [1/${SUB_LIB_COUNT}] ${FONT_LIBRARY} not found")
endif()

set(ANIMATION_LIBRARY "Animation" )
add_subdirectory(${ANIMATION_LIBRARY})
if (ANIMATION_LIBRARY)
    message(NOTICE " - [2/${SUB_LIB_COUNT}] ${ANIMATION_LIBRARY} found")
else()
    message(FATAL_ERROR " - [2/${SUB_LIB_COUNT}] ${ANIMATION_LIBRARY} not found")
endif()

# Create new library variable
set(CONSOLE_LIBS "Console_Libs")


# Bind libraries to one Library
add_library(${CONSOLE_LIBS} SHARED
        ${FONT_LIBRARY}
        ${ANIMATION_LIBRARY})


add_executable(${PROJECT_NAME} main.cpp )

# Link the libraries
set_target_properties(${CONSOLE_LIBS} PROPERTIES LINKER_LANGUAGE CXX)
include_directories(${CONSOLE_LIBS})

set(CMAKE_MODULE_PATH "/usr/local/share/CMake/Modules")
message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

# Create a library for find_package
install(TARGETS ${PROJECT_NAME}
        EXPORT ${CONSOLE_LIBS}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

# Create a config file for find_package
install(TARGETS ${CONSOLE_LIBS}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
