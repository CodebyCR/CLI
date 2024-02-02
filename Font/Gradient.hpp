//
// Created by Christoph Rohde on 08.02.23.
//

#pragma once

#include <iostream>
#include <vector>
#include "RGB.hpp"
#include <cmath>

struct Gradient : public std::vector<RGB> {

    Gradient(RGB rgb1, RGB rgb2, std::uint8_t steps = 50) : std::vector<RGB>(renderGradient(rgb1, rgb2, steps)) {}

//    [[nodiscard]]
//    static auto renderGradient(RGB rgb1, RGB rgb2, std::uint8_t steps) -> std::vector<RGB>  {
//        std::vector<RGB> gradient;
//        const auto rStep = static_cast<float>(rgb2.red - rgb1.red) / steps;
//        const auto gStep = static_cast<float>(rgb2.green - rgb1.green) / steps;
//        const auto bStep = static_cast<float>(rgb2.blue - rgb1.blue) / steps;
//
//        for (std::int16_t i = 0; i <= steps; i++) {
//            RGB rgb;
//            rgb.red = static_cast<std::uint8_t>(round(rgb1.red +  rStep * i));
//            rgb.green = static_cast<std::uint8_t>(round(rgb1.green + gStep * i));
//            rgb.blue = static_cast<std::uint8_t>(round(rgb1.blue + bStep * i));
//            printf("Red: %d, Green: %d, Blue: %d\n", rgb.red, rgb.green, rgb.blue);
//            gradient.push_back(rgb);
//        }
//
//        return gradient;
//    }

    [[nodiscard]]
    static auto renderGradient(RGB source, RGB target, std::uint8_t steps) -> std::vector<RGB>  {
        /// steps for r,g & b can between -255 and 255 (white to black and vice versa)
        /// so we need to cast to int16_t to avoid overflow
        std::vector<RGB> gradient;
        const auto rStep = static_cast<float>((target.red - source.red) / steps);
        const auto gStep = static_cast<float>((target.green - source.green) / steps);
        const auto bStep = static_cast<float>((target.blue - source.blue) / steps);

        //printf("additions -> Red: %d, Green: %d, Blue: %d\n", rStep, gStep, bStep);

        for (std::uint8_t i = 0; i <= steps; i++) {
            RGB rgb;
            rgb.red = static_cast<std::uint8_t>(  round(source.red + rStep * i));
            rgb.green = static_cast<std::uint8_t>(round(source.green + gStep * i));
            rgb.blue = static_cast<std::uint8_t>( round(source.blue + bStep * i));
//            printf("Red: %d, Green: %d, Blue: %d\n", rgb.red, rgb.green, rgb.blue);
            gradient.push_back(rgb);
        }

        return gradient;
    }

};
