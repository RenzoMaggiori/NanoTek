/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include "Chipset.hpp"

nts::pinsMapType &nts::AComponent::getPins() {
    return _pins;
}

void nts::AComponent::setLink(std::size_t pin, IComponent &component, std::size_t componentPin)
{
    AComponent *componentCast = dynamic_cast<AComponent*>(&component);
    nts::pinType pinType;
    nts::pinType compPinType;

    if (!componentCast)
        throw nts::Error("Component casting failed.");
    if (getPins().find(pin) == getPins().end())
        throw nts::Error("Pin outside of bounds.");
    if (componentCast->getPins().find(componentPin) == componentCast->getPins().end())
        throw nts::Error("Component pin outside of bounds.");

    pinType = getPinType(pin);
    compPinType = componentCast->getPinType(componentPin);
    //Handle chipset
    if (Chipset* chipsetPtr = dynamic_cast<Chipset*>(componentCast))
        return chipsetPtr->setLink(componentPin, *this, pin);
    //Handle hybrid pins
    if (pinType == pinType::HYBRID && compPinType == pinType::OUTPUT) {
        pin = -pin;
        pinType = getPinType(pin);
    } else if (compPinType == pinType::HYBRID && pinType == pinType::OUTPUT) {
        componentPin = -componentPin;
        compPinType = componentCast->getPinType(componentPin);
    }
    //Link pins
    if (pinType == pinType::INPUT  &&
        (compPinType == pinType::OUTPUT || compPinType == pinType::HYBRID)) {
        this->getPins()[pin].first = componentCast->getPins()[componentPin].first;
        componentCast->_outputLink.push_front(this);
    }
    if ((pinType == pinType::OUTPUT || pinType == pinType::HYBRID)
        && compPinType == pinType::INPUT) {
        componentCast->setLink(componentPin, *this, pin);
        this->_outputLink.push_front(componentCast);
    }
}

nts::Tristate nts::AComponent::compute(std::size_t pin) {
    if (getPins().find(pin) == getPins().end()) nts::Error("Invalid pin.");
    return *(_pins[pin].first.get());
}

nts::pinType nts::AComponent::getType() const {
    return _type;
}

nts::pinType nts::AComponent::getPinType(std::size_t pin) {
    if (getPins().find(pin) == getPins().end()) throw nts::Error("Invalid pin.");
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