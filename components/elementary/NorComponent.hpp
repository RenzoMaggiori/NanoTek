/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** NorComponent
*/

#ifndef NORCOMPONENT_HPP_
#define NORCOMPONENT_HPP_

#include "../../AComponent.hpp"

namespace nts {
    class NorComponent: public AComponent {
        public:
            NorComponent();
            pinType getPinType(std::size_t pin) override;
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !NORCOMPONENT_HPP_ */
