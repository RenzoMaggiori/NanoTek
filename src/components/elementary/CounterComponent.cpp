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
    for (size_t pin = 1; pin <= 15; ++pin) {
        if (pin == 8 || pin == 10 || pin == 11)
            continue;
        size_t bitPosition;
        switch (pin) {
            case 1: bitPosition = 12; break;
            case 2: bitPosition = 6; break;
            case 3: bitPosition = 5; break;
            case 4: bitPosition = 7; break;
            case 5: bitPosition = 4; break;
            case 6: bitPosition = 3; break;
            case 7: bitPosition = 2; break;
            case 9: bitPosition = 1; break;
            case 12: bitPosition = 9; break;
            case 13: bitPosition = 8; break;
            case 14: bitPosition = 10; break;
            case 15: bitPosition = 11; break;
            default: continue;
        }
        Tristate value = (_counter >> (bitPosition - 1)) & 1 ? Tristate::True : Tristate::False;
        *_pins[pin].first.get() = value;
    }
}

void nts::CounterComponent::simulate(std::size_t tick) {
    (void)tick;

    Tristate clock = *_pins[10].first.get();
    Tristate reset = *_pins[11].first.get();

    if (reset == Tristate::True) {
        _counter = 0;
    } else if (clock == Tristate::False) {
        if (_counter < 0xFFF)
            _counter++;
        else
            _counter = 0;
    }
    updateOutputPins();
    _prevClock = clock;
}