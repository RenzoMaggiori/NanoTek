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
    std::cout << "tick: " << _ticks << std::endl << "input(s):" << std::endl;
    for (auto &it: _components) {
        nts::Tristate status = it.second->compute(1);
        std::cout << "  " << it.first << ": " << ((status == nts::Tristate::Undefined) ? "U" : std::to_string(status))  << std::endl;
    }
}