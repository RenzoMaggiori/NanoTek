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
            void addComponent(std::string name, std::unique_ptr<nts::IComponent> component);
            std::map<std::string, std::unique_ptr<nts::IComponent>> &getComponents();
            void display();
            void createLinks(std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> links);

        protected:
        private:
        std::size_t _ticks = 0;
        std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
    };
}

#endif /* !CIRCUIT_HPP_ */
