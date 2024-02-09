/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AndComponent
*/

#include "AndComponent.hpp"

nts::AndComponent::AndComponent() {
    nts::pinType type = nts::pinType::INPUT;

    for (size_t i = 1; i < 4; i++) {
        if (i == 3)
            type = nts::pinType::OUTPUT;
        std::shared_ptr<nts::Tristate> status;
        status = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i].first = status;
        _pins[i].second = type;
    }
}

nts::pinType nts::AndComponent::getPinType(std::size_t pin) {
    if (pin > 3 || pin < 1) throw Error("Invalid pin.");
    return _pins[pin].second;
}

void nts::AndComponent::updateOutputPin() {
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