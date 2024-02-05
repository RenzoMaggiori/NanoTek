/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class Circuit: public AComponent {
        public:
            Circuit();
            pinType getPinType(std::size_t pin) override;
            void updateOutputPin() override;
            void setLink(std::size_t pin, IComponent &component, std::size_t componentPin) override;
            Tristate compute(std::size_t pin) override;
        protected:
        private:
        std::map<std::size_t, IComponent &> _components;
    };
}

#endif /* !CIRCUIT_HPP_ */
