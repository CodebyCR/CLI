//
// Created by Christoph Rohde on 04.02.23.
//

#pragma once

#include <iostream>
#include <sstream>
#include "RGB.hpp"

namespace Font {

    class Background {

    private:
        std::uint8_t red;
        std::uint8_t green;
        std::uint8_t blue;

    public:

        constexpr explicit Background(RGB rgb) : red(rgb.red), green(rgb.green), blue(rgb.blue) {}

        ~Background() = default;

        // Copy and move constructors
        constexpr Background(const Background &other) = default;

        constexpr Background(Background &&other) noexcept = default;

        constexpr Background &operator=(const Background &other) = default;

        constexpr Background &operator=(Background &&other) noexcept = default;

        constexpr auto operator<=>(const Background &other) const = default;

        constexpr friend auto operator<<(std::ostream &os, Background background) -> std::ostream & {
//            printf(" Red: %d, Green: %d, Blue: %d\n", background.red, background.green, background.blue);
            os
            << "\033[48;2;"
            << (background.red   ? background.red   : 0) << ";"
            << (background.green ? background.green : 0) << ";"
            << (background.blue  ? background.blue  : 0) << "m";
            return os;
        }

        friend auto operator + (Background const &background, char const * const text)  {
            printf("Call + Background");
            return
            "\033[48;2;"
            + std::to_string(background.red ? background.red : 0) + ";"
            + std::to_string(background.green ? background.green : 0) + ";"
            + std::to_string(background.blue ? background.blue : 0) + "m" + text;
        }

        auto to_string() -> std::string {
            printf("Call to_string Background");
            return
            "\033[48;2;" + std::to_string(this->red) + ";"
            + std::to_string(this->green) + ";"
            + std::to_string(this->blue) + "m";
        }

    };

    constexpr auto RESET_BACKGROUND = "\033[49m";

    auto static print_as_block(std::vector<RGB> const& gradient) -> std::string {
        auto ss = std::stringstream();

        for (auto const& color : gradient) {
            ss << Background(color) << ' ';
        }
        ss << Font::RESET_BACKGROUND<< std::endl;
        return ss.str();
    }
}