/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** NotComponent
*/

#include "NotComponent.hpp"
#include <iostream>

nts::NotComponent::NotComponent() {
    for (size_t i = 1; i < 3; i++) {
        std::shared_ptr<nts::Tristate> status = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i] = status;
    }
}

nts::pinType nts::NotComponent::getPinType(std::size_t pin) {
    if (pin > 2 || pin < 1) throw Error("Invalid pin.");
    if (pin == 1)
        return pinType::INPUT;
    if (pin == 2)
        return pinType::OUTPUT;
    return pinType::NONE;
}

void nts::NotComponent::updateOutputPin() {
    std::shared_ptr<nts::Tristate> status;

    if (*(_pins[1]) == Tristate::True) {
        *_pins[2].get() = Tristate::False;
        return;
    }
    if (*(_pins[1]) == Tristate::False) {
        *_pins[2].get() = Tristate::True;
        return;
    }
    *_pins[2].get() = Tristate::Undefined;
}
