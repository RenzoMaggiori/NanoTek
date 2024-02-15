/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** InputComponent
*/

#include "InputComponent.hpp"
#include <iostream>

nts::InputComponent::InputComponent() {
    _pins[1] = std::make_pair(std::make_shared<nts::Tristate>(Tristate::Undefined), nts::OUTPUT);
    _type = pinType::INPUT;
}

nts::pinType nts::InputComponent::getPinType(std::size_t pin) {
    if (pin != 1) throw nts::Error("Invalid pin.");
    return pinType::OUTPUT;
}

void nts::InputComponent::simulate(std::size_t tick) {
    (void) tick;
    return;
}

void nts::InputComponent::setInput(nts::Tristate status)
{
    *_pins[1].first.get() = status;
}