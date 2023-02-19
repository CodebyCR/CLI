//
// Created by Christoph Rohde on 04.02.23.
//

#pragma once

#include <iostream>
#include "RGB.hpp"

namespace Font {

    class Foreground {

    private:
        ushort red;
        ushort green;
        ushort blue;

    public:

        constexpr explicit Foreground(RGB rgb) : red(rgb.red), green(rgb.green), blue(rgb.blue) {}

        ~Foreground() = default;

        // Copy and move constructors
        constexpr Foreground(const Foreground &other) = default;

        constexpr Foreground(Foreground &&other) noexcept = default;

        constexpr Foreground &operator=(const Foreground &other) = default;

        constexpr Foreground &operator=(Foreground &&other) noexcept = default;

        constexpr auto operator<=>(const Foreground &other) const = default;

        constexpr friend auto operator<<(std::ostream &os, Foreground const &foreground) -> std::ostream & {
            os << "\033[38;2;"
            << foreground.red << ";"
            << foreground.green << ";"
            << foreground.blue << "m";
            return os;
        }

        friend auto operator + (Foreground const &foreground, char const * const text)  {
            return
                    "\033[38;2;"
                    + std::to_string(foreground.red) + ";"
                    + std::to_string(foreground.green) + ";"
                    + std::to_string(foreground.blue) + "m"  + text;
        }

        auto to_string() -> std::string {
            return
                    "\033[38;2;"
                    + std::to_string(this->red) + ";"
                    + std::to_string(this->green) + ";"
                    + std::to_string(this->blue) + "m";
        }

    };


    constexpr auto RESET_FOREGROUND = "\033[39m";
}