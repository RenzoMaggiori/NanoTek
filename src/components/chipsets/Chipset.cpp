/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset
*/

#include "Chipset.hpp"
#include "../elementary/NotComponent.hpp"
#include <cstddef>
#include <deque>
#include <iostream>
#include <ostream>

nts::pinType nts::Chipset::getPinType(std::size_t pin)
{
    AComponent *pinsMap;

    for (std::size_t i = 1; i <= _components.size(); i++) {
        pinsMap = dynamic_cast<AComponent *>(_components[i].get());
        for  (std::size_t j = 1; j <= pinsMap->getPins().size(); j++) {
            if (pinsMap->getPins()[j] == _pins[pin]) {
                return pinsMap->getPinType(j);
            }
        }
    }
    throw nts::Error("Pin not found. :" + std::to_string(pin));
}

nts::pinsPairType &nts::Chipset::getPin(std::size_t pin)
{
    AComponent *pinsMap;

    for (std::size_t i = 1; i <= _components.size(); i++) {
        pinsMap = dynamic_cast<AComponent *>(_components[i].get());
        for  (std::size_t j = 1; j <= pinsMap->getPins().size(); j++) {
            if (pinsMap->getPins()[j] == _pins[pin]) {
                return pinsMap->getPin(j);
            }
        }
    }
    throw nts::Error("Pin not found. :" + std::to_string(pin));
}

void nts::Chipset::simulate(std::size_t tick)
{
/*     AComponent* derivedComponent = nullptr;
    for (unsigned int i = 1; i <= _components.size(); i++) {
        for (auto &it: _components) {
            derivedComponent = dynamic_cast<AComponent*>(it.second.get());
            derivedComponent->simulate(tick);
        }
    } */
}

void nts::Chipset::setLink(std::size_t pin, IComponent &component, std::size_t componentPin)
{
    if (pin > _pins.size() || pin <= 0) throw nts::Error("Pin outside of bounds.");
    if (componentPin > static_cast<AComponent*>(&component)->getPins().size() || componentPin <= 0)
        throw nts::Error("Component pin outside of bounds.");

    nts::pinsMapType pinsMap;

    for (std::size_t i = 1; i <= _components.size(); i++) {
        pinsMap = dynamic_cast<AComponent *>(_components[i].get())->getPins();
        for  (std::size_t j = 1; j <= pinsMap.size(); j++) {
            if (pinsMap[j] == _pins[pin]) {
                _components[i].get()->setLink(j, component, componentPin);
            }
        }
    }
}

nts::Tristate nts::Chipset::compute(std::size_t pin)
{
    AComponent *pinsMap;

    for (std::size_t i = 1; i <= _components.size(); i++) {
        pinsMap = dynamic_cast<AComponent *>(_components[i].get());
        for  (std::size_t j = 1; j <= pinsMap->getPins().size(); j++) {
            if (pinsMap->getPins()[j] == _pins[pin]) {
                return pinsMap->compute(j);
            }
        }
    }
    return nts::Tristate::Undefined;
}