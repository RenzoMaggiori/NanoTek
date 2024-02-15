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
#include <sstream>

namespace nts {
    class Circuit: public IComponent {
        public:
            class Error;

            Circuit() = default;

            std::map<std::string, std::unique_ptr<nts::IComponent>> &getComponents();
            void addComponent(std::string name, std::unique_ptr<nts::IComponent> component);
            void createLinks(std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> links);
            nts::Tristate compute(std::size_t pin) override;
            void setLink(std::size_t pin, nts::IComponent & other, std ::size_t otherPin) override;
            void simulate(std::size_t ticks) override;
            void display();
            std::size_t getTicks() const;
            void setComponentsStatus(std::string status);
        protected:
        private:
            std::map<std::string, nts::Tristate> _inputStatus;
            std::size_t _ticks = 0;
            std::map<std::string, std::unique_ptr<nts::IComponent>> _components;
    };
}

#endif /* !CIRCUIT_HPP_ */