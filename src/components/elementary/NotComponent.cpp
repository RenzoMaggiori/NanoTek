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
    std::shared_ptr<nts::Tristate> status;
    for (size_t i = 1; i < 3; i++) {
        if (i == 2)
            type = nts::pinType::OUTPUT;
        status = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i] = std::make_pair(status, type);
    }
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
