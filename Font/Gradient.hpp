//
// Created by Christoph Rohde on 08.02.23.
//

#pragma once

#include <iostream>
#include <vector>
#include "RGB.hpp"
#include <cmath>

struct Gradient : public std::vector<RGB> {

    Gradient(RGB rgb1, RGB rgb2, ushort steps = 50) : std::vector<RGB>(renderGradient(rgb1, rgb2, steps)) {}

    [[nodiscard]]
    static auto renderGradient(RGB rgb1, RGB rgb2, ushort steps) -> std::vector<RGB>  {
        std::vector<RGB> gradient;
        const auto rStep = static_cast<float>(rgb2.red - rgb1.red) / steps;
        const auto gStep = static_cast<float>(rgb2.green - rgb1.green) / steps;
        const auto bStep = static_cast<float>(rgb2.blue - rgb1.blue) / steps;

        for (ushort i = 0; i <= steps; i++) {
            RGB rgb;
            rgb.red = static_cast<ushort>(round(rgb1.red +  rStep * i));
            rgb.green = static_cast<ushort>(round(rgb1.green + gStep * i));
            rgb.blue = static_cast<ushort>(round(rgb1.blue + bStep * i));
            gradient.push_back(rgb);
        }

        return gradient;
    }

};
