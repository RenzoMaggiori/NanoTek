/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** NotComponent
*/

#ifndef NOTCOMPONENT_HPP_
#define NOTCOMPONENT_HPP_

#include "../../AComponent.hpp"

namespace nts {
    class NotComponent: public AComponent {
        public:
            NotComponent();
            pinType getPinType(std::size_t pin) override;
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !NOTCOMPONENT_HPP_ */
