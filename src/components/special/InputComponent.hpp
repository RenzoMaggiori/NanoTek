/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class InputComponent: public AComponent {
        public:
            InputComponent();
            void simulate(std::size_t tick) override;
            bool setInput(nts::Tristate) override;
        protected:
        private:
    };
}

#endif
