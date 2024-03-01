/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"

nts::OutputComponent::OutputComponent() {
    this->getPins()[1].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
    this->getPins()[1].second = nts::INPUT;
    _type = nts::pinType::OUTPUT;
}

void nts::OutputComponent::simulate(std::size_t tick) {
    (void) tick;
    return;
}

bool nts::OutputComponent::setInput(nts::Tristate status)
{
    if (_pins[1].second == nts::pinType::HYBRID) {
        *_pins[1].first.get() = status;
        return true;
    } else {
        return false;
    }
}