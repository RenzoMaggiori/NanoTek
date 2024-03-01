/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4013
*/

#include "Chipset4013.hpp"
#include "FlipflopComponent.hpp"

nts::Chipset4013::Chipset4013()
{
    this->_components[1] = std::make_unique<nts::FlipflopComponent>();
    this->_components[2] = std::make_unique<nts::FlipflopComponent>();

    this->_pins[3] = static_cast<FlipflopComponent*>(this->_components[1].get())->getPins()[1];
    this->_pins[5] = static_cast<FlipflopComponent*>(this->_components[1].get())->getPins()[2];
    this->_pins[6] = static_cast<FlipflopComponent*>(this->_components[1].get())->getPins()[3];
    this->_pins[4] = static_cast<FlipflopComponent*>(this->_components[1].get())->getPins()[4];
    this->_pins[1] = static_cast<FlipflopComponent*>(this->_components[1].get())->getPins()[5];
    this->_pins[2] = static_cast<FlipflopComponent*>(this->_components[1].get())->getPins()[6];
    this->_pins[7] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);;
    this->_pins[11] = static_cast<FlipflopComponent*>(this->_components[2].get())->getPins()[1];
    this->_pins[9] = static_cast<FlipflopComponent*>(this->_components[2].get())->getPins()[2];
    this->_pins[8] = static_cast<FlipflopComponent*>(this->_components[2].get())->getPins()[3];
    this->_pins[10] = static_cast<FlipflopComponent*>(this->_components[2].get())->getPins()[4];
    this->_pins[13] = static_cast<FlipflopComponent*>(this->_components[2].get())->getPins()[5];
    this->_pins[12] = static_cast<FlipflopComponent*>(this->_components[2].get())->getPins()[6];
}