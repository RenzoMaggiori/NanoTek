/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include <memory>
#include <iostream>
#include <string>


void nts::Circuit::addComponent(std::string name, std::unique_ptr<nts::IComponent> component) {
    _components[name] = (std::move(component));
}

std::map<std::string, std::unique_ptr<nts::IComponent>> &nts::Circuit::getComponents() {
    return _components;
}

void nts::Circuit::display() {
    AComponent* derivedComponent = nullptr;
    std::cout << "tick: " << _ticks << std::endl << "input(s):" << std::endl;
    nts::pinType type = nts::pinType::INPUT;

    for (std::size_t i = 0; i < 2; i++) {
        if (type == nts::pinType::OUTPUT)
            std::cout << "output(s):" << std::endl;

        for (auto &it: _components) {
            derivedComponent = dynamic_cast<AComponent*>(it.second.get());
            if(derivedComponent->getType() == type) {
                nts::Tristate status = it.second->compute(1);
                std::cout << "  " << it.first << ": " << ((status == nts::Tristate::Undefined) ? "U" : std::to_string(status))  << std::endl;
            }
        }
        type = nts::pinType::OUTPUT;
    }
}

void nts::Circuit::createLinks(std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> links) {
    for (auto &link: links) {
        auto &source = link.first.first;
        auto &sourcePin = link.first.second;
        auto &destination = link.second.first;
        auto &destinationPin = link.second.second;

        if (_components.find(source) != _components.end() && _components.find(destination) != _components.end()) {
            _components[destination]->setLink(destinationPin, *_components[source].get(), sourcePin);
        }
    }
}