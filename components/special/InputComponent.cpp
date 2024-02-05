/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

nts::InputComponent::InputComponent() {
    std::shared_ptr<nts::Tristate> status = std::make_shared<nts::Tristate>(Tristate::Undefined);
    this->getPins()[1] = status;
    _type = pinType::INPUT;

}

nts::pinType nts::InputComponent::getPinType(std::size_t pin) {
    if (pin != 1) throw Error("Invalid pin.");
    return pinType::INPUT;
}

void nts::InputComponent::updateOutputPin() {
    return;
}

