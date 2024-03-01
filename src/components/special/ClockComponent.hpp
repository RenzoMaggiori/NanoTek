/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** ClockComponent
*/

#ifndef CLOCKCOMPONENT_HPP_
#define CLOCKCOMPONENT_HPP_

#include "AComponent.hpp"
#include <cstddef>

namespace nts {
    class ClockComponent: public AComponent {
        public:
            ClockComponent();
            void simulate(std::size_t tick) override;
            bool setInput(nts::Tristate) override;
        protected:
        private:
            bool _availableTick = true;
    };
}
#endif /* !CLOCKCOMPONENT_HPP_ */
