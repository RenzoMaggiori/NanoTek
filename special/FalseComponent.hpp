/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** FalseComponent
*/

#ifndef FALSECOMPONENT_HPP_
#define FALSECOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts
{
    class FalseComponent: public AComponent{
        public:
            FalseComponent();
            pinType getPinType(std::size_t pin) override;
            void updateOutputPin() override;
        protected:
        private:
    };
}

#endif /* !FALSECOMPONENT_HPP_ */
