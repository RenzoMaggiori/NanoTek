/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "IComponent.hpp"
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

    if (!componentCast) throw Error("Component casting failed.");
    if (pin > _pins.size() || pin <= 0) throw Error("Pin outside of bounds.");
    if (componentPin > componentCast->getPins().size() || componentPin <= 0) throw Error("Component pin outside of bounds.");

    if (this->getPinType(pin) == pinType::INPUT && componentCast->getPinType(componentPin) == pinType::OUTPUT)
        _pins[pin] = componentCast->_pins[componentPin];
    if (this->getPinType(pin) == pinType::OUTPUT && componentCast->getPinType(componentPin) == pinType::INPUT)
        componentCast->_pins[componentPin] = _pins[pin];

    this->updateOutputPin();
}

nts::Tristate nts::AComponent::compute(std::size_t pin) {
    if (pin > _pins.size()) Error("Invalid pin.");
    return *(_pins[pin]);
}

nts::pinType nts::AComponent::getType() const {
    return _type;
}

void nts::AComponent::simulate(std::size_t tick) {
    (void) tick;
}

void nts::AComponent::setInput(nts::Tristate status) {
    (void) status;
}