/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset2716
*/


#include "Chipset2716.hpp"
#include <iostream>
#include <iterator>

nts::Chipset2716::Chipset2716()
{
    for (size_t i = 1; i < 25; i++) {
        if (i < 9) {
            _pins[i].second = nts::pinType::INPUT;
        } else if (i > 8 && i < 12) {
            _pins[i].second = nts::pinType::HYBRID;
        } else if (i == 12){
            _pins[i].second = nts::pinType::NONE;
        } else if (i > 12 && i < 18) {
            _pins[i].second = nts::pinType::HYBRID;
        } else if (i == 18) {
            _pins[i].second = nts::pinType::INPUT;
        } else if (i == 19) {
            _pins[i].second = nts::pinType::NONE;
        } else if (i == 20) {
            _pins[i].second = nts::pinType::INPUT;
        } else if (i == 21) {
            _pins[i].second = nts::pinType::NONE;
        } else if (i > 21 && i < 24) {
            _pins[i].second = nts::pinType::INPUT;
        } else if (i == 24) {
            _pins[i].second = nts::pinType::NONE;
        }
        _pins[i].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
    }
}


int nts::Chipset2716::getAddress()
{
    int address = 0;
    std::deque<nts::Tristate> inputs;

    inputs.push_back(*_pins[8].first.get());
    inputs.push_back(*_pins[7].first.get());
    inputs.push_back(*_pins[6].first.get());
    inputs.push_back(*_pins[5].first.get());
    inputs.push_back(*_pins[4].first.get());
    inputs.push_back(*_pins[3].first.get());
    inputs.push_back(*_pins[2].first.get());
    inputs.push_back(*_pins[1].first.get());
    inputs.push_back(*_pins[23].first.get());
    inputs.push_back(*_pins[22].first.get());
    inputs.push_back(*_pins[19].first.get());

    for (std::size_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] == nts::Tristate::True) {
            address += 1 << i;
        }
    }
    return address;
}

void nts::Chipset2716::readMode(int address)
{
    int data = this->_memory[address];
    int byte0 = data & 0x01;
    int byte1 = data & 0x02;
    int byte2 = data & 0x04;
    int byte3 = data & 0x08;
    int byte4 = data & 0x10;
    int byte5 = data & 0x20;
    int byte6 = data & 0x40;
    int byte7 = data & 0x80;

    *this->_pins[9].first.get() = (nts::Tristate)byte0;
    *this->_pins[10].first.get() = (nts::Tristate)byte1;
    *this->_pins[11].first.get() = (nts::Tristate)byte2;
    *this->_pins[13].first.get() = (nts::Tristate)byte3;
    *this->_pins[14].first.get() = (nts::Tristate)byte4;
    *this->_pins[15].first.get() = (nts::Tristate)byte5;
    *this->_pins[16].first.get() = (nts::Tristate)byte6;
    *this->_pins[17].first.get() = (nts::Tristate)byte7;
}

void nts::Chipset2716::programMode(int address)
{
    int data = 0;
    std::deque<nts::Tristate> inputs;

    inputs.push_back(*_pins[9].first.get());
    inputs.push_back(*_pins[10].first.get());
    inputs.push_back(*_pins[11].first.get());
    inputs.push_back(*_pins[13].first.get());
    inputs.push_back(*_pins[14].first.get());
    inputs.push_back(*_pins[15].first.get());
    inputs.push_back(*_pins[16].first.get());
    inputs.push_back(*_pins[17].first.get());

    for (std::size_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] != nts::Tristate::Undefined) {
            data += 1 << i;
        }
    }
    this->_memory[address] = data;

}

void nts::Chipset2716::simulate(std::size_t tick)
{
    (void)tick;
    int address = getAddress();
    //Mode reading
    if (*this->_pins[18].first.get() == nts::Tristate::False &&
        *this->_pins[20].first.get() == nts::Tristate::True) {
        readMode(address);
        return;
    }
    //Mode programming
    if (*this->_pins[18].first.get() == nts::Tristate::True &&
        *this->_pins[20].first.get() == nts::Tristate::True) {
        programMode(address);
        return;
    }
}