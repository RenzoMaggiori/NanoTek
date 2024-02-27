/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** FlipflopComponent
*/

#include "FlipflopComponent.hpp"

nts::FlipflopComponent::FlipflopComponent()
{
    nts::pinType type = nts::pinType::INPUT;

    for (size_t i = 1; i < 7; i++) {
        if (i == 5)
            type = nts::pinType::OUTPUT;
        _pins[i].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i].second = type;
    }
}

void nts::FlipflopComponent::simulate(std::size_t tick) {
    (void)tick;
    Tristate clk = *_pins[1].first.get();
    Tristate d = *_pins[2].first.get();
    Tristate set = *_pins[3].first.get();
    Tristate reset = *_pins[4].first.get();
    Tristate q_prev = *_pins[5].first.get();
    Tristate qbar_prev = *_pins[6].first.get();

    Tristate q = Tristate::Undefined;
    Tristate qbar = Tristate::Undefined;

    if (set == Tristate::True && reset == Tristate::False) {
        q = Tristate::True;
        qbar = Tristate::False;
    } else if (set == Tristate::True && reset == Tristate::True) {
        q = Tristate::True;
        qbar = Tristate::True;
    } else if (reset == Tristate::True && set == Tristate::False)  {
        q = Tristate::False;
        qbar = Tristate::True;
    } else if (clk == Tristate::True) {
        q = d;
        qbar = (d == Tristate::True) ? Tristate::False : Tristate::True;
    } else {
        q = q_prev;
        qbar = qbar_prev;
    }

    *_pins[5].first.get() = q;
    *_pins[6].first.get() = qbar;
}


