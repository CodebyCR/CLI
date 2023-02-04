#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include "Font/Background.hpp"
#include "Font/Foreground.hpp"
#include "Font/Format.hpp"
#include "Font/Underline.hpp"

auto print_with_pause(const char *text) -> void {
    write(1, text, strlen(text));
    usleep(210'000);
}

auto erase_last_line() -> void {
    write(1, "\33[2K\r", 5);  // erase line and carriage return
    write(1, "\33[1A", 4);    // move 1 line up
    write(1, "\33[2K\r", 5);  // erase line and carriage return
}

auto print_progressbar_1(const int MAX_PROGRESS = 50){

    std::string progress;
    std::cout << "Progress 1:" << std::endl;

    for (ushort i = 0; i <= MAX_PROGRESS; i++) {
        auto red = static_cast<ushort>(i * 5);
        ushort blue = 250 - red;
        std::stringstream ss;

        ss
                << Font::Background({.red = red, .green = 0, .blue = blue}) << std::string( i, ' ' )
                << Font::Background({.red = 120, .green = 120, .blue = 120}) << std::string( MAX_PROGRESS - i, ' ' )
                << Font::Format::RESET::ALL;
        progress = ss.str();
        ss.flush();

        auto progress2 = Font::Format::FRAMED +  progress + Font::Format::RESET::ALL;

        print_with_pause(progress2.c_str());
        erase_last_line();
    }
    std::cout << std::endl;
}

auto print_progressbar_2(const int MAX_PROGRESS = 50){

    std::cout << "Progress 2:" << std::endl;
    std::string pending;
    std::string progress;

    for (ushort i = 0; i <= MAX_PROGRESS; i++) {
        auto red = static_cast<ushort>(i * 5);
        ushort blue = 250 - red;
        std::stringstream ss;

        progress += Font::Background({.red = red, .green = 0, .blue = blue}) + " " + Font::Format::RESET::ALL;

        ss      << Font::Background({.red = 120, .green = 120, .blue = 120}) << std::string( MAX_PROGRESS - i, ' ' )
                << Font::Format::RESET::ALL;
        pending = ss.str();
//        ss.flush();

        auto final_progress = progress + pending;

//        auto progress2 = Font::Format::FRAMED + final_progress + RESET;


        print_with_pause(final_progress.c_str());
        erase_last_line();
    }
    std::cout << std::endl;
}

auto main() -> int {

    print_progressbar_1();

    print_progressbar_2();


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

        print_with_pause(progress2.c_str());
        erase_last_line();
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

        print_with_pause(progress3.c_str());
        erase_last_line();
    }
    std::cout << std::endl;

    return 0;
}
