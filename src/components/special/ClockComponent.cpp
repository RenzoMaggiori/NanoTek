/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

nts::ClockComponent::ClockComponent()
{
    this->getPins()[1].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
    this->getPins()[1].second = nts::OUTPUT;
    _type = pinType::INPUT;
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

bool nts::ClockComponent::setInput(nts::Tristate status)
{
    this->_availableTick = false;
    *this->getPins()[1].first.get() = status;
    return true;
}