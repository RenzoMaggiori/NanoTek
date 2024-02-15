/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include <exception>
#include <memory>
#include <map>

namespace nts {
    enum pinType {
        INPUT,
        OUTPUT,
        NONE
    };
    class AComponent:public IComponent {
        protected:
            pinType _type = pinType::NONE;
            std::map<std::size_t, std::pair<std::shared_ptr<nts::Tristate>, nts::pinType>> _pins;
        public:
            // Nested
            class Error;
            // Virtual
            virtual pinType getPinType(std::size_t pin) = 0;
            virtual void setInput(nts::Tristate);

            // Setters
            virtual void setLink(std::size_t pin, IComponent &component, std::size_t componentPin) override;

            // Getters
            virtual std::pair<std::shared_ptr<nts::Tristate>, nts::pinType> getPin(std::size_t pin);
            std::map<std::size_t, std::pair<std::shared_ptr<nts::Tristate>, nts::pinType>> &getPins();
            pinType getType() const;

            // Member
            virtual void simulate(std::size_t tick) override;
            virtual Tristate compute(std::size_t pin) override;

        private:
    };
}

#endif
