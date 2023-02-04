//
// Created by Christoph Rohde on 04.02.23.
//

#pragma once

#include <iostream>
#include "RGB.hpp"

namespace Font {

    class Background {

    private:
        ushort red;
        ushort green;
        ushort blue;

    public:

        constexpr explicit Background(RGB rgb) : red(rgb.red), green(rgb.green), blue(rgb.blue) {}

        ~Background() = default;

        // Copy and move constructors
        constexpr Background(const Background &other) = default;

        constexpr Background(Background &&other) noexcept = default;

        constexpr Background &operator=(const Background &other) = default;

        constexpr Background &operator=(Background &&other) noexcept = default;

        constexpr auto operator<=>(const Background &other) const = default;

        constexpr friend auto operator<<(std::ostream &os, Background const &background) -> std::ostream & {
            os << "\033[48;2;" << background.red << ";" << background.green << ";" << background.blue << "m";
            return os;
        }

        friend auto operator + (Background const &background, char const * const text)  {
            return
            "\033[48;2;" + std::to_string(background.red)
            + ";" + std::to_string(background.green)
            + ";" + std::to_string(background.blue) + "m" + text;
        }
    };

    constexpr auto RESET_BACKGROUND = "\033[49m";
}