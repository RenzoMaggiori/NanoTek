/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "IComponent.hpp"
#include "components/chipsets/Chipset.hpp"
#include <iostream>
#include <memory>
nts::pinsMapType &nts::AComponent::getPins() {
    return _pins;
}

void nts::AComponent::setLink(std::size_t pin, IComponent &component, std::size_t componentPin) {
    AComponent *componentCast = dynamic_cast<AComponent*>(&component);
    nts::pinType thisPinType;
    nts::pinType compPinType;

    if (!componentCast) throw nts::Error("Component casting failed.");
    if (pin > _pins.size() || pin <= 0) throw nts::Error("Pin outside of bounds.");
    if (componentPin > componentCast->getPins().size() || componentPin <= 0) throw nts::Error("Component pin outside of bounds.");

    if (Chipset* chipsetPtr = dynamic_cast<Chipset*>(componentCast))
        return chipsetPtr->setLink(componentPin, *this, pin);
    thisPinType = this->getPinType(pin);
    compPinType = componentCast->getPinType(componentPin);

    if (thisPinType == pinType::INPUT && compPinType == pinType::OUTPUT) {
        this->getPins()[pin].first = componentCast->getPins()[componentPin].first;
        componentCast->_outputLink.push_front(this);
    }
    if (thisPinType == pinType::OUTPUT && compPinType == pinType::INPUT) {
        componentCast->getPins()[componentPin].first = this->getPins()[pin].first;
        this->_outputLink.push_front(componentCast);
    }
}

nts::Tristate nts::AComponent::compute(std::size_t pin) {
    if (pin > _pins.size()) nts::Error("Invalid pin.");
    return *(_pins[pin].first.get());
}

nts::pinType nts::AComponent::getType() const {
    return _type;
}

nts::pinType nts::AComponent::getPinType(std::size_t pin) {
    if (pin > _pins.size()) throw nts::Error("Invalid pin.");
    return _pins[pin].second;
}

void nts::AComponent::simulate(std::size_t tick) {
    this->simulate(tick);
    (void) tick;
}

bool nts::AComponent::setInput(nts::Tristate status) {
    (void) status;
    return false;
}

std::deque<nts::IComponent *> nts::AComponent::getOutputLink() {
    return this->_outputLink;
}

void nts::AComponent::setPriority(std::size_t priority) {
    _priority = priority;
}

std::size_t nts::AComponent::getPriority() const {
    return _priority;
}

void nts::AComponent::setOutputLink(IComponent * outputLink) {
    _outputLink.push_front(outputLink);
}