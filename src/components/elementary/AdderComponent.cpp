/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** AdderComponent
*/

#include "AdderComponent.hpp"

nts::AdderComponent::AdderComponent() {
    nts::pinType type = nts::pinType::INPUT;

    for (size_t i = 1; i < 6; i++) {
        if (i == 5 || i == 4)
            type = nts::pinType::OUTPUT;
        std::shared_ptr<nts::Tristate> status;
        status = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i].first = status;
        _pins[i].second = type;
    }
}

void nts::AdderComponent::simulate(std::size_t tick) {
    (void)tick;

    Tristate inputA = *_pins[1].first.get();
    Tristate inputB = *_pins[2].first.get();
    Tristate carryIn = *_pins[3].first.get();

    Tristate sum, carryOut;
    if (inputA == Tristate::False && inputB == Tristate::False && carryIn == Tristate::False) {
        sum = Tristate::False;
        carryOut = Tristate::False;
    } else if (inputA == Tristate::False && inputB == Tristate::True && carryIn == Tristate::False) {
        sum = Tristate::True;
        carryOut = Tristate::False;
    } else if (inputA == Tristate::False && inputB == Tristate::False && carryIn == Tristate::True) {
        sum = Tristate::True;
        carryOut = Tristate::False;
    } else if (inputA == Tristate::False && inputB == Tristate::True && carryIn == Tristate::True) {
        sum = Tristate::False;
        carryOut = Tristate::True;
    } else if (inputA == Tristate::True && inputB == Tristate::False && carryIn == Tristate::False) {
        sum = Tristate::True;
        carryOut = Tristate::False;
    } else if (inputA == Tristate::True && inputB == Tristate::True && carryIn == Tristate::False) {
        sum = Tristate::False;
        carryOut = Tristate::True;
    } else if (inputA == Tristate::True && inputB == Tristate::False && carryIn == Tristate::True) {
        sum = Tristate::False;
        carryOut = Tristate::True;
    } else if (inputA == Tristate::True && inputB == Tristate::True && carryIn == Tristate::True) {
        sum = Tristate::True;
        carryOut = Tristate::True;
    } else {
        sum = Tristate::Undefined;
        carryOut = Tristate::Undefined;
    }

    *_pins[4].first.get() = carryOut;
    *_pins[5].first.get() = sum;
}
