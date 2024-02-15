/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** NotComponent
*/

#include "NotComponent.hpp"
#include <iostream>

nts::NotComponent::NotComponent() {
    nts::pinType type = nts::pinType::INPUT;

    for (size_t i = 1; i < 3; i++) {
        if (i == 2)
            type = nts::pinType::OUTPUT;
        std::shared_ptr<nts::Tristate> status = std::make_shared<nts::Tristate>(Tristate::Undefined);

        // Store the shared pointer and type in the pair associated with key 'i'
        _pins[i] = std::make_pair(status, type);
    }
}

nts::pinType nts::NotComponent::getPinType(std::size_t pin) {
    if (pin > 2 || pin < 1) throw nts::Error("Invalid pin.");
    return _pins[pin].second;
}

void nts::NotComponent::simulate(std::size_t tick) {
    (void) tick;
    std::shared_ptr<nts::Tristate> status;

    if (*_pins[1].first.get() == Tristate::True) {
        *_pins[2].first.get() = Tristate::False;
        return;
    }
    if (*_pins[1].first.get() == Tristate::False) {
        *_pins[2].first.get() = Tristate::True;
        return;
    }
    *_pins[2].first.get() = Tristate::Undefined;
}
