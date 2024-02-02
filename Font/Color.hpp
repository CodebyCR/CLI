//
// Created by Christoph Rohde on 07.02.23.
//

#pragma once

#include <iostream>
#include <sstream>
#include "RGB.hpp"

namespace Color{

    constexpr auto RED = RGB{255, 0, 0};
    constexpr auto GREEN = RGB{0, 255, 0};
    constexpr auto BLUE = RGB{0, 0, 255};
    constexpr auto YELLOW = RGB{255, 255, 0};
    constexpr auto CYAN = RGB{0, 255, 255};
    constexpr auto MAGENTA = RGB{255, 0, 255};
    constexpr auto WHITE = RGB{255, 255, 255};
    constexpr auto BLACK = RGB{0, 0, 0};
    constexpr auto GRAY = RGB{128, 128, 128};
    constexpr auto PINK = RGB{255, 192, 203};
    constexpr auto ORANGE = RGB{255, 165, 0};
    constexpr auto BROWN = RGB{165, 42, 42};
    constexpr auto PURPLE = RGB{128, 0, 128};
    constexpr auto LIME = RGB{0, 255, 0};
    constexpr auto MAROON = RGB{128, 0, 0};
    constexpr auto OLIVE = RGB{128, 128, 0};
    constexpr auto NAVY = RGB{0, 0, 128};
    constexpr auto TEAL = RGB{0, 128, 128};
    constexpr auto SILVER = RGB{192, 192, 192};
    constexpr auto AQUA = RGB{0, 255, 255};
    constexpr auto FUCHSIA = RGB{255, 0, 255};
    constexpr auto LAVENDER = RGB{230, 230, 250};
    constexpr auto TURQUOISE = RGB{64, 224, 208};
    constexpr auto DARK_RED = RGB{139, 0, 0};
    constexpr auto DARK_GREEN = RGB{0, 100, 0};
    constexpr auto DARK_BLUE = RGB{0, 0, 139};
    constexpr auto DARK_YELLOW = RGB{139, 139, 0};
    constexpr auto DARK_CYAN = RGB{0, 139, 139};
    constexpr auto DARK_WHITE = RGB{139, 139, 139};
    constexpr auto LIGHT_RED= RGB{.red = 255, .green = 128, .blue = 128 };
    constexpr auto INDIGO   = RGB{.red = 57, .green = 73, .blue = 171};
    constexpr auto LIGHT_GRAY = RGB{.red = 228, .green = 228, .blue = 228};
    constexpr auto DRIP_PURPLE = RGB{.red = 80, .green = 80, .blue = 210};
    constexpr auto LIGHT_PURPLE = RGB{.red = 150, .green = 150, .blue = 255};
    constexpr auto DARK_PURPLE = RGB{.red = 50, .green = 50, .blue = 150};


    [[nodiscard]]
    constexpr static auto from_hex(const std::uint32_t hex) -> RGB {
        auto r = static_cast<std::uint8_t>((hex & 0xFF0000) >> 16);
        auto g = static_cast<std::uint8_t>((hex & 0x00FF00) >> 8);
        auto b = static_cast<std::uint8_t>(hex & 0x0000FF);

        return RGB{r, g, b};
    }

    [[nodiscard]]
    [[nodiscard]]
    static auto from_hex(std::string_view hex_code) -> RGB{
        std::uint32_t hex;
        std::stringstream ss;

        if (hex_code[0] == '#') {
            ss << std::hex << hex_code.substr(1);
        } else {
            ss << std::hex << hex_code;
        }
        ss >> hex;

        return from_hex(hex);
    }

    [[nodiscard]]
    static auto from_rgb(std::string_view rgb) -> RGB {
        // rgb format:
        // 250,255,70
        // 3,255,0

        std::stringstream ss;
        ss << rgb;

        std::uint32_t r, g, b;
        char c;
        ss >> r >> c >> g >> c >> b;

        return RGB{static_cast<std::uint8_t>(r), static_cast<std::uint8_t>(g), static_cast<std::uint8_t>(b)};
    }

    [[nodiscard]]
    static auto to_num(const RGB &rgb) -> std::uint32_t {
        return (rgb.red << 16) | (rgb.green << 8) | rgb.blue;
    }

    [[nodiscard]]
    static auto to_hex(const RGB &rgb) -> std::string {
        std::stringstream ss;
        ss << std::hex << to_num(rgb);
        return ss.str();
    }

    [[nodiscard]]
    static auto to_rgb(const RGB &rgb) -> std::string {
        return std::to_string(rgb.red) + ", " + std::to_string(rgb.green) + ", " + std::to_string(rgb.blue);
    }


}
