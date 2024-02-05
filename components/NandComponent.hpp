/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** NandComponent
*/

#ifndef NANDCOMPONENT_HPP_
#define NANDCOMPONENT_HPP_

#include "../AComponent.hpp"

namespace nts {
    class NandComponent: public AComponent {
        public:
            NandComponent();
            pinType getPinType(std::size_t pin) override;
            void updateOutputPin() override;
        protected:
        private:
    };
}

#endif /* !NANDCOMPONENT_HPP_ */
