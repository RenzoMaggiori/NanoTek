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

void nts::Chipset::simulate(std::size_t tick)
{
    AComponent* derivedComponent = nullptr;
    for (auto &it: _components) {
        derivedComponent = dynamic_cast<AComponent*>(it.second.get());
        derivedComponent->simulate(tick);
    }
}

void nts::Chipset::setLink(std::size_t pin, IComponent &component, std::size_t componentPin)
{
    if (pin > _pins.size() || pin <= 0) throw nts::Error("Pin outside of bounds.");
    if (componentPin > static_cast<AComponent*>(&component)->getPins().size() || componentPin <= 0)
        throw nts::Error("Component pin outside of bounds.");
    
    std::map<std::size_t, std::pair<std::shared_ptr<nts::Tristate>, nts::pinType>> pinsMap;

    for (std::size_t i = 1; i <= _components.size(); i++) {
        pinsMap = dynamic_cast<AComponent *>(_components[i].get())->getPins();
        for  (std::size_t j = 1; j <= pinsMap.size(); j++) {
            if (pinsMap[j] == _pins[pin]) {
                this->_components[i]->setLink(j, component, componentPin);
            }
        }
    }
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