/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4008
*/

#include "Chipset4008.hpp"
#include "AdderComponent.hpp"

nts::Chipset4008::Chipset4008() {

    this->_components[1] = std::make_unique<nts::AdderComponent>();
    this->_components[2] = std::make_unique<nts::AdderComponent>();
    this->_components[3] = std::make_unique<nts::AdderComponent>();
    this->_components[4] = std::make_unique<nts::AdderComponent>();

    this->_pins[15] = static_cast<AdderComponent*>(this->_components[1].get())->getPins()[1];
    this->_pins[1] = static_cast<AdderComponent*>(this->_components[1].get())->getPins()[2];
    this->_pins[2] = static_cast<AdderComponent*>(this->_components[2].get())->getPins()[1];
    this->_pins[3] = static_cast<AdderComponent*>(this->_components[2].get())->getPins()[2];
    this->_pins[4] = static_cast<AdderComponent*>(this->_components[3].get())->getPins()[1];
    this->_pins[5] = static_cast<AdderComponent*>(this->_components[3].get())->getPins()[2];
    this->_pins[6] = static_cast<AdderComponent*>(this->_components[4].get())->getPins()[1];
    this->_pins[7] = static_cast<AdderComponent*>(this->_components[4].get())->getPins()[2];
    this->_pins[8] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);
    this->_pins[16] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);

    this->_pins[14] = static_cast<AdderComponent*>(this->_components[1].get())->getPins()[4];
    static_cast<AdderComponent*>(this->_components[1].get())->getPins()[3] = static_cast<AdderComponent*>(this->_components[2].get())->getPins()[4];
    static_cast<AdderComponent*>(this->_components[2].get())->getPins()[3] = static_cast<AdderComponent*>(this->_components[3].get())->getPins()[4];
    static_cast<AdderComponent*>(this->_components[3].get())->getPins()[3] = static_cast<AdderComponent*>(this->_components[4].get())->getPins()[4];
    static_cast<AdderComponent*>(this->_components[2].get())->setOutputLink(this->_components[1].get());
    static_cast<AdderComponent*>(this->_components[3].get())->setOutputLink(this->_components[2].get());
    static_cast<AdderComponent*>(this->_components[4].get())->setOutputLink(this->_components[3].get());
    this->_pins[9] = static_cast<AdderComponent*>(this->_components[4].get())->getPins()[3];

    this->_pins[13] = static_cast<AdderComponent*>(this->_components[1].get())->getPins()[5];
    this->_pins[12] = static_cast<AdderComponent*>(this->_components[2].get())->getPins()[5];
    this->_pins[11] = static_cast<AdderComponent*>(this->_components[3].get())->getPins()[5];
    this->_pins[10] = static_cast<AdderComponent*>(this->_components[4].get())->getPins()[5];
}

