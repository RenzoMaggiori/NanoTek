/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4001
*/

#include "Chipset4001.hpp"
#include "../elementary/NorComponent.hpp"

nts::Chipset4001::Chipset4001()
{
    this->_components[1] = std::make_unique<nts::NorComponent>();
    this->_components[2] = std::make_unique<nts::NorComponent>();
    this->_components[3] = std::make_unique<nts::NorComponent>();
    this->_components[4] = std::make_unique<nts::NorComponent>();

    this->_pins[1] = static_cast<NorComponent*>(this->_components[1].get())->getPin(1);
    this->_pins[2] = static_cast<NorComponent*>(this->_components[1].get())->getPin(2);
    this->_pins[3] = static_cast<NorComponent*>(this->_components[1].get())->getPin(3);
    this->_pins[4] = static_cast<NorComponent*>(this->_components[2].get())->getPin(3);
    this->_pins[5] = static_cast<NorComponent*>(this->_components[2].get())->getPin(2);
    this->_pins[6] = static_cast<NorComponent*>(this->_components[2].get())->getPin(1);
    this->_pins[7] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);;
    this->_pins[8] = static_cast<NorComponent*>(this->_components[3].get())->getPin(1);
    this->_pins[9] = static_cast<NorComponent*>(this->_components[3].get())->getPin(2);
    this->_pins[10] = static_cast<NorComponent*>(this->_components[3].get())->getPin(3);
    this->_pins[11] = static_cast<NorComponent*>(this->_components[4].get())->getPin(3);
    this->_pins[12] = static_cast<NorComponent*>(this->_components[4].get())->getPin(2);
    this->_pins[13] = static_cast<NorComponent*>(this->_components[4].get())->getPin(1);
    this->_pins[14] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);
}