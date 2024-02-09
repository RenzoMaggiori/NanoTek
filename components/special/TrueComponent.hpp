/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** TrueComponent
*/

#ifndef TRUECOMPONENT_HPP_
#define TRUECOMPONENT_HPP_

#include "../../AComponent.hpp"

namespace nts {
    class TrueComponnet: public AComponent {
        public:
            TrueComponnet();
            pinType getPinType(std::size_t pin) override;
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif