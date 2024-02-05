/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include <memory>
#include <iostream>

std::map<std::size_t, std::shared_ptr<nts::Tristate>> &nts::AComponent::getPins() {
    return _pins;
}

std::shared_ptr<nts::Tristate> nts::AComponent::getPin(std::size_t pin) {
    return _pins[pin];
}

void nts::AComponent::setLink(std::size_t pin, IComponent &component, std::size_t componentPin) {
    AComponent *componentCast = dynamic_cast<AComponent*>(&component);

    if (pin > _pins.size()) throw Error("Pin outside of bounds.");
    if (componentPin > componentCast->getPins().size()) throw Error("Component pin outside of bounds.");

    _pins[pin] = componentCast->getPins()[componentPin];

    this->updateOutputPin();
}

nts::Tristate nts::AComponent::compute(std::size_t pin) {
    if (pin > _pins.size()) Error("Invalid pin.");
    return *(_pins[pin]);
}

