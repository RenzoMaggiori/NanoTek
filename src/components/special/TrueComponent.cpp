/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"
#include <memory>

nts::TrueComponnet::TrueComponnet() {
    this->getPins()[1].first = std::make_shared<nts::Tristate>(Tristate::True);
    this->getPins()[1].second = nts::OUTPUT;
    _type = pinType::NONE;
}

nts::pinType nts::TrueComponnet::getPinType(std::size_t pin) {
    if (pin != 1) throw nts::Error("Invalid pin.");
    return pinType::OUTPUT;
}

void nts::TrueComponnet::simulate(std::size_t tick) {
    (void) tick;
    return;
}