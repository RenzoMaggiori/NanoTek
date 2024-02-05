/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4001
*/

#include "Chipset4001.hpp"
#include "../NorComponent.hpp"

nts::Chipset4001::Chipset4001()
{
    for (int i = 1; i < 5; i++) {
        this->_components[i] = std::make_unique<nts::NorComponent>();
    }
}