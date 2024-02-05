/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4071
*/

#include "Chipset4071.hpp"
#include "../elementary/OrComponent.hpp"

nts::Chipset4071::Chipset4071() {
    for (int i = 1; i < 5; i++) {
        this->_components[i] = std::make_unique<nts::OrComponent>();
    }
}
