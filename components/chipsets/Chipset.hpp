/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Chipset
*/

#ifndef CHIPSET_HPP_
#define CHIPSET_HPP_

#include "../../AComponent.hpp"
#include <memory>

namespace nts {
    class Chipset: public AComponent {
        public:
            Chipset() = default;
            pinType getPinType(std::size_t pin) override;
            void simulate(std::size_t tick) override;
            virtual void setLink(std::size_t pin, IComponent &component, std::size_t componentPin) override;
            Tristate compute(std::size_t pin) override;
            std::pair<std::shared_ptr<nts::Tristate>, nts::pinType> getPin(std::size_t pin) override;
        protected:
            std::map<std::size_t, std::unique_ptr<nts::IComponent>> _components;
        private:
    };
}

#endif /* !CHIPSET_HPP_ */
