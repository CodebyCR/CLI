
set(FONT_SOURCES
        "RGB.hpp"
        "Format.hpp"
        "Foreground.hpp"
        "Background.hpp"
        "Underline.hpp"
        "Color.hpp"
        "Gradient.hpp")

add_library(${FONT_LIBRARY} INTERFACE ${FONT_SOURCES} )


target_include_directories( ${FONT_LIBRARY}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR} )