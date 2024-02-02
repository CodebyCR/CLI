//
// Created by Christoph Rohde on 02.02.24.
//

#pragma once

#include "Commands.hpp"
#include "../Font/Gradient.hpp"
#include "../Font/Color.hpp"
#include "../Font/Color.hpp"
#include "../Font/Foreground.hpp"
#include "../Font/Background.hpp"

#include <iostream>
#include <vector>


class CommandHandler {
private:
    std::vector<std::string> rawCommands;

    auto getFilteredArgs() -> std::vector<std::string> {
        std::vector<std::string> filteredArgs;
        // drop the first argument, which is the program name
        rawCommands.erase(rawCommands.begin());
//        rawCommands.erase(rawCommands.begin());

        std::ranges::copy_if(rawCommands, std::back_inserter(filteredArgs), [](auto const& arg) {
            return arg != "cli" && !arg.starts_with("-");
        });

        return filteredArgs;
    }

    auto print_brand() -> std::string {
        constexpr auto brand =  "    CLI Tools • since 2023 •\n"
                                "    Version: 0.6.0\n"
                                "    All rights reserved.\n"
                                "    Copyright © 2024. Christoph Rohde\n"
                                "    Licence: MIT";

        const auto brandGradient = Gradient(Color::DRIP_PURPLE, Color::CYAN, 75);

        std::stringstream ss;
        ss
                << Font::print_as_line(brandGradient)
                << Font::Foreground(Color::LIGHT_PURPLE) << brand << Font::RESET_FOREGROUND << std::endl
                << Font::print_as_line(brandGradient);
        return ss.str();
    }

public:
    explicit CommandHandler(std::vector<std::string> const& rawCommands) : rawCommands(rawCommands) {}

    auto execute_args() -> void {
        const CLI::Commands command = CLI::map_to_command(this->rawCommands);
        execute_command(command);
    }


    auto execute_command(CLI::Commands const& command) -> void {
        const auto filteredArgs = getFilteredArgs();

        switch(command){
            using namespace CLI;

            case Commands::EXIT:
                std::cout << "No commands / args given" << std::endl;
                break;

            case Commands::HELP:
                std::cout <<
                          "Currently supported commands:\n"
                          "  -h, --help:      Display this help message\n"
                          "  -v, --version:   Display the version of the program\n"
                          "  -16, --hex:      Convert a RGB color code to Hex ('0,255,0' -> '#00FF00')\n"
                          "  -r, --rgb:       Convert a Hex color code to RGB ('#00FF00' -> '0,255,0')\n"
                          "  -s, --show:      Show the color in the terminal\n";
                break;

            case Commands::VERBOSE:
                for(auto index = 0; index < filteredArgs.size(); index++) {
                    std::cout << index << " " << filteredArgs[index] << std::endl;
                }
                std::cout << std::endl;
                break;

            case Commands::VERSION:
                std::cout << print_brand() << std::endl;
                break;

            case Commands::SHOW:
                break;

            case Commands::TO_HEX_AND_VERBOSE:
                for(auto index = 0; index < filteredArgs.size(); index++) {
                    std::cout << index << " " << filteredArgs[index] << std::endl;
                }
                std::cout << std::endl;

            [[fallthrough]];
            case Commands::TO_HEX:
                for(auto const& arg : filteredArgs){
                    const auto color = Color::from_rgb(arg);
                    std::cout << arg << " -> Hex: #" << Color::to_hex(color) << std::endl;
                }
                break;

            case Commands::TO_DEC:
                break;


            case Commands::TO_RGB_AND_VERBOSE:
                for(auto index = 0; index < filteredArgs.size(); index++) {
                    std::cout << index << " " << filteredArgs[index] << std::endl;
                }
                std::cout << std::endl;

            [[fallthrough]];
            case Commands::TO_RGB:
                for(auto const& arg : filteredArgs){
                    const auto color = Color::from_hex(arg);
                    std::cout << arg << " -> RGB: " << Color::to_rgb(color) << std::endl;
                }
                break;


            case Commands::TO_HEX_AND_SHOW_VERBOSE:
                for(auto index = 0; index < filteredArgs.size(); index++) {
                    std::cout << index << " " << filteredArgs[index] << std::endl;
                }
                std::cout << std::endl;

            [[fallthrough]];
            case Commands::TO_HEX_AND_SHOW:
                for(auto const& arg : filteredArgs){
                    const auto color = Color::from_rgb(arg);
                    const std::vector<RGB> gradient{color, color, color};

                    std::cout << "RGB: " << arg
                    << " -> Hex: #" << Color::to_hex(color) << ' '
                    << Font::print_as_block(gradient) << std::endl;
                }
                break;


            case Commands::TO_DEC_AND_SHOW_VERBOSE:
                for(auto index = 0; index < filteredArgs.size(); index++) {
                    std::cout << index << " " << filteredArgs[index] << std::endl;
                }
                std::cout << std::endl;

            [[fallthrough]];
            case Commands::TO_DEC_AND_SHOW:
                break;


            case Commands::TO_RGB_AND_SHOW_VERBOSE:
                for(auto index = 0; index < filteredArgs.size(); index++) {
                    std::cout << index << " " << filteredArgs[index] << std::endl;
                }
                std::cout << std::endl;

            [[fallthrough]];
            case Commands::TO_RGB_AND_SHOW:

                for(auto const& arg : filteredArgs){
                    const auto color = Color::from_hex(arg);
                    const std::vector<RGB> gradient{color, color, color};

                    std::cout << "Hex: " << arg << " -> RGB: "
                    << Color::to_rgb(color) << ' '
                    << Font::print_as_block(gradient) << std::endl;
                }
                break;

            default:
                std::cout << "Unknown command: " << static_cast<std::uint16_t>(command) << std::endl;

                break;



        }
    }


};
