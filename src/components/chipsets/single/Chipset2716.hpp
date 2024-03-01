/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset2716
*/

#ifndef CHIPSET2716_HPP_
#define CHIPSET2716_HPP_

#include "AComponent.hpp"

namespace nts {
    class Chipset2716 : public AComponent {
        public:
            Chipset2716();
            void simulate(std::size_t tick) override;
            void readMode(int address);
            void programMode(int address);
            int getAddress();
        private:
        uint8_t _memory[2048];
    };
}

#endif /* !CHIPSET2716_HPP_ */
