/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** ClockComponent
*/

#ifndef CLOCKCOMPONENT_HPP_
#define CLOCKCOMPONENT_HPP_

#include "../../AComponent.hpp"

namespace nts {
    class ClockComponent: public AComponent {
        public:
            ClockComponent();
            pinType getPinType(std::size_t pin) override;
            void updateOutputPin() override;
            void setInput(nts::Tristate) override;
        protected:
        private:
    };
}
#endif /* !CLOCKCOMPONENT_HPP_ */
