/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "IComponent.hpp"
#include "circuits/Circuit.hpp"
#include "components/chipsets/Chipset4001.hpp"
#include "components/chipsets/Chipset4011.hpp"
#include "components/chipsets/Chipset4030.hpp"
#include "components/chipsets/Chipset4069.hpp"
#include "components/chipsets/Chipset4071.hpp"
#include "components/chipsets/Chipset4081.hpp"
#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "components/special/TrueComponent.hpp"
#include "components/special/FalseComponent.hpp"
#include <memory>
#include <map>
#include <functional>


class Factory {
    public:
        class Error: public std::exception {
            private:
                std::string _msg;
            public:
                Error(std::string msg): _msg(msg) {}
                const char *what() const noexcept override { return _msg.c_str(); }
        };

        Factory();

        void createLinks(std::map<std::string, std::unique_ptr<nts::IComponent>> components, std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> links);

        std::unique_ptr<nts::IComponent> createComponent(const std::string &type);
        std::unique_ptr<nts::IComponent> create4001() const;
        std::unique_ptr<nts::IComponent> create4011() const;
        std::unique_ptr<nts::IComponent> create4030() const;
        std::unique_ptr<nts::IComponent> create4069() const;
        std::unique_ptr<nts::IComponent> create4071() const;
        std::unique_ptr<nts::IComponent> create4081() const;
        std::unique_ptr<nts::IComponent> createInput() const;
        std::unique_ptr<nts::IComponent> createOutput() const;
        std::unique_ptr<nts::IComponent> createFalse() const;
        std::unique_ptr<nts::IComponent> createTrue() const;

    protected:
    private:
        std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> _creators;
};

#endif /* !FACTORY_HPP_ */
