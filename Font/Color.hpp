//
// Created by Christoph Rohde on 07.02.23.
//

#pragma once

#include <iostream>
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

}
