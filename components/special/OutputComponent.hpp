/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** OutputComponent
*/

#ifndef OUTPUTCOMPONENT_HPP_
#define OUTPUTCOMPONENT_HPP_

#include "../../AComponent.hpp"

namespace nts {
    class OutputComponent: public AComponent {
        public:
            OutputComponent();
            pinType getPinType(std::size_t pin) override;
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !OUTPUTCOMPONENT_HPP_ */
