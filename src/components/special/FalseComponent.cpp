/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** FalseComponent
*/

#include "FalseComponent.hpp"

nts::FalseComponent::FalseComponent() {
    this->getPins()[1].first = std::make_shared<nts::Tristate>(Tristate::False);
    this->getPins()[1].second = nts::OUTPUT;
    _type = pinType::NONE;
}

void nts::FalseComponent::simulate(std::size_t tick) {
    (void) tick;
    return;
}