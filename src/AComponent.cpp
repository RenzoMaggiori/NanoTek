/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <float.h>
#include <memory>
#include <iostream>
nts::pinsMapType &nts::AComponent::getPins() {
    return _pins;
}

nts::pinsPairType &nts::AComponent::getPin(std::size_t pin) {
    return _pins[pin];
}

void nts::AComponent::setLink(std::size_t pin, IComponent &component, std::size_t componentPin) {
    AComponent *componentCast = dynamic_cast<AComponent*>(&component);

    if (!componentCast) throw nts::Error("Component casting failed.");
    if (pin > _pins.size() || pin <= 0) throw nts::Error("Pin outside of bounds.");
    if (componentPin > componentCast->getPins().size() || componentPin <= 0) throw nts::Error("Component pin outside of bounds.");

    if (this->getPinType(pin) == pinType::INPUT && componentCast->getPinType(componentPin) == pinType::OUTPUT) {
        this->getPin(pin).first = componentCast->getPin(componentPin).first;
        componentCast->_outputLink = this;
    }
    if (this->getPinType(pin) == pinType::OUTPUT && componentCast->getPinType(componentPin) == pinType::INPUT) {
        componentCast->getPin(componentPin).first = this->getPin(pin).first;
        this->_outputLink = componentCast;
    }

}

nts::Tristate nts::AComponent::compute(std::size_t pin) {
    if (pin > _pins.size()) nts::Error("Invalid pin.");
    return *(_pins[pin].first.get());
}

nts::pinType nts::AComponent::getType() const {
    return _type;
}

void nts::AComponent::simulate(std::size_t tick) {
    this->simulate(tick);
    (void) tick;
}

void nts::AComponent::setInput(nts::Tristate status) {
    (void) status;
    return;
}

void nts::AComponent::setOutputLink(nts::IComponent &component) {
    this->_outputLink = &component;
}

nts::IComponent *nts::AComponent::getOutputLink() {
    return this->_outputLink;
}