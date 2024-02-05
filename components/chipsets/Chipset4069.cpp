/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4069
*/

#include "Chipset4069.hpp"

#include "../NotComponent.hpp"

nts::Chipset4069::Chipset4069()
{
    for (int i = 1; i < 7; i++) {
        this->_components[i] = std::make_unique<nts::NotComponent>();
    }
}
