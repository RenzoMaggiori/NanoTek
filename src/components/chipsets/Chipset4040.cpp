/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4040
*/

#include "Chipset4040.hpp"

nts::Chipset4040::Chipset4040() {
    this->_components[1] = std::make_unique<nts::CounterComponent>();

    for (size_t i = 0; i < 16; ++i) {
        this->_pins[i + 1] = static_cast<CounterComponent*>(this->_components[1].get())->getPins()[i + 1];
    }

    this->_pins[10] = static_cast<CounterComponent*>(this->_components[1].get())->getPins()[10];
    this->_pins[11] = static_cast<CounterComponent*>(this->_components[1].get())->getPins()[11];
    this->_pins[8] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);
    this->_pins[16] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);
}