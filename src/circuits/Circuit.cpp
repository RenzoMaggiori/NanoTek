/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Circuit
*/

#include "Circuit.hpp"
#include <cstddef>
#include <iterator>
#include <map>
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

std::map<nts::AComponent*, std::size_t> nts::Circuit::loopThroughLinks(nts::AComponent *castComponent,
    std::map<nts::AComponent*, std::size_t> &componentMap, std::size_t priority)
{
    for (unsigned int i = 0; i < castComponent->getOutputLink().size(); i++) {
        AComponent* nextComponent = static_cast<AComponent*>(castComponent->getOutputLink()[i]);
        if (nextComponent->getPriority() <= priority) {
            auto it = componentMap.find(nextComponent);
            if (it != componentMap.end()) {
                componentMap.erase(it);
            }
            priority++;
            nextComponent->setPriority(priority);
            componentMap.insert({nextComponent, priority});
        }
        componentMap = loopThroughLinks(nextComponent, componentMap, priority);
    }
    return componentMap;
}

void nts::Circuit::setSortedComponents() {
    AComponent *castComponent = nullptr;
    std::map<nts::AComponent*, std::size_t> componentMap;

    //Loop all components
    for (auto &component : _components) {
        castComponent = static_cast<AComponent*>(component.second.get());
        //Acces ONLY the ones which are of type INPUT e.g.(True, False, Clock, ...)
        if (castComponent->getPins().size() == 1) {
            castComponent->setPriority(1); // 1
            componentMap.insert({castComponent, 1});
            //Iterate over all the links setting the priority n + 1 e.g. (True(1)->Not(2)->And(3)...)
            componentMap = loopThroughLinks(castComponent, componentMap, 1);
        }
    }
    //Insert the components into a multimap sorted by priority
    for (auto &component : componentMap) {
        this->_sortedComponents. insert({component.second, component.first});
    }
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
            if(derivedComponent->getType() == type ) {
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
    setSortedComponents();
}

void nts::Circuit::simulate(std::size_t ticks) {
    AComponent* derivedComponent = nullptr;
    std::vector<std::string> removeUpdated;
    for (auto &update: _inputStatus) {
        if (_components.find(update.first) != _components.end()) {
            derivedComponent = dynamic_cast<AComponent*>(_components.find(update.first)->second.get());
            if (derivedComponent->setInput(update.second) == false)
                    throw nts::Error("Invalid component match");
            else
                removeUpdated.push_back(update.first);

        } else
            throw nts::Error("Invalid component match");
    }
    for (const auto &key : removeUpdated)
        _inputStatus.erase(key);
    derivedComponent = nullptr;
    for (auto &component: _sortedComponents) {
        component.second ->simulate(ticks);
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
    if (_components.find(source) !=_components.end())
        _inputStatus[source] = pinValue;
    else
        throw nts::Error("Invalid input value");
}