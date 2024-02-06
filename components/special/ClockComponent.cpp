/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

nts::ClockComponent::ClockComponent()
{
    std::shared_ptr<nts::Tristate> status = std::make_shared<nts::Tristate>(Tristate::Undefined);
    this->getPins()[1] = status;
    _type = pinType::INPUT;
}

nts::pinType nts::ClockComponent::getPinType(std::size_t pin)
{
    if (pin != 1)
        throw Error("Invalid pin.");
    return pinType::OUTPUT;
}

void nts::ClockComponent::updateOutputPin()
{
    nts::Tristate state = *this->getPins()[1].get();
    if (state == nts::Tristate::False)
        *this->getPins()[1].get() = nts::Tristate::True;
    else if (state == nts::Tristate::True)
        *this->getPins()[1].get() = nts::Tristate::False;
}

void nts::ClockComponent::setInput(nts::Tristate status)
{
    *this->getPins()[1].get() = status;
}