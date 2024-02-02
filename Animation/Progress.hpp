//
// Created by Christoph Rohde on 07.02.23.
//

#pragma once


#include <iostream>
#include <thread>
#include <sstream>
#include "../Font/Gradient.hpp"
#include "../Font/Foreground.hpp"
#include "../Font/Background.hpp"
#include "../Font/Color.hpp"
#include "../Font/Gradient.hpp"
#include "../Font/Format.hpp"


namespace Progress {

    auto print_progressbar_1(const std::uint8_t MAX_PROGRESS = 50) {
        auto PURPLE = Color::PURPLE;
        auto BLUE = Color::NAVY;
        auto gradient = Gradient(BLUE, PURPLE, MAX_PROGRESS);

        std::cout << "Progress 1:" << std::endl;

        for (std::uint8_t i = 0; i <= MAX_PROGRESS; i++) {
            std::stringstream ss;

            ss << Font::Background(gradient.at(i)) << std::string(i, ' ')
               << Font::Background({.red = 120, .green = 120, .blue = 120}) << std::string(MAX_PROGRESS - i, ' ')
               << Font::Format::RESET::ALL;
            std::string progress = ss.str();
            ss.flush();

            auto progress2 = Font::Format::FRAMED + progress + Font::Format::RESET::ALL;

            std::cout << '\r' << progress2 << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        std::cout << std::endl;
    }

    auto print_progressbar_2(Gradient gradient = {Color::PURPLE, Color::INDIGO},
                             const int MAX_PROGRESS = 50) {

        std::cout << "\nProgress 2:" << std::endl;

        std::string progress;

        for (std::uint8_t i = 0; i <= MAX_PROGRESS; i++) {
            std::stringstream ss;

            progress += Font::Background(gradient.at(i)) + " " + Font::Format::RESET::ALL;

            ss << Font::Background(Color::GRAY) << std::string(MAX_PROGRESS - i, ' ')
               << Font::Format::RESET::ALL;
            std::string pending = ss.str();
            ss.flush();

            std::cout << '\r' << progress << pending << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        std::cout << std::endl;
    }


    auto print_progressbar_3(Gradient const& gradient = {Color::PURPLE, Color::INDIGO},
                             const std::uint8_t MAX_PROGRESS = 50) {

        std::cout << "\nProgress 3:" << std::endl;
        std::string pending;
        std::string progress;

        const auto fileSize = 50;
        // fileSize as 100%
        const auto percent = (double) 100 / fileSize;


        std::uint8_t max = 0;
        for (int index = 0; index <= fileSize; index++) {
            const auto currentPercent = (int) (percent * index);

            auto compare = static_cast<std::uint8_t>(currentPercent / 2);

            if (compare > max || index == 0) {
                max = compare;
                std::stringstream ss;

                progress += Font::Background(gradient.at(max)) + " " + Font::Format::RESET::ALL;

                ss << Font::Background(Color::GRAY) << std::string(MAX_PROGRESS - max, ' ')
                   << Font::Format::RESET::ALL;
                pending = ss.str();
                ss.flush();
            }

            std::cout << '\r' << progress << pending << ' ' << std::to_string(currentPercent) << '%' << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));

        }
        std::cout << std::endl;
    }

    auto print_progressbar_4(Gradient const& gradient = {Color::INDIGO, Color::DARK_CYAN},
                             const std::uint8_t MAX_PROGRESS = 50) {

        std::cout << "\nProgress 4:" << std::endl;
        std::string pending;
        std::string progress;


        const auto fileSize = 500;
        // fileSize as 100%
        const auto percent = (double) 100 / fileSize;

        std::uint8_t max = 0;

        for (int index = 0; index <= fileSize; index++) {
            const auto currentPercent = static_cast<int>(percent * index);


            if (const auto compare = static_cast<std::uint8_t>(currentPercent / 2);
                    compare > max || index == 0) {

                max = compare;
                std::stringstream ss;

                progress += Font::Foreground(gradient.at(max)) + "—" + Font::Format::RESET::ALL;


                ss << Font::Foreground(Color::GRAY) << std::string(MAX_PROGRESS - max, ' ')
                   << Font::Format::RESET::ALL;
                pending = ss.str();
            }

            std::cout << '\r' << progress << pending << ' ' << std::to_string(currentPercent) << '%' << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));

        }
        std::cout << std::endl;
    }

}
