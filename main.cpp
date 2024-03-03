#include "Font/Background.hpp"
#include "Font/Foreground.hpp"
#include "Font/Format.hpp"
#include "Font/Underline.hpp"
#include "Font/Color.hpp"
#include "Font/Gradient.hpp"
#include "Font/MultiGradient.hpp"
#include "Animation/Progress.hpp"


#include <iostream>
#include <vector>
#include "extern/Command-Liner/src/CommandHandler.hpp"
#include "extern/Command-Liner/src/Option.hpp"
#include "extern/Command-Liner/src/ReservedOptions.hpp"

namespace OptionIds {

    constexpr std::uint64_t TO_HEX_ID {0x0000'1001};
    constexpr std::uint64_t TO_RGB_ID {0x0010'0001};
    constexpr std::uint64_t SHOW {0x0000'0101};
//    EXIT    = 0000'0000,
//    HELP    = 0000'0001,
//    VERBOSE = 0000'0010,
//    VERSION = 0000'0011,
//    SHOW    = 0000'0101,
//    TO_HEX  = 0000'1001,
//    TO_DEC  = 0001'0001,
//    TO_RGB  = 0010'0001,
//
//    /// Combined commands
//    TO_HEX_AND_SHOW = 0000'1101,
//    TO_DEC_AND_SHOW = 0001'0101,
//    TO_RGB_AND_SHOW = 0010'0101,
//
//    /// With verbose
//    TO_HEX_AND_VERBOSE = 0000'1011,
//    TO_DEC_AND_VERBOSE = 0001'0011,
//    TO_RGB_AND_VERBOSE = 0010'0011,
//
//    TO_HEX_AND_SHOW_VERBOSE = 0000'1111,
//    TO_DEC_AND_SHOW_VERBOSE = 0001'0111,
//    TO_RGB_AND_SHOW_VERBOSE = 0010'0111
};

enum class ColorEnum : std::int32_t {
    PINK = 0xFFC0CB,
    GREEN = 0x00FF00,
    ORANGE = 0xFFA500,
    YELLOW = 0xFFFF00,
    PURPLE = 0x800080,
    BLUE = 0x0000FF,
    RED = 0xFF0000,
    BLACK = 0x000000,
    WHITE = 0xFFFFFF,
    GRAY = 0x808080,
    BROWN = 0xA52A2A,
    LIME = 0x00FF00,
};


auto enum_to_rgb(ColorEnum color) -> RGB {
    return Color::from_hex(static_cast<std::int32_t>(color));
}

auto gradientColor() -> void {
    auto rainbowColors = std::vector<RGB>{Color::RED,    Color::ORANGE,
                                          Color::YELLOW, Color::GREEN,
                                          Color::BLUE,   Color::PURPLE};

    for(auto const& [color, symbol] : MultiGradient::colorize_text("Hello World from C++", rainbowColors)) {
        std::cout << Font::Foreground(Color::brighter(color, 2)) << symbol << Font::Format::RESET::ALL;
    }
}

static auto print_brand() -> std::string {
    constexpr auto brand =  "    CLI Tools • since 2023 •\n"
                            "    Version: 0.8.0\n"
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


auto main(int argc, char *argv[]) -> int {

    const auto args = std::vector<std::string>(argv, argv + argc);

    Option versionOption{
        .id = ReservedOptions::VERSION_ID,
        .verboseName = "--version",
        .quickName = "-v",
        .description = "Prints the version of the program.",
        .function = []([[maybe_unused]]std::vector<std::string> const& args) {
            std::cout << print_brand() << std::endl;
        }
    };

    Option toHexOption{
        .id = OptionIds::TO_HEX_ID,
        .verboseName = "--hex",
        .quickName = "-x",
        .description = "Converts a RGB color to a hex color.",
        .function = [](std::vector<std::string> const& args) {
            for(auto const& arg : args){
                const auto color = Color::from_rgb(arg);
                std::cout << arg << " -> Hex: #" << Color::to_hex(color) << std::endl;
            }
        }
    };

    Option toRgbOption{
        .id = OptionIds::TO_RGB_ID,
        .verboseName = "--rgb",
        .quickName = "-r",
        .description = "Converts a hex color to a RGB color.",
        .function = [](std::vector<std::string> const& args) {
            for(auto const& arg : args){
                const auto color = Color::from_hex(arg);
                std::cout << arg << " -> RGB: " << Color::to_rgb(color) << std::endl;
            }
        }
    };

    Option showOption{
        .id = OptionIds::SHOW,
        .verboseName = "--show",
        .quickName = "-s",
        .description = "Shows a color in the terminal.",
        .function = [](std::vector<std::string> const& args) {
            for(auto const& arg : args){
                const auto color = Color::from_rgb(arg);
                std::cout << arg << " -> " << Font::print_as_block({color}) << std::endl;
            }
        }
    };

    Option toHexAndShowOption{
        .id = OptionIds::TO_HEX_ID | OptionIds::SHOW,
        .verboseName = "--hex-and-show",
        .quickName = "-xs",
        .description = "Converts a RGB color to a hex color and shows it in the terminal.",
        .function = [](std::vector<std::string> const& args) {
            for(auto const& arg : args){
                const auto color = Color::from_rgb(arg);
                const std::vector<RGB> gradient{color, color, color};

                std::cout << "RGB: " << arg
                          << " -> Hex: #" << Color::to_hex(color) << ' '
                          << Font::print_as_block(gradient) << std::endl;
            }

        }
    };

    Option toRgbAndShowOption{
        .id = OptionIds::TO_RGB_ID | OptionIds::SHOW,
        .verboseName = "--rgb-and-show",
        .quickName = "-rs",
        .description = "Converts a hex color to a RGB color and shows it in the terminal.",
        .function = [](std::vector<std::string> const& args) {
            for(auto const& arg : args){
                const auto color = Color::from_hex(arg);
                const std::vector<RGB> gradient{color, color, color};

                std::cout << "Hex: " << arg << " -> RGB: "
                          << Color::to_rgb(color) << ' '
                          << Font::print_as_block(gradient) << std::endl;
            }
        }
    };

    CommandHandler commandHandler(args);
    commandHandler.add(versionOption);
    commandHandler.add(toHexOption);
    commandHandler.add(toRgbOption);
    commandHandler.add(showOption);
    commandHandler.add(toHexAndShowOption);
    commandHandler.add(toRgbAndShowOption);
    commandHandler.execute();

//    auto colorVector = std::vector<RGB>{Color::RED, Color::GREEN, Color::BLUE, Color::YELLOW, Color::ORANGE, Color::PINK};
//    auto gradient = MultiGradient(colorVector, 50);


    // CommandHandler commandHandler(argv, argv + argc);
    // commandHandler.add(helpCommand);
    // commandHandler.addManual("The Manual of the program."
    //                          "This is a very long description about the program."
    //                          "This is a very long description about the program.");
    // commandHandler.execute_args();

    // predefined commands (vielleicht letztes byte einnehmen)
    // --exit       -> 0
    // --help       -> 1
    // --manual     -> 2
    // --version    -> 3
    // --verbose    -> 4







    return 0;

//    process_args(args);

//    CLI::map_to_command(args);

    // example cli usage:
    // ./cli --hex 0,255,0      -> #00FF00
    // ./cli --rgb #00FF00      -> 0,255,0
    // ./cli --help             -> print help
    // ./cli --version          -> print brand
    // ./cli --show 0,255,0     -> 0,255,0 (and color in terminal)
    // ./cli -sr #00FF00        -> 0,255,0 (and color in terminal)


    //    const auto path = std::filesystem::path("/Users/christoph_rohde/Downloads");
//    const auto iter = std::filesystem::recursive_directory_iterator(
//            path, std::filesystem::directory_options::skip_permission_denied);
//
//    const auto files = std::vector<std::filesystem::path>(begin(iter), end(iter));
//
//    auto extension_set = std::set<std::string, std::less<>>();
//    for (auto const &entry: files) {
//        extension_set.emplace(entry.extension());
//    }
//
//    for (auto const &set_entry: extension_set) {
//        std::cout << set_entry << std::endl;
//    }

    auto lime = enum_to_rgb(ColorEnum::BLUE);


//    auto PINK   = Color::from_hex("#FFC0CB");
//    auto GREEN  = Color::from_hex("#00FF00");
//    auto YELLOW = Color::from_hex("#FFFF00");
//    auto ORANGE = Color::from_hex("#FFA500");


//    Progress::print_progressbar_1();
//
//    Progress::print_progressbar_2();

//    Progress::print_progressbar_3({Color::WHITE, Color::BLACK});
//
//    Progress::print_progressbar_3({Color::BLACK, Color::WHITE});

//    Progress::print_progressbar_3({lime, Color::DRIP_PURPLE});

    Progress::print_progressbar_4();


    std::cout << "Press any key to continue... ";
    std::cin.get();


    auto RESET = Font::Format::RESET::ALL;
    auto MAX_PROGRESS = 50;


    std::cout << "Progress:" << std::endl;
    std::string progress2;

    for (std::uint8_t i = 0; i <= MAX_PROGRESS; i++) {
        auto red = static_cast<std::uint8_t>(i * 5);
        std::uint8_t blue = 255 - red;
        std::stringstream ss;

        ss << Font::Foreground({.red = red, .green = 0, .blue = blue}) << 'A' << RESET;
        progress2 += ss.str();
        ss.flush();

        std::cout << '\r' << progress2.c_str() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    std::cout << std::endl;


    std::cout << "Reset only Foreground color:" << std::endl;
    std::cout << Font::Foreground({})
              << Font::Background({.red=122, .green=122, .blue=122})
              << "This is an example text." << Font::RESET_FOREGROUND
              << "This is an example text." << RESET << std::endl;

    std::cout << "Reset only Background color:" << std::endl;
    std::cout << Font::Foreground({})
              << Font::Background({.red=122, .green=122, .blue=122})
              << "This is an example text." << Font::RESET_BACKGROUND
              << "This is an example text." << RESET << std::endl;


    std::cout << "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
                 "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl,"
                 " eget aliquam nisl nisl sit amet nisl. "
                 "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
              << Font::Format::BOLD << "\n" <<
              "eget aliquam nisl nisl sit amet nisl. Donec auctor, nisl eget ultricies luctus, "
              << Font::Format::ITALIC << "\n" <<
              "nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. Donec auctor, "
              << Font::Format::UNDERLINED << "\n" <<
              "nisl eget ultricies luctus, nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. "
              << Font::Format::BLINK << "\n" <<
              "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
              << Font::Format::INVERTED << "\n" <<
              "eget aliquam nisl nisl sit amet nisl. Donec auctor, nisl eget ultricies luctus, "
              << Font::Format::STRIKETHROUGH << "\n" <<
              "nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. Donec auctor, "
              "nisl eget ultricies luctus, nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. "
              << Font::Format::RESET::BOLD << "\n" <<
              "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
              << Font::Format::RESET::ITALIC << "\n" <<
              "eget aliquam nisl nisl sit amet nisl. "
              << Font::Format::RESET::UNDERLINED << "\n" <<
              "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
              << Font::Format::RESET::BLINK << "\n" <<
              "eget aliquam nisl nisl sit amet nisl. "
              << Font::Format::RESET::INVERTED << "\n" <<
              "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
              << Font::Format::RESET::STRIKETHROUGH << "\n" <<
              "eget aliquam nisl nisl sit amet nisl. Donec auctor, nisl eget ultricies luctus, "
              << Font::Format::OVERLINE << "\n" <<
              "nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. Donec auctor, "
              << Font::Format::FRAMED << "\n" <<
              "nisl eget ultricies luctus, nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. "
              << Font::Format::ENCIRCLED << "\n" <<
              "Donec auctor, nisl eget ultricies luctus, "
              << Font::Format::RESET::OVERLINE << "\n" <<
              "nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. Donec auctor, "
              << Font::Format::RESET::FRAMED << "\n" <<
              "nisl eget ultricies luctus, nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. "
              << Font::Format::RESET::ENCIRCLED << "\n" <<
              "Done" << std::endl;


    std::cout << "\nProgress:" << std::endl;
    std::string progress3;

    for (std::uint8_t i = 0; i <= MAX_PROGRESS; i++) {
        auto red = static_cast<std::uint8_t>(i * 5);
        std::uint8_t blue = 250 - red;
        std::stringstream ss;

        ss << Font::Underline({.red = red, .green = 0, .blue = blue}) << 'A' << RESET;
        progress3 += ss.str();
        ss.flush();

        std::cout << '\r' << progress2.c_str() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    std::cout << std::endl;

    return 0;
}


