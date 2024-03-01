/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** LoggerComponent
*/

#ifndef LOGGERCOMPONENT_HPP_
#define LOGGERCOMPONENT_HPP_

#include "AComponent.hpp"
#include <fstream>

namespace nts {
    class LoggerComponent: public AComponent {
        public:
            LoggerComponent();
            void simulate(std::size_t tick) override;
            int getByte();
        protected:
        private:
        std::ofstream _logger;
        Tristate _prevClock = Tristate::Undefined;
    };
}


#endif /* !LOGGERCOMPONENT_HPP_ */
