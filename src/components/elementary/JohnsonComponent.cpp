/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** JohnsonComponent
*/

#include "JohnsonComponent.hpp"

nts::JohnsonComponent::JohnsonComponent() {
    nts::pinType type = nts::pinType::INPUT;

    for (size_t i = 1; i < 15; i++) {
        if (i == 4)
            type = nts::pinType::OUTPUT;
        std::shared_ptr<nts::Tristate> status;
        status = std::make_shared<nts::Tristate>(Tristate::Undefined);
        _pins[i].first = status;
        _pins[i].second = type;
    }
}

void nts::JohnsonComponent::simulate(std::size_t tick) {
    (void) tick;
    Tristate clock = *_pins[1].first.get();
    Tristate reset = *_pins[3].first.get();

    if (_prevClock == Tristate::Undefined) {
        for (std::size_t i = 1; i < 11; i++)
            *_pins[i + 3].first.get() = Tristate::False;
    }
    if (reset == Tristate::True || _currentCount == 10) {
        if (_currentCount != 0)
            *_pins[_currentCount + 3].first.get() = Tristate::False;
        _currentCount = 0;
        return;
    }
    if (clock == Tristate::False) {
        if(_currentCount + 1 != 11)
            *_pins[_currentCount + 4].first.get() = Tristate::True;
        if (_currentCount != 0)
            *_pins[_currentCount + 3].first.get() = Tristate::False;
        _currentCount++;
    }
    if (_currentCount > 5)
        *_pins[14].first.get() = Tristate::True;
    else
        *_pins[14].first.get() = Tristate::False;
    _prevClock = clock;
}