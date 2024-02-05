/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** FalseComponent
*/

#include "FalseComponent.hpp"

nts::FalseComponent::FalseComponent() {
    std::shared_ptr<nts::Tristate> status = std::make_shared<nts::Tristate>(Tristate::False);
    this->getPins()[1] = status;
}

nts::pinType nts::FalseComponent::getPinType(std::size_t pin) {
    if (pin != 1) throw Error("Invalid pin.");
    return pinType::OUTPUT;
}

void nts::FalseComponent::updateOutputPin() {
    return;
}