//
// Created by Christoph Rohde on 07.02.23.
//

#pragma once

#include <iostream>
#include <sstream>
#include "RGB.hpp"
#include "RGBA.hpp"

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
    constexpr auto GOLD = RGB{255, 215, 0};
    constexpr auto SILVER = RGB{192, 192, 192};
    constexpr auto FRESH_ORANGE = RGB{.red = 255, .green = 102, .blue = 77};
    constexpr auto BROWN = RGB{165, 42, 42};
    constexpr auto PURPLE = RGB{128, 0, 128};
    constexpr auto LIME = RGB{0, 255, 0};
    constexpr auto MAROON = RGB{128, 0, 0};
    constexpr auto OLIVE = RGB{128, 128, 0};
    constexpr auto NAVY = RGB{0, 0, 128};
    constexpr auto TEAL = RGB{0, 128, 128};
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
    constexpr auto SPACE_INDIGO = RGB{.red = 50, .green =70, .blue = 133};


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

        std::uint32_t red;
        std::uint32_t green;
        std::uint32_t b;
        char c;
        ss >> red >> c >> green >> c >> b;

        return RGB{static_cast<std::uint8_t>(red), static_cast<std::uint8_t>(green), static_cast<std::uint8_t>(b)};
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

    /// Brither color
    [[nodiscard]]
    static auto brighter(const RGB &rgb, std::uint8_t times = 1) -> RGB {
        const auto rawRed = rgb.red + 32 * times;
        const auto rawGreen = rgb.green + 32 * times;
        const auto rawBlue = rgb.blue + 32 * times;

        return RGB{
                static_cast<std::uint8_t>(rawRed > 255 ? 255 : rawRed),
                static_cast<std::uint8_t>(rawGreen > 255 ? 255 : rawGreen),
                static_cast<std::uint8_t>(rawBlue > 255 ? 255 : rawBlue)
        };
    }

    /// Darker color
    [[nodiscard]]
    static auto darker(const RGB &rgb) -> RGB {
        const auto rawRed = rgb.red - 32;
        const auto rawGreen = rgb.green - 32;
        const auto rawBlue = rgb.blue - 32;

        return RGB{
                static_cast<std::uint8_t>(rawRed < 0 ? 0 : rawRed),
                static_cast<std::uint8_t>(rawGreen < 0 ? 0 : rawGreen),
                static_cast<std::uint8_t>(rawBlue < 0 ? 0 : rawBlue)
        };
    }

    /// Invert color
    [[nodiscard]]
    static auto invert(const RGB &rgb) -> RGB {
        return RGB{
                static_cast<std::uint8_t>(255 - rgb.red),
                static_cast<std::uint8_t>(255 - rgb.green),
                static_cast<std::uint8_t>(255 - rgb.blue)
        };
    }

    /// Mix two colors (maybe with | operator)
    [[nodiscard]]
    static auto mix(const RGB &a, const RGB &b) -> RGB {
        return RGB{
                static_cast<std::uint8_t>((a.red + b.red) / 2),
                static_cast<std::uint8_t>((a.green + b.green) / 2),
                static_cast<std::uint8_t>((a.blue + b.blue) / 2)
        };
    }

    /// Interpolate two colors
    [[nodiscard]]
    static auto interpolate(const RGB &a, const RGB &b, float t) -> RGB {
        return RGB{
                static_cast<std::uint8_t>(a.red + (b.red - a.red) * t),
                static_cast<std::uint8_t>(a.green + (b.green - a.green) * t),
                static_cast<std::uint8_t>(a.blue + (b.blue - a.blue) * t)
        };
    }

    /// Convert to grayscale
    [[nodiscard]]
    static auto to_grayscale(const RGB &rgb) -> RGB {
        auto gray = static_cast<std::uint8_t>((rgb.red + rgb.green + rgb.blue) / 3);
        return RGB{gray, gray, gray};
    }

    /// Convert to sepia
    [[nodiscard]]
    static auto to_sepia(const RGB &rgb) -> RGB {
        auto r = static_cast<std::uint8_t>(rgb.red * 0.393 + rgb.green * 0.769 + rgb.blue * 0.189);
        auto g = static_cast<std::uint8_t>(rgb.red * 0.349 + rgb.green * 0.686 + rgb.blue * 0.168);
        auto b = static_cast<std::uint8_t>(rgb.red * 0.272 + rgb.green * 0.534 + rgb.blue * 0.131);
        return RGB{r, g, b};
    }

    /// to RGBA
    [[nodiscard]]
    static auto to_rgba(const RGB &rgb, std::uint8_t alpha) -> RGBA {
        return RGBA{rgb.red, rgb.green, rgb.blue, alpha};
    }


}
