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
#include <deque>
#include <memory>
#include <map>

namespace nts {
    enum pinType {
        INPUT,
        OUTPUT,
        HYBRID,
        NONE
    };
    typedef std::pair<std::shared_ptr<nts::Tristate>, nts::pinType> pinsPairType;
    typedef std::map<std::size_t, nts::pinsPairType> pinsMapType;
    class AComponent:public IComponent {
        protected:
            pinType _type = pinType::NONE;
            nts::pinsMapType _pins;
            std::deque<IComponent *> _outputLink;
            std::size_t _priority = 0;
        public:
            // Nested
            class Error;
            // Virtual
            virtual pinType getPinType(std::size_t pin);
            virtual bool setInput(nts::Tristate);
            void setPriority(std::size_t priority);

            // Setters
            virtual void setLink(std::size_t pin, IComponent &component, std::size_t componentPin) override;
            void setOutputLink(IComponent * outputLink);
            // Getters
            nts::pinsMapType &getPins();
            pinType getType() const;
            std::deque<IComponent *> getOutputLink();
            std::size_t getPriority() const;

            // Member
            virtual void simulate(std::size_t tick) override;
            virtual Tristate compute(std::size_t pin) override;

        private:
    };
}

#endif
