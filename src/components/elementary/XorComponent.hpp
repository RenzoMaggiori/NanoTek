/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** XorComponent
*/

#ifndef XORCOMPONENT_HPP_
#define XORCOMPONENT_HPP_

#include "../../AComponent.hpp"

namespace nts {
    class XorComponent: public AComponent{
        public:
            XorComponent();
            pinType getPinType(std::size_t pin) override;
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !XORCOMPONENT_HPP_ */
