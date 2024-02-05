/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset
*/

#include "Chipset.hpp"
#include <cstddef>

nts::pinType nts::Chipset::getPinType(std::size_t pin)
{
    std::size_t i = 0;

    for (auto &it : _components) {
        if (i == pin)
            return it.second->getPinType(pin);
        i = i + it.second->getPins().size();
    }
    return nts::pinType::NONE;
}

void nts::Chipset::updateOutputPin()
{
    for (auto &it: _components) {
        it.second->updateOutputPin();
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

    for (auto &it : _components) {
        if (i == pin)
            return it.second->compute(pin);
        i = i + it.second->getPins().size();
    }
    return nts::Tristate::Undefined;
}