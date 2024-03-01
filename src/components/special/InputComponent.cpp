/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

nts::InputComponent::InputComponent() {
    _pins[1] = std::make_pair(std::make_shared<nts::Tristate>(Tristate::Undefined), nts::OUTPUT);
    _type = pinType::INPUT;
}

void nts::InputComponent::simulate(std::size_t tick) {
    (void) tick;
    return;
}

bool nts::InputComponent::setInput(nts::Tristate status)
{
    *_pins[1].first.get() = status;
    return true;
}