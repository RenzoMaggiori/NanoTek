/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AndComponent
*/

#include "AndComponent.hpp"

nts::AndComponent::AndComponent()
{
    nts::pinType type = nts::pinType::INPUT;

    for (size_t i = 1; i < 4; i++) {
        if (i == 3)
            type = nts::pinType::OUTPUT;
        _pins[i].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i].second = type;
    }
}

void nts::AndComponent::simulate(std::size_t tick) {
    (void) tick;
    std::shared_ptr<nts::Tristate> status;

    if (*_pins[1].first.get() == Tristate::True && *_pins[2].first.get() == Tristate::True) {
        *_pins[3].first.get() = nts::Tristate::True;
        return;
    }
    if (*_pins[1].first.get() == Tristate::False || *_pins[2].first.get() == Tristate::False) {
        *_pins[3].first.get() = nts::Tristate::False;
        return;
    }
    *_pins[3].first.get() = nts::Tristate::Undefined;
}