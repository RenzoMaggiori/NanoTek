/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"

nts::TrueComponnet::TrueComponnet() {
    std::shared_ptr<nts::Tristate> status = std::make_shared<nts::Tristate>(Tristate::True);
    this->getPins()[1] = status;
}

nts::pinType nts::TrueComponnet::getPinType(std::size_t pin) {
    if (pin != 1) throw Error("Invalid pin.");
    return pinType::OUTPUT;
}

void nts::TrueComponnet::updateOutputPin() {
    return;
}