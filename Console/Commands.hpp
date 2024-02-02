//
// Created by Christoph Rohde on 02.02.24.
//

#pragma once

#include <iostream>
#include <map>

namespace CLI {

    enum class Commands : std::uint16_t {
        EXIT    = 0000'0000,
        HELP    = 0000'0001,
        VERBOSE = 0000'0010,
        VERSION = 0000'0011,
        SHOW    = 0000'0101,
        TO_HEX  = 0000'1001,
        TO_DEC  = 0001'0001,
        TO_RGB  = 0010'0001,

        /// Combined commands
        TO_HEX_AND_SHOW = 0000'1101,
        TO_DEC_AND_SHOW = 0001'0101,
        TO_RGB_AND_SHOW = 0010'0101,

        /// With verbose
        TO_HEX_AND_VERBOSE = 0000'1011,
        TO_DEC_AND_VERBOSE = 0001'0011,
        TO_RGB_AND_VERBOSE = 0010'0011,

        TO_HEX_AND_SHOW_VERBOSE = 0000'1111,
        TO_DEC_AND_SHOW_VERBOSE = 0001'0111,
        TO_RGB_AND_SHOW_VERBOSE = 0010'0111
    };

    constexpr auto operator|(Commands lhs, Commands rhs) -> Commands {
        return static_cast<Commands>(static_cast<std::uint16_t>(lhs) | static_cast<std::uint16_t>(rhs));
    }

    constexpr auto operator&(Commands lhs, Commands rhs) -> Commands {
        return static_cast<Commands>(static_cast<std::uint16_t>(lhs) & static_cast<std::uint16_t>(rhs));
    }

    constexpr auto operator+=(Commands lhs, Commands rhs) -> Commands {
        return static_cast<Commands>(static_cast<std::uint16_t>(lhs) + static_cast<std::uint16_t>(rhs));
    }


    constexpr auto to_command(std::uint16_t command) -> Commands {
        return static_cast<Commands>(command);
    }


    static auto to_string(Commands command) -> std::string {
        std::map<Commands, std::string> commandMap = {
                {Commands::EXIT, "EXIT"},
                {Commands::HELP, "HELP"},
                {Commands::VERBOSE, "VERBOSE"},
                {Commands::VERSION, "VERSION"},
                {Commands::SHOW, "SHOW"},
                {Commands::TO_HEX, "TO_HEX"},
                {Commands::TO_DEC, "TO_DEC"},
                {Commands::TO_RGB, "TO_RGB"},
                {Commands::TO_HEX_AND_SHOW, "TO_HEX_AND_SHOW"},
                {Commands::TO_DEC_AND_SHOW, "TO_DEC_AND_SHOW"},
                {Commands::TO_RGB_AND_SHOW, "TO_RGB_AND_SHOW"},
                {Commands::TO_HEX_AND_VERBOSE, "TO_HEX_AND_VERBOSE"},
                {Commands::TO_DEC_AND_VERBOSE, "TO_DEC_AND_VERBOSE"},
                {Commands::TO_RGB_AND_VERBOSE, "TO_RGB_AND_VERBOSE"},
                {Commands::TO_HEX_AND_SHOW_VERBOSE, "TO_HEX_AND_SHOW_VERBOSE"},
                {Commands::TO_DEC_AND_SHOW_VERBOSE, "TO_DEC_AND_SHOW_VERBOSE"},
                {Commands::TO_RGB_AND_SHOW_VERBOSE, "TO_RGB_AND_SHOW_VERBOSE"}
        };

        return commandMap[command];
    }

    // example cli usage:
    // ./cli --hex 0,255,0      -> #00FF00
    // ./cli --rgb #00FF00      -> 0,255,0
    // ./cli --help             -> print help
    // ./cli --version          -> print brand
    // ./cli --show 0,255,0     -> 0,255,0 (and color in terminal)
    // ./cli -sr #00FF00        -> 0,255,0 (and color in terminal)

    static auto map_to_command(std::vector<std::string> const &command) -> Commands {
        std::map<std::string, Commands> commandMap = {
                {"--help",    Commands::HELP},
                {"-h",        Commands::HELP},
                {"--verbose", Commands::VERBOSE},
                {"-b",        Commands::VERBOSE},
                {"--version", Commands::VERSION},
                {"-v",        Commands::VERSION},
                {"--show",    Commands::SHOW},
                {"-s",        Commands::SHOW},
                {"--hex",     Commands::TO_HEX},
                {"-16",       Commands::TO_HEX},
                {"--rgb",     Commands::TO_RGB},
                {"-r",        Commands::TO_RGB},
                {"--exit",    Commands::EXIT},
                {"-e",        Commands::EXIT},

                /// Combined Commands
                {"-sr",       Commands::TO_RGB_AND_SHOW},
                {"-rs",       Commands::TO_HEX_AND_SHOW},

                {"-16s",      Commands::TO_HEX_AND_SHOW},
                {"-s16",      Commands::TO_HEX_AND_SHOW},

                {"-10s",      Commands::TO_DEC_AND_SHOW},
                {"-s10",      Commands::TO_DEC_AND_SHOW},

                /// With verbose
                {"-16b",      Commands::TO_HEX_AND_VERBOSE},
                {"-b16",      Commands::TO_HEX_AND_VERBOSE},

                {"-10b",      Commands::TO_DEC_AND_VERBOSE},
                {"-b10",      Commands::TO_DEC_AND_VERBOSE},

                {"-s16b",     Commands::TO_HEX_AND_SHOW_VERBOSE},
                {"-b16s",     Commands::TO_HEX_AND_SHOW_VERBOSE},

                {"-s10b",     Commands::TO_DEC_AND_SHOW_VERBOSE},
                {"-b10s",     Commands::TO_DEC_AND_SHOW_VERBOSE},


        };

        Commands totalCommand = Commands::EXIT;

        for(auto const &cmd: command) {
            if (commandMap.contains(cmd)) {
                totalCommand = totalCommand | commandMap[cmd];
            }
        }

        return totalCommand;
    }


}