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
#include <vector>
#include<algorithm>

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

void nts::Circuit::simulate(std::size_t ticks) {
    AComponent* derivedComponent = nullptr;
    std::vector<std::string> removeUpdated;

    for (auto &update: _inputStatus) {
        if (_components.find(update.first) != _components.end()) {
            derivedComponent = dynamic_cast<AComponent*>(_components.find(update.first)->second.get());
            if (derivedComponent->getType() != nts::pinType::INPUT) throw nts::Error("Invalid component match");
            derivedComponent->setInput(update.second);
            removeUpdated.push_back(update.first);
        } else
            throw nts::Error("Invalid component match");
    }
    for (const auto &key : removeUpdated)
        _inputStatus.erase(key);
    derivedComponent = nullptr;
    for (auto &component: _components) {
        derivedComponent = dynamic_cast<AComponent*>(component.second.get());
        derivedComponent->simulate(ticks);
    }
    _ticks = ticks;
}

nts::Tristate nts::Circuit::compute(std::size_t pin) {
    (void) pin;
    return Tristate::Undefined;
}

void nts::Circuit::setLink(std::size_t pin, nts::IComponent & other, std ::size_t otherPin) {
    (void) pin;
    (void) other;
    (void) otherPin;
}

std::size_t nts::Circuit::getTicks() const {
    return _ticks;
}

void nts::Circuit::setComponentsStatus(std::string line) {
    if (line.empty()) return;
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    std::istringstream iss(line);
    std::string source, token, pin;
    Tristate pinValue = Tristate::Undefined;

    if (std::getline(iss, token, ' ')) {
        auto colonPos = token.find('=');
        if (colonPos != std::string::npos) {
            source = token.substr(0, colonPos);
            pin = token.substr(colonPos + 1);
            if (pin == "1")
                pinValue = Tristate::True;
            else if (pin == "0")
                pinValue = Tristate::False;
            else if (pin == "U")
                pinValue = Tristate::Undefined;
            else
                throw nts::Error("Invalid input value");
        }
    }
    _inputStatus[source] = pinValue;
}