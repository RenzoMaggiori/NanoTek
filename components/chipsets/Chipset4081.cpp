/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4081
*/

#include "Chipset4081.hpp"

nts::Chipset4081::Chipset4081() {
    for (int i = 1; i < 5; i++) {
        this->_components[i] = std::make_unique<nts::AndComponent>();
    }
}
