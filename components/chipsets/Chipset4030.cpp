/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4030
*/

#include "Chipset4030.hpp"
#include "../elementary/XorComponent.hpp"

nts::Chipset4030::Chipset4030()
{
    int y = 0;
    for (int i = 1; i < 5; i++) {
        this->_components[i] = std::make_unique<nts::XorComponent>();
        AComponent *derivedComponent = dynamic_cast<AComponent *>(this->_components[i].get());
        for (int count = 1; count < 4; count++) {
            this->_pins[y] = derivedComponent->getPin(count);
            y++;
        }
    }
}
