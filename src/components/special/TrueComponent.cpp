/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"

nts::TrueComponnet::TrueComponnet() {
    this->getPins()[1].first = std::make_shared<nts::Tristate>(Tristate::True);
    this->getPins()[1].second = nts::OUTPUT;
    _type = pinType::NONE;
}

void nts::TrueComponnet::simulate(std::size_t tick) {
    (void) tick;
    return;
}