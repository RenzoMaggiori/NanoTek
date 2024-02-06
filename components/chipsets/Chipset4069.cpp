/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4069
*/

#include "Chipset4069.hpp"

#include "../elementary/NotComponent.hpp"

nts::Chipset4069::Chipset4069()
{
    int y = 0;

    for (int i = 1; i < 7; i++) {
        this->_components[i] = std::make_unique<nts::NotComponent>();
        AComponent *derivedComponent = dynamic_cast<AComponent *>(this->_components[i].get());
        if (i == 4)
            y++;
        for (int count = 1; count < 3; count++) {
            this->_pins[y] = derivedComponent->getPin(count);
            y++;
        }
    }
}
