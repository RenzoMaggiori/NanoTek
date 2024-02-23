/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4008
*/

#include "Chipset4008.hpp"


void nts::Chipset4008::adder(int firstPin, bool comp, int andPin1, int andPin2) {
    this->_components[firstPin] = std::make_unique<nts::XorComponent>();
    this->_components[firstPin + 1] = std::make_unique<nts::OrComponent>();
    this->_components[firstPin + 2] = std::make_unique<nts::AndComponent>();
    this->_components[firstPin + 3] = std::make_unique<nts::AndComponent>();
    this->_components[firstPin + 4] = std::make_unique<nts::XorComponent>();

    static_cast<XorComponent*>(this->_components[firstPin + 4].get())->getPins()[1] = static_cast<XorComponent*>(this->_components[firstPin].get())->getPins()[3];

    if (!comp)
        static_cast<AndComponent*>(this->_components[firstPin + 2].get())->getPins()[1] = static_cast<AndComponent*>(this->_components[firstPin + 7].get())->getPins()[3];
    else
        static_cast<AndComponent*>(this->_components[firstPin + 2].get())->getPins()[1] = this->_pins[9];

    static_cast<AndComponent*>(this->_components[firstPin + 2].get())->getPins()[2] = static_cast<AndComponent*>(this->_components[firstPin].get())->getPins()[3];

    static_cast<AndComponent*>(this->_components[firstPin + 3].get())->getPins()[1] = this->_pins[andPin1];
    static_cast<AndComponent*>(this->_components[firstPin + 3].get())->getPins()[2] = this->_pins[andPin2];

    static_cast<OrComponent*>(this->_components[firstPin + 1].get())->getPins()[1] = static_cast<AndComponent*>(this->_components[firstPin + 2].get())->getPins()[3];
    static_cast<OrComponent*>(this->_components[firstPin + 1].get())->getPins()[2] = static_cast<AndComponent*>(this->_components[firstPin + 3].get())->getPins()[3];
}

nts::Chipset4008::Chipset4008() {

    adder(16, true, 6, 7);
    adder(11, false, 4, 5);
    adder(6, false, 3, 2);
    adder(1, false, 1, 15);

    static_cast<XorComponent*>(this->_components[20].get())->getPins()[2] = this->_pins[9];

    this->_pins[13] = static_cast<XorComponent*>(this->_components[5].get())->getPins()[3];
    this->_pins[12] = static_cast<XorComponent*>(this->_components[10].get())->getPins()[3];
    this->_pins[11] = static_cast<XorComponent*>(this->_components[15].get())->getPins()[3];
    this->_pins[10] = static_cast<XorComponent*>(this->_components[20].get())->getPins()[3];
    static_cast<XorComponent*>(this->_components[1].get())->getPins()[1] = this->_pins[15];
    static_cast<XorComponent*>(this->_components[1].get())->getPins()[2] = this->_pins[1];
    static_cast<XorComponent*>(this->_components[6].get())->getPins()[1] = this->_pins[2];
    static_cast<XorComponent*>(this->_components[6].get())->getPins()[2] = this->_pins[3];
    static_cast<XorComponent*>(this->_components[11].get())->getPins()[1] = this->_pins[4];
    static_cast<XorComponent*>(this->_components[11].get())->getPins()[2] = this->_pins[5];
    static_cast<XorComponent*>(this->_components[16].get())->getPins()[1] = this->_pins[6];
    static_cast<XorComponent*>(this->_components[16].get())->getPins()[2] = this->_pins[7];
    this->_pins[8] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);;
    this->_pins[16] = std::make_pair<std::shared_ptr<nts::Tristate>, nts::pinType>(nullptr, nts::pinType::NONE);
}

