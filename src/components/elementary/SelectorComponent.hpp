/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** SelectorComponent
*/

#ifndef SELECTORCOMPONENT_HPP_
#define SELECTORCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class SelectorComponent: public AComponent {
        public:
            SelectorComponent();
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !SELECTORCOMPONENT_HPP_ */
