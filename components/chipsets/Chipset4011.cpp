/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4011
*/

#include "Chipset4011.hpp"
#include "../elementary/NandComponent.hpp"

nts::Chipset4011::Chipset4011()
{
    for (int i = 1; i < 5; i++) {
        this->_components[i] = std::make_unique<nts::NandComponent>();
    }
}
