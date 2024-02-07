/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Factory
*/

#include "Factory.hpp"

Factory::Factory() {
    _creators["4001"] = [this]() { return this->create4001(); };
    _creators["4011"] = [this]() { return this->create4011(); };
    _creators["4030"] = [this]() { return this->create4030(); };
    _creators["4069"] = [this]() { return this->create4069(); };
    _creators["4071"] = [this]() { return this->create4071(); };
    _creators["4081"] = [this]() { return this->create4081(); };

    _creators["input"] = [this]() { return this->createInput(); };
    _creators["output"] = [this]() { return this->createOutput(); };
    _creators["true"] = [this]() { return this->createTrue(); };
    _creators["false"] = [this]() { return this->createFalse(); };
    _creators["clock"] = [this]() { return this->createClock(); };

    _creators["or"] = [this]() { return this->createOr(); };
    _creators["nor"] = [this]() { return this->createNor(); };
    _creators["xor"] = [this]() { return this->createXor(); };
    _creators["not"] = [this]() { return this->createNot(); };
    _creators["and"] = [this]() { return this->createAnd(); };
    _creators["nand"] = [this]() { return this->createNand(); };
}

// chipsets

std::unique_ptr<nts::IComponent> Factory::create4001() const {
    return std::make_unique<nts::Chipset4001>();
}

std::unique_ptr<nts::IComponent> Factory::create4011() const {
    return std::make_unique<nts::Chipset4011>();
}

std::unique_ptr<nts::IComponent> Factory::create4030() const {
    return std::make_unique<nts::Chipset4030>();
}

std::unique_ptr<nts::IComponent> Factory::create4069() const {
    return std::make_unique<nts::Chipset4069>();
}

std::unique_ptr<nts::IComponent> Factory::create4071() const {
    return std::make_unique<nts::Chipset4071>();
}

std::unique_ptr<nts::IComponent> Factory::create4081() const {
    return std::make_unique<nts::Chipset4081>();
}

// special

std::unique_ptr<nts::IComponent> Factory::createInput() const {
    return std::make_unique<nts::InputComponent>();
}

std::unique_ptr<nts::IComponent> Factory::createOutput() const {
    return std::make_unique<nts::OutputComponent>();
}

std::unique_ptr<nts::IComponent> Factory::createTrue() const {
    return std::make_unique<nts::TrueComponnet>();
}

std::unique_ptr<nts::IComponent> Factory::createFalse() const {
    return std::make_unique<nts::FalseComponent>();
}

std::unique_ptr<nts::IComponent> Factory::createClock() const {
    return std::make_unique<nts::ClockComponent>();
}

// elementary

std::unique_ptr<nts::IComponent> Factory::createOr() const {
    return std::make_unique<nts::OrComponent>();
}

std::unique_ptr<nts::IComponent> Factory::createNot() const {
    return std::make_unique<nts::NotComponent>();
}

std::unique_ptr<nts::IComponent> Factory::createNor() const {
    return std::make_unique<nts::NorComponent>();
}

std::unique_ptr<nts::IComponent> Factory::createXor() const {
    return std::make_unique<nts::XorComponent>();
}

std::unique_ptr<nts::IComponent> Factory::createAnd() const {
    return std::make_unique<nts::AndComponent>();
}

std::unique_ptr<nts::IComponent> Factory::createNand() const {
    return std::make_unique<nts::NandComponent>();
}

// create

std::unique_ptr<nts::IComponent> Factory::createComponent(const std::string &type) {
    auto it = _creators.find(type);
    if (it != _creators.end())
        return it->second();

    throw Error("Unknown component type: " + type);
}

