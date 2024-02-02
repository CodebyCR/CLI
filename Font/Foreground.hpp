//
// Created by Christoph Rohde on 04.02.23.
//

#pragma once

#include <iostream>
#include <sstream>
#include "RGB.hpp"

namespace Font {
    constexpr auto RESET_FOREGROUND = "\033[39m";

    class Foreground {

    private:
        std::uint8_t red;
        std::uint8_t green;
        std::uint8_t blue;

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
            << (foreground.red ? foreground.red : 0) << ";"
            << (foreground.green ? foreground.green : 0) << ";"
            << (foreground.blue ? foreground.blue : 0) << "m";
            return os;
        }

        friend auto operator + (Foreground const &foreground, char const * const text)  {
//            printf(" Red: %d, Green: %d, Blue: %d\n", foreground.red, foreground.green, foreground.blue);
            return
                    "\033[38;2;"
                    + std::to_string(foreground.red) + ";"
                    + std::to_string(foreground.green) + ";"
                    + std::to_string(foreground.blue) + "m"  + text;
        }

        auto to_string() -> std::string {
//            printf(" Red: %d, Green: %d, Blue: %d\n", this->red, this->green, this->blue);
            return
                    "\033[38;2;"
                    + std::to_string(this->red) + ";"
                    + std::to_string(this->green) + ";"
                    + std::to_string(this->blue) + "m";
        }





    };

    auto static print_as_line(std::vector<RGB> const& gradient) -> std::string {
        auto ss = std::stringstream();

        for (auto const& color : gradient) {
            ss << Foreground(color) << "—";
        }
        ss << Font::RESET_FOREGROUND << std::endl;
        return ss.str();
    }

}