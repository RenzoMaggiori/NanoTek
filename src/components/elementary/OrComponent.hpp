/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** OrComponent
*/

#ifndef ORCOMPONENT_HPP_
#define ORCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class OrComponent: public AComponent {
        public:
            OrComponent();
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !ORCOMPONENT_HPP_ */
