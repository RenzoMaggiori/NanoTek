/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** CounterComponent
*/

#include "CounterComponent.hpp"

nts::CounterComponent::CounterComponent()
{
    nts::pinType type = nts::pinType::OUTPUT;

    for (size_t i = 1; i < 17; i++) {
        if (i == 10 || i == 11)
            type = nts::pinType::INPUT;
        else
            type = nts::pinType::OUTPUT;
        _pins[i].first = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i].second = type;
    }
}

void nts::CounterComponent::updateOutputPins() {
    for (int i = 1; i < 17; ++i) {
        if (i == 10 || i == 11 || i == 8 || i == 16)
            continue;
        Tristate value = (_counter >> i) & 0x01 ? Tristate::True : Tristate::False;
        *_pins[i].first.get() = value;
    }
}

void nts::CounterComponent::simulate(std::size_t tick) {
    (void)tick; 

    Tristate clock = *_pins[10].first.get();
    Tristate reset = *_pins[11].first.get();

    if (reset == Tristate::True)
        _counter = 0;
    else if (clock == Tristate::True && _prevClock == Tristate::False) {
        _counter++;
        if (_counter >= 4096)
            _counter = 0;
    }
    _prevClock = clock;
    updateOutputPins();
}