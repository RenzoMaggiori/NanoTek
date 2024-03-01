/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** JohnsonComponent
*/

#ifndef JOHNSONCOMPONENT_HPP_
#define JOHNSONCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class JohnsonComponent: public AComponent {
        public:
            JohnsonComponent();
            void simulate(std::size_t tick) override;
        protected:
        private:
            Tristate _prevClock = Tristate::Undefined;
            std::size_t _currentCount = 0;
    };
}

#endif /* !JOHNSONCOMPONENT_HPP_ */
