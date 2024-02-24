/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** FlipflopComponent
*/

#ifndef FLIPFLOPCOMPONENT_HPP_
#define FLIPFLOPCOMPONENT_HPP_

#include "../../AComponent.hpp"

namespace nts {
    class FlipflopComponent: public AComponent {
        public:
            FlipflopComponent();
            void simulate(std::size_t tick) override;
            void set(bool value);
        protected:
        private:
            Tristate _prevClock = Tristate::Undefined;
    };
}

#endif /* !FLIPFLOPCOMPONENT_HPP_ */
