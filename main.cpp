#include <iostream>
#include <sstream>
#include <string>
#include "Font/Background.hpp"
#include "Font/Foreground.hpp"
#include "Font/Format.hpp"
#include "Font/Underline.hpp"
#include "Font/Color.hpp"
#include "Font/Gradient.hpp"
#include <future>
#include <vector>
#include <cmath>

//auto print_with_pause(const char *text) -> void {
//    write(1, text, strlen(text));
//    usleep(210'000);
//}
//
//auto erase_last_line() -> void {
//    write(1, "\33[2K\r", 5);  // erase line and carriage return
//    write(1, "\33[1A", 4);    // move 1 line up
//    write(1, "\33[2K\r", 5);  // erase line and carriage return
//}


//std::future<void> print_with_pause(const std::string& text) {
//    return std::async(std::launch::async, [text] {
//        std::cout << text;
//        std::this_thread::sleep_for(std::chrono::milliseconds(210));
//    });
//}



auto renderGradient(RGB rgb1, RGB rgb2, int steps) -> std::vector<RGB>  {
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


auto print_progressbar_1(const int MAX_PROGRESS = 50){
    auto PURPLE = Color::PURPLE;
    auto BLUE = Color::NAVY;
    auto gradient = renderGradient(BLUE, PURPLE, MAX_PROGRESS);

    std::string progress;
    std::cout << "Progress 1:" << std::endl;

    for (ushort i = 0; i <= MAX_PROGRESS; i++) {
        auto red = static_cast<ushort>(i * 5);
        ushort blue = 250 - red;
        std::stringstream ss;

        ss      << Font::Background(gradient.at(i)) << std::string( i, ' ' )
                << Font::Background({.red = 120, .green = 120, .blue = 120}) << std::string( MAX_PROGRESS - i, ' ' )
                << Font::Format::RESET::ALL;
        progress = ss.str();
        ss.flush();

        auto progress2 = Font::Format::FRAMED +  progress + Font::Format::RESET::ALL;

        std::cout << '\r' << progress2 << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    std::cout << std::endl;
}

auto print_progressbar_2( Gradient gradient = {Color::PURPLE, Color::INDIGO},
                          const int MAX_PROGRESS = 50){

    std::cout << "\nProgress 2:" << std::endl;
    std::string pending;
    std::string progress;

    for (ushort i = 0; i <= MAX_PROGRESS; i++) {
        auto red = static_cast<ushort>(i * 5);
        ushort blue = 250 - red;
        std::stringstream ss;

        progress += Font::Background(gradient.at(i)) + " " + Font::Format::RESET::ALL;

        ss      << Font::Background(Color::GRAY) << std::string( MAX_PROGRESS - i, ' ' )
                << Font::Format::RESET::ALL;
        pending = ss.str();

        auto final_progress = progress + pending;

        std::cout << '\r' << final_progress.c_str() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    std::cout << std::endl;
}




auto print_progressbar_3( Gradient gradient = {Color::PURPLE, Color::INDIGO},
                          const int MAX_PROGRESS = 50){

    std::cout << "\nProgress 3:" << std::endl;
    std::string pending;
    std::string progress;

    const auto fileSize = 50;
    // fileSize as 100%
    const auto percent = (double) 100 / fileSize;


    ushort max = 0;
    for (int index = 0; index <= fileSize; index++) {
        const auto currentPercent = (int)(percent * (index ));

        auto compare = static_cast<ushort>(currentPercent /2);

        if( compare > max || index == 0) {
            max = compare;
            auto red = static_cast<ushort>(max * 5);
            ushort blue = 250 - red;
            std::stringstream ss;

            progress += Font::Background(gradient.at(max)) + " " + Font::Format::RESET::ALL;

            ss << Font::Background(Color::GRAY) << std::string(MAX_PROGRESS - max, ' ')
               << Font::Format::RESET::ALL;
            pending = ss.str();
        }

        std::cout << '\r' << progress << pending << ' ' << std::to_string(currentPercent) + '%' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

    }
    std::cout << std::endl;
}

auto print_progressbar_4( Gradient gradient = {Color::INDIGO, Color::DARK_CYAN},
                          const int MAX_PROGRESS = 50){

    std::cout << "\nProgress 4:" << std::endl;
    std::string pending;
    std::string progress;

    const auto fileSize = 50;
    // fileSize as 100%
    const auto percent = (double) 100 / fileSize;

    ushort max = 0;

for (int index = 0; index <= fileSize; index++) {
        const auto currentPercent = static_cast<int>(percent * (index ));


    if(auto compare = static_cast<ushort>(currentPercent /2);
        compare > max || index == 0) {

            max = compare;
            auto red = static_cast<ushort>(max * 5);
            ushort blue = 250 - red;
            std::stringstream ss;

            progress += Font::Foreground(gradient.at(max)) + "—" + Font::Format::RESET::ALL;


            ss << Font::Foreground(Color::GRAY) <<  std::string(MAX_PROGRESS - max, ' ')
               << Font::Format::RESET::ALL;
            pending = ss.str();
        }

        std::cout << '\r' << progress << pending << ' ' << std::to_string(currentPercent) + '%' << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

    }
    std::cout << std::endl;
}


auto main() -> int {


    auto PINK = Color::from_hex("#FFC0CB");
    auto GREEN = Color::from_hex("#00FF00");
    auto YELLOW = Color::from_hex("#FFFF00");
    auto ORANGE = Color::from_hex("#FFA500");

//    for (auto const& current_RGB : renderGradient(Color::BLUE, Color::INDIGO, 50)) {
//        std::cout << Font::Background(current_RGB) << ' ' << Font::Format::RESET::ALL;
//    }


    std::cout << std::endl;

    print_progressbar_1();

    print_progressbar_2();

    print_progressbar_3();

    print_progressbar_4();


    std::cout << "Press any key to continue... ";
    std::cin.get();


    auto RESET = Font::Format::RESET::ALL;
    auto MAX_PROGRESS = 50;


    std::cout << "Progress:" << std::endl;
    std::string progress2;

    for (ushort i = 0; i <= MAX_PROGRESS; i++) {
        auto red = static_cast<ushort>(i * 5);
        ushort blue = 250 - red;
        std::stringstream ss;

        ss << Font::Foreground({.red = red, .green = 0, .blue = blue}) << 'A' << RESET;
        progress2 += ss.str();
        ss.flush();

        std::cout << '\r' << progress2.c_str() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    std::cout << std::endl;


    std::cout << "Reset only Foreground color:" << std::endl;
    std::cout << Font::Foreground({})
                << Font::Background({.red=122, .green=122, .blue=122})
                << "This is an example text." << Font::RESET_FOREGROUND
                << "This is an example text." << RESET << std::endl;

    std::cout << "Reset only Background color:" << std::endl;
    std::cout << Font::Foreground({})
                << Font::Background({.red=122, .green=122, .blue=122})
                << "This is an example text." << Font::RESET_BACKGROUND
                << "This is an example text." << RESET << std::endl;


    std::cout << "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
                 "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl,"
                 " eget aliquam nisl nisl sit amet nisl. "
                 "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
                 << Font::Format::BOLD <<"\n" <<
                 "eget aliquam nisl nisl sit amet nisl. Donec auctor, nisl eget ultricies luctus, "
                 << Font::Format::ITALIC <<"\n" <<
                 "nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. Donec auctor, "
                    << Font::Format::UNDERLINED <<"\n" <<
                 "nisl eget ultricies luctus, nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. "
                    << Font::Format::BLINK <<"\n" <<
                 "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
                    << Font::Format::INVERTED <<"\n" <<
                 "eget aliquam nisl nisl sit amet nisl. Donec auctor, nisl eget ultricies luctus, "
                    << Font::Format::STRIKETHROUGH <<"\n" <<
                 "nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. Donec auctor, "
                 "nisl eget ultricies luctus, nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. "
                 << Font::Format::RESET::BOLD <<"\n" <<
                 "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
                    << Font::Format::RESET::ITALIC <<"\n" <<
                 "eget aliquam nisl nisl sit amet nisl. "
                    << Font::Format::RESET::UNDERLINED <<"\n" <<
                 "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
                    << Font::Format::RESET::BLINK << "\n" <<
                 "eget aliquam nisl nisl sit amet nisl. "
                    << Font::Format::RESET::INVERTED <<"\n" <<
                 "Donec auctor, nisl eget ultricies luctus, nisl nisl aliquam nisl, "
                    << Font::Format::RESET::STRIKETHROUGH <<"\n" <<
                 "eget aliquam nisl nisl sit amet nisl. Donec auctor, nisl eget ultricies luctus, "
                  << Font::Format::OVERLINE <<"\n" <<
                 "nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. Donec auctor, "
                  << Font::Format::FRAMED <<"\n" <<
                 "nisl eget ultricies luctus, nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. "
                    << Font::Format::ENCIRCLED <<"\n" <<
                 "Donec auctor, nisl eget ultricies luctus, "
                    << Font::Format::RESET::OVERLINE <<"\n" <<
                 "nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. Donec auctor, "
                    << Font::Format::RESET::FRAMED <<"\n" <<
                 "nisl eget ultricies luctus, nisl nisl aliquam nisl, eget aliquam nisl nisl sit amet nisl. "
                    << Font::Format::RESET::ENCIRCLED <<"\n" <<
                 "Done" << std::endl;


    std::cout << "\nProgress:" << std::endl;
    std::string progress3;

    for (ushort i = 0; i <= MAX_PROGRESS; i++) {
        auto red = static_cast<ushort>(i * 5);
        ushort blue = 250 - red;
        std::stringstream ss;

        ss << Font::Underline({.red = red, .green = 0, .blue = blue}) << 'A' << RESET;
        progress3 += ss.str();
        ss.flush();

        std::cout << '\r' << progress2.c_str() << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    std::cout << std::endl;

    return 0;
}
