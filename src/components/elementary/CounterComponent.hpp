/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** CounterComponent
*/

#ifndef COUNTERCOMPONENT_HPP_
#define COUNTERCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class CounterComponent: public AComponent {
        public:
            CounterComponent();
            void simulate(std::size_t tick) override;
            void updateOutputPins();
        protected:
        private:
            std::size_t _counter = 0;
            Tristate _prevClock = Tristate::Undefined;
    };
}

#endif /* !COUNTERCOMPONENT_HPP_ */
