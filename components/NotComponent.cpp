/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** NotComponent
*/

#include "NotComponent.hpp"


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
        status = std::make_shared<nts::Tristate>(Tristate::False);
        _pins[2] = status;
        return;
    }
    if (*(_pins[1]) == Tristate::False) {
        status = std::make_shared<nts::Tristate>(Tristate::True);
        _pins[2] = status;
        return;
    }
        status = std::make_shared<nts::Tristate>(Tristate::Undefined);
    _pins[2] = status;
}
