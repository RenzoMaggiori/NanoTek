/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset
*/

#include "Chipset.hpp"
#include <cstddef>
#include <memory>

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

std::shared_ptr<nts::Tristate> nts::Chipset::getPin(std::size_t pin)
{
    std::size_t i = 0;
    AComponent* derivedComponent = nullptr;

    for (auto &it : _components) {
        derivedComponent = dynamic_cast<AComponent*>(it.second.get());
        if (i == pin)
            return derivedComponent->getPin(pin);
        i = i + derivedComponent->getPins().size();
    }
    return nullptr;
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
    for (auto &it: _components) {
        it.second->setLink(pin, component, componentPin);
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