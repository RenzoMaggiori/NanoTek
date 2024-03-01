/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** FalseComponent
*/

#ifndef FALSECOMPONENT_HPP_
#define FALSECOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts
{
    class FalseComponent: public AComponent{
        public:
            FalseComponent();
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !FALSECOMPONENT_HPP_ */
