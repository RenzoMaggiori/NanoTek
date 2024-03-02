/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4801
*/

#include "Chipset4801.hpp"

nts::Chipset4801::Chipset4801()
{
    //ADDRESS
    _pins[1].second = nts::pinType::INPUT;
    _pins[2].second = nts::pinType::INPUT;
    _pins[3].second = nts::pinType::INPUT;
    _pins[4].second = nts::pinType::INPUT;
    _pins[5].second = nts::pinType::INPUT;
    _pins[6].second = nts::pinType::INPUT;
    _pins[7].second = nts::pinType::INPUT;
    _pins[8].second = nts::pinType::INPUT;
    _pins[22].second = nts::pinType::INPUT;
    _pins[23].second = nts::pinType::INPUT;

    //HYBRID OUTPUTS
    _pins[9].second = nts::pinType::HYBRID;
    _pins[10].second = nts::pinType::HYBRID;
    _pins[11].second = nts::pinType::HYBRID;
    _pins[13].second = nts::pinType::HYBRID;
    _pins[14].second = nts::pinType::HYBRID;
    _pins[15].second = nts::pinType::HYBRID;
    _pins[16].second = nts::pinType::HYBRID;
    _pins[17].second = nts::pinType::HYBRID;
    _pins[static_cast<std::size_t>(-9)].second = nts::pinType::INPUT;
    _pins[static_cast<std::size_t>(-10)].second = nts::pinType::INPUT;
    _pins[static_cast<std::size_t>(-11)].second = nts::pinType::INPUT;
    _pins[static_cast<std::size_t>(-13)].second = nts::pinType::INPUT;
    _pins[static_cast<std::size_t>(-14)].second = nts::pinType::INPUT;
    _pins[static_cast<std::size_t>(-15)].second = nts::pinType::INPUT;
    _pins[static_cast<std::size_t>(-16)].second = nts::pinType::INPUT;
    _pins[static_cast<std::size_t>(-17)].second = nts::pinType::INPUT;

    //IGNORE
    _pins[12].second = nts::pinType::NONE;
    _pins[19].second = nts::pinType::NONE;
    _pins[24].second = nts::pinType::NONE;

    //MODES
    _pins[18].second = nts::pinType::INPUT;
    _pins[20].second = nts::pinType::INPUT;
    _pins[21].second = nts::pinType::INPUT;


    for (size_t i = 1; i < 25; i++) {
        _pins[i].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
    }

    std::fill(std::begin(this->_memory), std::end(this->_memory), 0);
}


int nts::Chipset4801::getAddress()
{
    int address = 0;
    std::deque<nts::Tristate> inputs;

    inputs.push_front(*_pins[8].first.get());
    inputs.push_front(*_pins[7].first.get());
    inputs.push_front(*_pins[6].first.get());
    inputs.push_front(*_pins[5].first.get());
    inputs.push_front(*_pins[4].first.get());
    inputs.push_front(*_pins[3].first.get());
    inputs.push_front(*_pins[2].first.get());
    inputs.push_front(*_pins[1].first.get());
    inputs.push_front(*_pins[23].first.get());
    inputs.push_front(*_pins[22].first.get());

    for (std::size_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] != nts::Tristate::Undefined)
            break;
        if (i == inputs.size() - 1)
            return (-1);
    }

    for (std::size_t i = inputs.size(); i > 0; i--) {
        if (inputs[i-1] == nts::Tristate::True) {
            address += 1 << (inputs.size() - i);
        }
    }
    return address;
}

void nts::Chipset4801::readMode(int address)
{
    int data = this->_memory[address];
    int byte0 = data & 1;
    int byte1 = (data >> 1) & 1;
    int byte2 = (data >> 2) & 1;
    int byte3 = (data >> 3) & 1;
    int byte4 = (data >> 4) & 1;
    int byte5 = (data >> 5) & 1;
    int byte6 = (data >> 6) & 1;
    int byte7 = (data >> 7) & 1;

    *this->_pins[9].first.get() = (nts::Tristate)byte0;
    *this->_pins[10].first.get() = (nts::Tristate)byte1;
    *this->_pins[11].first.get() = (nts::Tristate)byte2;
    *this->_pins[13].first.get() = (nts::Tristate)byte3;
    *this->_pins[14].first.get() = (nts::Tristate)byte4;
    *this->_pins[15].first.get() = (nts::Tristate)byte5;
    *this->_pins[16].first.get() = (nts::Tristate)byte6;
    *this->_pins[17].first.get() = (nts::Tristate)byte7;
}

void nts::Chipset4801::writeMode(int address)
{
    int data = 0;
    std::deque<nts::Tristate> inputs;

    inputs.push_front(*_pins[static_cast<std::size_t>(-9)].first.get());
    inputs.push_front(*_pins[static_cast<std::size_t>(-10)].first.get());
    inputs.push_front(*_pins[static_cast<std::size_t>(-11)].first.get());
    inputs.push_front(*_pins[static_cast<std::size_t>(-13)].first.get());
    inputs.push_front(*_pins[static_cast<std::size_t>(-14)].first.get());
    inputs.push_front(*_pins[static_cast<std::size_t>(-15)].first.get());
    inputs.push_front(*_pins[static_cast<std::size_t>(-16)].first.get());
    inputs.push_front(*_pins[static_cast<std::size_t>(-17)].first.get());

    for (std::size_t i = inputs.size(); i > 0; i--) {
        if (inputs[i-1] == nts::Tristate::True) {
            data += 1 << (inputs.size() - i);
        }
    }
    this->_memory[address] = data;
}

void nts::Chipset4801::simulate(std::size_t tick)
{
    (void)tick;
    int address = getAddress();
    if (address < 0 || address > 2048)
        return;
    //Mode reading
    if (*this->_pins[18].first.get() == nts::Tristate::False &&
        *this->_pins[21].first.get() == nts::Tristate::False) {
        writeMode(address);
        return;
    }
    //Mode programming
    if (*this->_pins[18].first.get() == nts::Tristate::False &&
        *this->_pins[20].first.get() == nts::Tristate::False &&
        *this->_pins[21].first.get() == nts::Tristate::True) {
        readMode(address);
        return;
    }
}