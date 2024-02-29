/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset2716
*/


#include "Chipset2716.hpp"
#include <fstream>

nts::Chipset2716::Chipset2716()
{
    std::ifstream file("./rom.bin");

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
    _pins[19].second = nts::pinType::INPUT;
    //OUTPUTS
    _pins[9].second = nts::pinType::OUTPUT;
    _pins[10].second = nts::pinType::OUTPUT;
    _pins[11].second = nts::pinType::OUTPUT;
    _pins[13].second = nts::pinType::OUTPUT;
    _pins[14].second = nts::pinType::OUTPUT;
    _pins[15].second = nts::pinType::OUTPUT;
    _pins[16].second = nts::pinType::OUTPUT;
    _pins[17].second = nts::pinType::OUTPUT;
    //IGNORE
    _pins[12].second = nts::pinType::NONE;
    _pins[21].second = nts::pinType::NONE;
    _pins[24].second = nts::pinType::NONE;
    //MODES
    _pins[18].second = nts::pinType::INPUT;
    _pins[20].second = nts::pinType::INPUT;

    for (size_t i = 1; i < 25; i++) {
        _pins[i].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
    }

    if (file.is_open()) {
        std::copy(std::istreambuf_iterator<char>(file),
                  std::istreambuf_iterator<char>(),
                  std::begin(this->_memory));
    }
    file.close();
}


int nts::Chipset2716::getAddress()
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
    inputs.push_front(*_pins[19].first.get());

    //Check if all inputs are undefined
    for (std::size_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] != nts::Tristate::Undefined)
            break;
        if (i == inputs.size() - 1)
            return (-1);
    }
    //Compute address
    for (std::size_t i = 0; i < inputs.size(); i++) {
        if (inputs[i] == nts::Tristate::True) {
            address += 1 << (inputs.size() - 1 - i);
        }
    }
    return address;
}

void nts::Chipset2716::readMode(int address)
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

void nts::Chipset2716::simulate(std::size_t tick)
{
    (void)tick;
    int address;
    //Mode reading
    if (*this->_pins[18].first.get() == nts::Tristate::False &&
        *this->_pins[20].first.get() == nts::Tristate::False) {
        address = getAddress();
        if (address < 0 || address > 2048)
            return;
        readMode(address);
        return;
    }
}