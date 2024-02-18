/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "IComponent.hpp"
#include "components/chipsets/Chipset.hpp"
#include <memory>
nts::pinsMapType &nts::AComponent::getPins() {
    return _pins;
}

void nts::AComponent::setLink(std::size_t pin, IComponent &component, std::size_t componentPin) {
    AComponent *componentCast = dynamic_cast<AComponent*>(&component);

    if (Chipset* chipsetPtr = dynamic_cast<Chipset*>(componentCast)) {
        chipsetPtr->setLink(componentPin, *this, pin);
        return;
    }
    if (!componentCast) throw nts::Error("Component casting failed.");
    if (pin > _pins.size() || pin <= 0) throw nts::Error("Pin outside of bounds.");
    if (componentPin > componentCast->getPins().size() || componentPin <= 0) throw nts::Error("Component pin outside of bounds.");

    if (this->getPinType(pin) == pinType::INPUT && componentCast->getPinType(componentPin) == pinType::OUTPUT) {
        this->getPins()[pin].first = componentCast->getPins()[componentPin].first;
        componentCast->_outputLink = this;
    }
    if (this->getPinType(pin) == pinType::OUTPUT && componentCast->getPinType(componentPin) == pinType::INPUT) {
        componentCast->getPins()[componentPin].first = this->getPins()[pin].first;
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

nts::pinType nts::AComponent::getPinType(std::size_t pin) {
    if (pin > _pins.size()) throw nts::Error("Invalid pin.");
    return _pins[pin].second;
}

void nts::AComponent::simulate(std::size_t tick) {
    this->simulate(tick);
    (void) tick;
}

void nts::AComponent::setInput(nts::Tristate status) {
    (void) status;
    return;
}

nts::IComponent *nts::AComponent::getOutputLink() {
    return this->_outputLink;
}

void nts::AComponent::setPriority(std::size_t priority) {
    _priority = priority;
}

std::size_t nts::AComponent::getPriority() const {
    return _priority;
}