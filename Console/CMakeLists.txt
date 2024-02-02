
set(COMMAND_LINE_SOURCES
        "Commands.hpp"
        "CommandHandler.hpp"
)

add_library(${CONSOLE_LIBRARY} INTERFACE ${COMMAND_LINE_SOURCES} )


target_include_directories( ${CONSOLE_LIBRARY}
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)