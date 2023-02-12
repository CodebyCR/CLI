//
// Created by Christoph Rohde on 07.02.23.
//

#pragma once


#include <iostream>
#include <experimental/coroutine>

struct ProgressBar {
    struct promise_type {
        uint index;

        auto initial_suspend() ->  std::experimental::suspend_always{ /*... */ return{};}

        auto final_suspend() noexcept -> std::experimental::suspend_always{ /*... */ return{};}

        auto get_return_object() -> ProgressBar { /*... */ }

        auto yield_value(int value) -> std::experimental::suspend_always {
            index = value;
            return{};
        }

        auto return_void() -> void { /*... */ }

        auto unhandled_exception() const -> void {
            std::cout << "unhandled_exception" << std::endl;
        }


    };
};

