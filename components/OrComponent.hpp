/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** OrComponent
*/

#ifndef ORCOMPONENT_HPP_
#define ORCOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class OrComponent: public AComponent {
        public:
            OrComponent();
            pinType getPinType(std::size_t pin) override;
            void updateOutputPin() override;
        protected:
        private:
    };
}

#endif /* !ORCOMPONENT_HPP_ */
