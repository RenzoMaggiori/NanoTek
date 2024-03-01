/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AndComponent
*/

#ifndef ANDCOMPONENT_HPP_
#define ANDCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class AndComponent: public AComponent {
        public:
            AndComponent();
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif