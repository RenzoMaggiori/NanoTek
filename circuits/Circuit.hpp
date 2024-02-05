/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Circuit
*/

#ifndef CIRCUIT_HPP_
#define CIRCUIT_HPP_

#include "../AComponent.hpp"
#include <deque>


namespace nts {
    class Circuit {
        public:
            Circuit() = default;
            void addComponent(std::unique_ptr<nts::IComponent> &component);
        protected:
        private:
        std::deque<std::unique_ptr<nts::IComponent>> _components;
    };
}

#endif /* !CIRCUIT_HPP_ */
