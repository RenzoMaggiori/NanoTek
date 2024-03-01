/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset4008
*/

#ifndef CHIPSET4008_HPP_
#define CHIPSET4008_HPP_

#include "Chipset.hpp"


namespace nts {
    class Chipset4008: public Chipset {
        public:
            Chipset4008();
            void adder(int firstPin, bool comp, int andPin1, int andPin2);
        protected:
        private:
    };
}

#endif /* !CHIPSET4008_HPP_ */
