/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset
*/

#include "Chipset.hpp"
#include "../elementary/NotComponent.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

nts::pinType nts::Chipset::getPinType(std::size_t pin)
{
    std::size_t i = 0;
    AComponent* derivedComponent = nullptr;

    for (auto &it : _components) {
        derivedComponent = dynamic_cast<AComponent*>(it.second.get());
        if (i == pin)
            return derivedComponent->getPinType(pin);
        i = i + derivedComponent->getPins().size();
    }
    return nts::pinType::NONE;
}

std::pair<std::shared_ptr<nts::Tristate>, nts::pinType> nts::Chipset::getPin(std::size_t pin)
{
    std::size_t i = 0;
    AComponent* derivedComponent = nullptr;
    for (auto &it : _components) {
        derivedComponent = dynamic_cast<AComponent*>(it.second.get());
        if (i == pin)
            return derivedComponent->getPin(pin);
        i = i + derivedComponent->getPins().size();
    }
    return std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);
}

void nts::Chipset::updateOutputPin()
{
    AComponent* derivedComponent = nullptr;
    for (auto &it: _components) {
        derivedComponent = dynamic_cast<AComponent*>(it.second.get());
        derivedComponent->updateOutputPin();
    }
}

void nts::Chipset::setLink(std::size_t pin, IComponent &component, std::size_t componentPin)
{
    AComponent *componentCast = dynamic_cast<AComponent*>(&component);
    if (!componentCast) throw Error("Component casting failed.");
    if (pin > _pins.size() || pin <= 0) throw Error("Pin outside of bounds.");
    if (componentPin > componentCast->getPins().size() || componentPin <= 0) throw Error("Component pin outside of bounds.");
    //In case the pin is 1- 7
    if (pin < 8) {
        if (pin % 2 == 0)
            this->_components[pin / 2]->setLink(2, component, componentPin);
        else
            this->_components[(pin / 2) + 1]->setLink(1, component, componentPin);
    } else if (pin >= 8) {
        if (pin % 2 != 0)
            this->_components[(pin / 2)]->setLink(1, component, componentPin);
        else
            this->_components[(pin / 2)]->setLink(2, component, componentPin);
    }
    this->updateOutputPin();
}



nts::Tristate nts::Chipset::compute(std::size_t pin)
{
    std::size_t i = 0;
    AComponent* derivedComponent = nullptr;

    for (auto &it : _components) {
        derivedComponent = dynamic_cast<AComponent*>(it.second.get());
        if (i == pin)
            return it.second->compute(pin);
        i = i + derivedComponent->getPins().size();
    }
    return nts::Tristate::Undefined;
}