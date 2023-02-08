
set(ANIMATION_SOURCES
        "Progress.hpp")

add_library(${ANIMATION_LIBRARY} INTERFACE ${ANIMATION_SOURCES} )


target_include_directories( ${ANIMATION_LIBRARY}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR} )