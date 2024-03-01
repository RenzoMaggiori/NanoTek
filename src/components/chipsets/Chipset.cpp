/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset
*/

#include "Chipset.hpp"


void nts::Chipset::setLink(std::size_t pin, IComponent &component, std::size_t componentPin)
{
    if (getPins().find(pin) == getPins().end() || pin <= 0) throw nts::Error("Pin outside of bounds.");
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

