//
// Created by Christoph Rohde on 04.02.23.
//

#pragma once

#include <iostream>
#include "RGB.hpp"

namespace Font {

    class Underline {

    private:
        ushort red;
        ushort green;
        ushort blue;

    public:

        constexpr explicit Underline(RGB rgb) : red(rgb.red), green(rgb.green), blue(rgb.blue) {}

        ~Underline() = default;

        // Copy and move constructors
        constexpr Underline(const Underline &other) = default;

        constexpr Underline(Underline &&other) noexcept = default;

        constexpr Underline &operator=(const Underline &other) = default;

        constexpr Underline &operator=(Underline &&other) noexcept = default;

        constexpr auto operator<=>(const Underline &other) const = default;

        constexpr friend auto operator<<(std::ostream &os, Underline const &background) -> std::ostream & {
            os << "\033[58;2;" << background.red << ";" << background.green << ";" << background.blue << "m";
            return os;
        }
    };

}
