/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** FalseComponent
*/

#include "FalseComponent.hpp"

nts::FalseComponent::FalseComponent() {
    this->getPins()[1].first = std::make_shared<nts::Tristate>(Tristate::False);
    this->getPins()[1].second = nts::OUTPUT;
    _type = pinType::NONE;
}

nts::pinType nts::FalseComponent::getPinType(std::size_t pin) {
    if (pin != 1) throw nts::Error("Invalid pin.");
    return pinType::OUTPUT;
}

void nts::FalseComponent::simulate(std::size_t tick) {
    (void) tick;
    return;
}