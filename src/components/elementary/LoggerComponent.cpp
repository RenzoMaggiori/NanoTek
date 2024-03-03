/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** LoggerComponent
*/

#include "LoggerComponent.hpp"
#include <iostream>

nts::LoggerComponent::LoggerComponent()
{
    nts::pinType type = nts::pinType::INPUT;
    for (size_t i = 1; i < 11; i++) {
        _pins[i].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i].second = type;
    }
}

int nts::LoggerComponent::getByte()
{
    int address = 0;
    std::deque<nts::Tristate> inputs;

    inputs.push_front(*_pins[1].first.get());
    inputs.push_front(*_pins[2].first.get());
    inputs.push_front(*_pins[3].first.get());
    inputs.push_front(*_pins[4].first.get());
    inputs.push_front(*_pins[5].first.get());
    inputs.push_front(*_pins[6].first.get());
    inputs.push_front(*_pins[7].first.get());
    inputs.push_front(*_pins[8].first.get());

    for (std::size_t i = inputs.size(); i > 0; i--) {
        if (inputs[i-1] == nts::Tristate::True) {
            address += 1 << (inputs.size() - i);
        }
    }
    return address;
}

void nts::LoggerComponent::simulate(std::size_t tick)
{
    if (*_pins[10].first.get() != Tristate::True
    && *_pins[9].first.get() == Tristate::True &&
    (_prevClock == Tristate::False || _prevClock == Tristate::Undefined)) {
        this->_logger.open("./log.bin", std::ios_base::app);
        if (!this->_logger.is_open()) {
            throw  nts::Error("Could not open log file");
            return;
        }
        this->_logger << (char)getByte();
        this->_logger.close();
    }
    _prevClock = *_pins[9].first.get();
 }
