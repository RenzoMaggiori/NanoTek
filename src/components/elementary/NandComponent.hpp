/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** NandComponent
*/

#ifndef NANDCOMPONENT_HPP_
#define NANDCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class NandComponent: public AComponent {
        public:
            NandComponent();
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !NANDCOMPONENT_HPP_ */
