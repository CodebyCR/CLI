//
// Created by Christoph Rohde on 08.02.23.
//

#pragma once

#include <iostream>
#include <vector>
#include "RGB.hpp"
#include <cmath>

struct Gradient : public std::vector<RGB> {

    Gradient(RGB rgb1, RGB rgb2, ushort steps) : std::vector<RGB>(renderGradient(rgb1, rgb2, steps)) {}

    auto renderGradient(RGB rgb1, RGB rgb2, ushort steps) const -> std::vector<RGB>  {
        std::vector<RGB> gradient;
        float rStep = (rgb2.red - rgb1.red) / (float)steps;
        float gStep = (rgb2.green - rgb1.green) / (float)steps;
        float bStep = (rgb2.blue - rgb1.blue) / (float)steps;

        for (int i = 0; i <= steps; i++) {
            RGB rgb;
            rgb.red = round(rgb1.red + rStep * i);
            rgb.green = round(rgb1.green + gStep * i);
            rgb.blue = round(rgb1.blue + bStep * i);
            gradient.push_back(rgb);
        }

        return gradient;
    }

};
