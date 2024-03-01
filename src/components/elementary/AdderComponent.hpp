/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** AdderComponent
*/

#ifndef ADDERCOMPONENT_HPP_
#define ADDERCOMPONENT_HPP_

#include "AComponent.hpp"

namespace nts {
    class AdderComponent: public AComponent {
        public:
            AdderComponent();
            void simulate(std::size_t tick) override;
        protected:
        private:
    };
}

#endif /* !ADDERCOMPONENT_HPP_ */

