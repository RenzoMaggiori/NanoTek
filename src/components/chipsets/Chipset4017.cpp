/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4017
*/

#include "Chipset4017.hpp"
#include "JohnsonComponent.hpp"

nts::Chipset4017::Chipset4017() {
    this->_components[1] = std::make_unique<nts::JohnsonComponent>();

    this->_pins[14] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[1];
    this->_pins[13] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[2];
    this->_pins[15] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[3];

    this->_pins[3] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[4];
    this->_pins[2] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[5];
    this->_pins[4] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[6];
    this->_pins[7] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[7];
    this->_pins[8] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);;
    this->_pins[10] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[8];
    this->_pins[1] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[9];
    this->_pins[5] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[10];
    this->_pins[6] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[11];
    this->_pins[9] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[12];
    this->_pins[11] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[13];

    this->_pins[12] = static_cast<JohnsonComponent*>(this->_components[1].get())->getPins()[14];
}

