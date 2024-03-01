/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4801
*/

#ifndef CHIPSET4801_HPP_
#define CHIPSET4801_HPP_

#include "AComponent.hpp"

namespace nts {
    class Chipset4801 : public AComponent {
        public:
            Chipset4801();
            void simulate(std::size_t tick) override;
            void readMode(int address);
            void writeMode(int address);
            int getAddress();
        private:
        uint8_t _memory[1024];
    };
}

#endif /* !CHIPSET4801_HPP_ */
