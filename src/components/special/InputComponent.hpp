/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

#include "../../AComponent.hpp"

namespace nts {
    class InputComponent: public AComponent {
        public:
            InputComponent();
            pinType getPinType(std::size_t pin) override;
            void simulate(std::size_t tick) override;
            void setInput(nts::Tristate) override;
        protected:
        private:
    };
}

#endif
