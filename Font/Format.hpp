//
// Created by Christoph Rohde on 04.02.23.
//

#pragma once

namespace Font{
    namespace Format {
        constexpr auto BOLD = "\033[1m";
        constexpr auto DIM = "\033[2m";
        constexpr auto ITALIC = "\033[3m";
        constexpr auto UNDERLINED = "\033[4m";
        constexpr auto BLINK = "\033[5m";
        constexpr auto INVERTED = "\033[7m";
        constexpr auto HIDDEN = "\033[8m";
        constexpr auto STRIKETHROUGH = "\033[9m";
        constexpr auto OVERLINE = "\033[53m";
        constexpr auto FRAMED = "\033[51m";
        constexpr auto ENCIRCLED = "\033[52m";



        namespace RESET {
            constexpr auto ALL = "\033[0m";
            constexpr auto BOLD = "\033[21m";
            constexpr auto DIM = "\033[22m";
            constexpr auto ITALIC = "\033[23m";
            constexpr auto UNDERLINED = "\033[24m";
            constexpr auto BLINK = "\033[25m";
            constexpr auto INVERTED = "\033[27m";
            constexpr auto HIDDEN = "\033[28m";
            constexpr auto STRIKETHROUGH = "\033[29m";
            constexpr auto OVERLINE = "\033[55m";
            constexpr auto FRAMED = "\033[54m";
            constexpr auto ENCIRCLED = "\033[54m";
        }
    }
}
