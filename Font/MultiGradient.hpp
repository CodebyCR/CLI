//
// Created by Christoph Rohde on 09.02.24.
//

#pragma once

#include "RGB.hpp"
#include "Gradient.hpp"
#include <iostream>
#include <vector>


struct MultiGradient: public std::vector<RGB> {

    MultiGradient(std::vector<RGB> const& colors, std::uint8_t const& steps) :
        std::vector<RGB>(renderMultiGradient(colors, steps)) {}

    [[nodiscard]]
    static auto renderMultiGradient(std::vector<RGB> const& colors, std::uint8_t const& steps) -> std::vector<RGB> {
        std::vector<RGB> multiGradient;
        const auto stepsPerColor = static_cast<std::uint8_t>(steps / (colors.size() + 0.5f));
        for (std::size_t i = 0; i < colors.size() - 1; i++) {
            std::vector<RGB> gradient = Gradient::renderGradient(colors[i], colors[i + 1], stepsPerColor);
            multiGradient.insert(multiGradient.end(), gradient.begin(), gradient.end());
        }
        return multiGradient;
    }

    /// static function to return a iterator
    /// for example in a for loop
    /// of the current RGB & the char in the text
    /// @param std::vector<RGB> const& colors
    /// @param std::string_view text
    static auto colorize_text(std::string_view text, std::vector<RGB> const& colors) -> std::vector<std::pair<RGB, char>> {
        std::vector<std::pair<RGB, char>> colorized_text;
        for (std::size_t i = 0; i < text.size(); i++) {
            colorized_text.emplace_back(colors[i % colors.size()], text[i]);
        }
        return colorized_text;
    }

    static auto gradient_colorize_text(std::string_view text, std::vector<RGB> const& colors) -> std::vector<std::pair<RGB, char>> {
        std::vector<RGB> multiGradient = renderMultiGradient(colors, text.size());
        std::vector<std::pair<RGB, char>> colorized_text;
        for (std::size_t i = 0; i < text.size(); i++) {
            colorized_text.emplace_back(multiGradient[i], text[i]);
        }
        return colorized_text;
    }

};
