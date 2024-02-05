/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** NandComponent
*/

#include "NandComponent.hpp"

nts::NandComponent::NandComponent() {
    for (size_t i = 1; i < 4; i++) {
        std::shared_ptr<nts::Tristate> status = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i] = status;
    }
}

nts::pinType nts::NandComponent::getPinType(std::size_t pin) {
    if (pin > 3 || pin < 1) throw Error("Invalid pin.");
    if (pin < 3)
        return pinType::INPUT;
    if (pin == 3)
        return pinType::OUTPUT;
    return pinType::NONE;
}

void nts::NandComponent::updateOutputPin() {
    std::shared_ptr<nts::Tristate> status;

    if (*(_pins[1]) == Tristate::True && *(_pins[2]) == Tristate::True) {
        status = std::make_shared<nts::Tristate>(Tristate::False);
        _pins[3] = status;
        return;
    }
    if (*(_pins[1]) == Tristate::False || *(_pins[2]) == Tristate::False) {
        status = std::make_shared<nts::Tristate>(Tristate::True);
        _pins[3] = status;
        return;
    }
    status = std::make_shared<nts::Tristate>(Tristate::Undefined);
    _pins[3] = status;
}

