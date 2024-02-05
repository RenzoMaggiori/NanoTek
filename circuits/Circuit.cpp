/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include <memory>


void nts::Circuit::addComponent(std::string name, std::unique_ptr<nts::IComponent> component) {
    _components[name] = (std::move(component));
}

std::map<std::string, std::unique_ptr<nts::IComponent>> &nts::Circuit::getComponents() {
    return _components;
}