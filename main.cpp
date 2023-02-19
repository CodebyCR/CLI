#include <iostream>
#include "Font/Background.hpp"
#include "Font/Foreground.hpp"
#include "Font/Format.hpp"
#include "Font/Underline.hpp"
#include "Font/Color.hpp"
#include "Font/Gradient.hpp"
#include <vector>
#include "Animation/Progress.hpp"



auto main(int argc, char* argv[]) -> int {

    const auto args = std::vector<std::string>(argv, argv + argc);

    std::cout << "\nArguments:" << std::endl;
    for (auto const &arg : args) {
        std::cout << arg << std::endl;
    }


    auto PINK = Color::from_hex("#FFC0CB");
    auto GREEN = Color::from_hex("#00FF00");
    auto YELLOW = Color::from_hex("#FFFF00");
    auto ORANGE = Color::from_hex("#FFA500");


    std::cout << std::endl;

//    Progress::print_progressbar_1();
//
//    Progress::print_progressbar_2();

    Progress::print_progressbar_3({YELLOW, GREEN});

    Progress::print_progressbar_4();


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
