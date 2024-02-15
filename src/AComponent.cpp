/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <memory>

std::map<std::size_t, std::pair<std::shared_ptr<nts::Tristate>, nts::pinType>> &nts::AComponent::getPins() {
    return _pins;
}

std::pair<std::shared_ptr<nts::Tristate>, nts::pinType> nts::AComponent::getPin(std::size_t pin) {
    return _pins[pin];
}

void nts::AComponent::setLink(std::size_t pin, IComponent &component, std::size_t componentPin) {
    AComponent *componentCast = dynamic_cast<AComponent*>(&component);

    if (!componentCast) throw nts::Error("Component casting failed.");
    if (pin > _pins.size() || pin <= 0) throw nts::Error("Pin outside of bounds.");
    if (componentPin > componentCast->getPins().size() || componentPin <= 0) throw nts::Error("Component pin outside of bounds.");
        if (this->getPinType(pin) == pinType::INPUT && componentCast->getPinType(componentPin) == pinType::OUTPUT) {
            _pins[pin].first.reset();
            _pins[pin].first = componentCast->_pins[componentPin].first;
        }
        if (this->getPinType(pin) == pinType::OUTPUT && componentCast->getPinType(componentPin) == pinType::INPUT) {
            componentCast->_pins[componentPin].first.reset();
            componentCast->_pins[componentPin].first = _pins[pin].first;
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