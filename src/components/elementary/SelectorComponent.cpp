/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** SelectorComponent
*/

#include "SelectorComponent.hpp"

nts::SelectorComponent::SelectorComponent()
{
    nts::pinType type = nts::pinType::INPUT;

    for (size_t i = 1; i < 16; i++) {
        if (i == 14)
            type = nts::pinType::OUTPUT;
        else
            type = nts::pinType::INPUT;
        _pins[i].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i].second = type;
    }
}

void nts::SelectorComponent::simulate(std::size_t tick) {
    (void)tick;

    Tristate in_0 = *_pins[1].first.get();
    Tristate in_1 = *_pins[2].first.get();
    Tristate in_2 = *_pins[3].first.get();
    Tristate in_3 = *_pins[4].first.get();
    Tristate in_4 = *_pins[5].first.get();
    Tristate in_5 = *_pins[6].first.get();
    Tristate in_6 = *_pins[7].first.get();
    Tristate in_7 = *_pins[9].first.get();
    Tristate in_a = *_pins[11].first.get();
    Tristate in_b = *_pins[12].first.get();
    Tristate in_c = *_pins[13].first.get();
    Tristate inhibit = *_pins[10].first.get();
    Tristate enable = *_pins[15].first.get();

    Tristate out_data;

    if (enable == Tristate::True) {
        out_data = Tristate::Undefined;
    } else if (inhibit == Tristate::True ) {
        out_data = Tristate::False;
    } else {
        if (in_c == Tristate::False && in_b == Tristate::False && in_a == Tristate::False)
            out_data = in_0;
        else if (in_c == Tristate::False && in_b == Tristate::False && in_a == Tristate::True)
            out_data = in_1;
        else if (in_c == Tristate::False && in_b == Tristate::True && in_a == Tristate::False)
            out_data = in_2;
        else if (in_c == Tristate::False && in_b == Tristate::True && in_a == Tristate::True)
            out_data = in_3;
        else if (in_c == Tristate::True && in_b == Tristate::False && in_a == Tristate::False)
            out_data = in_4;
        else if (in_c == Tristate::True && in_b == Tristate::False && in_a == Tristate::True)
            out_data = in_5;
        else if (in_c == Tristate::True && in_b == Tristate::True && in_a == Tristate::False)
            out_data = in_6;
        else if (in_c == Tristate::True && in_b == Tristate::True && in_a == Tristate::True)
            out_data = in_7;
        else
            out_data = Tristate::Undefined;
    }

    *_pins[14].first.get() = out_data;
}

