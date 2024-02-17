/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include <cstddef>
#include <exception>
#include <memory>
#include <map>

namespace nts {
    enum pinType {
        INPUT,
        OUTPUT,
        NONE
    };
    typedef std::pair<std::shared_ptr<nts::Tristate>, nts::pinType> pinsPairType;
    typedef std::map<std::size_t, nts::pinsPairType> pinsMapType;
    class AComponent:public IComponent {
        protected:
            pinType _type = pinType::NONE;
            nts::pinsMapType _pins;
            IComponent *_outputLink = nullptr;
        public:
            std::size_t _priority = 0;
            // Nested
            class Error;
            // Virtual
            virtual pinType getPinType(std::size_t pin) = 0;
            virtual void setInput(nts::Tristate);

            // Setters
            virtual void setLink(std::size_t pin, IComponent &component, std::size_t componentPin) override;
            virtual void setOutputLink(IComponent &component);
            // Getters
            virtual nts::pinsPairType &getPin(std::size_t pin);
            nts::pinsMapType &getPins();
            pinType getType() const;
            virtual IComponent *getOutputLink();

            // Member
            virtual void simulate(std::size_t tick) override;
            virtual Tristate compute(std::size_t pin) override;

        private:
    };
}

#endif
