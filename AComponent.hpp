/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"
#include "Link.hpp"
#include <memory>
#include <vector>
#include <exception>

namespace nts {
    enum pinType {
        INPUT,
        OUTPUT,
        NONE
    };
    class AComponent: public IComponent {
        protected:
            std::map<std::size_t,  std::shared_ptr<Tristate>> _pins;
            std::map<std::size_t, std::shared_ptr<Link>> _links;
        public:
            // Nested
            class Error: public std::exception
            {
                private:
                    std::string _msg;
                public:
                    Error(std::string msg): _msg(msg) {}
                    const char *what() const noexcept override {
                        return _msg.c_str();
                    }
            };
            // Virtual
            virtual pinType getPinType(std::size_t pin) = 0;
            virtual void updateOutputPin() = 0;

            // Setters
            void setLink(std::size_t pin, IComponent &component, std::size_t componentPin) override;

            // Getters
            std::map<std::size_t, std::shared_ptr<nts::Tristate>> &getPins();
            std::map<std::size_t, std::shared_ptr<Link>> &getLinks();

            // Member
            // void simulate(std::size_t tick);
            Tristate compute(std::size_t pin);

        private:
    };
}

#endif
