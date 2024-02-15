/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"
#include <iostream>

nts::ClockComponent::ClockComponent()
{
    this->getPins()[1].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
    this->getPins()[1].second = nts::OUTPUT;
    _type = pinType::INPUT;
}

nts::pinType nts::ClockComponent::getPinType(std::size_t pin)
{
    if (pin != 1)
        throw nts::Error("Invalid pin.");
    return pinType::OUTPUT;
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    if (!this->_availableTick) {
        this->_availableTick = true;
        return;
    }
    nts::Tristate state = *this->getPins()[1].first.get();
    if (state != nts::Tristate::Undefined)
        *this->getPins()[1].first.get() = (state == nts::Tristate::True) ? nts::Tristate::False : nts::Tristate::True;
}

void nts::ClockComponent::setInput(nts::Tristate status)
{
    this->_availableTick = false;
    *this->getPins()[1].first.get() = status;
}