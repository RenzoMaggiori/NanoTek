/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Factory
*/

#include "Factory.hpp"

nts::Factory::Factory() {
    _creators["4001"] = []() { return std::make_unique<nts::Chipset4001>(); };
    _creators["4008"] = []() { return std::make_unique<nts::Chipset4008>(); };
    _creators["4011"] = []() { return std::make_unique<nts::Chipset4011>(); };
    _creators["4013"] = []() { return std::make_unique<nts::Chipset4013>(); };
    _creators["4017"] = []() { return std::make_unique<nts::Chipset4017>(); };
    _creators["4030"] = []() { return std::make_unique<nts::Chipset4030>(); };
    _creators["4040"] = []() { return std::make_unique<nts::Chipset4040>(); };
    _creators["4069"] = []() { return std::make_unique<nts::Chipset4069>(); };
    _creators["4071"] = []() { return std::make_unique<nts::Chipset4071>(); };
    _creators["4081"] = []() { return std::make_unique<nts::Chipset4081>(); };
    _creators["4512"] = []() { return std::make_unique<nts::Chipset4512>(); };
    _creators["2716"] = []() { return std::make_unique<nts::Chipset2716>(); };
    _creators["4801"] = []() { return std::make_unique<nts::Chipset4801>(); };

    _creators["input"] = []() { return std::make_unique<nts::InputComponent>(); };
    _creators["output"] = []() { return std::make_unique<nts::OutputComponent>(); };
    _creators["true"] = []() { return std::make_unique<nts::TrueComponnet>(); };
    _creators["false"] = []() { return std::make_unique<nts::FalseComponent>(); };
    _creators["clock"] = []() { return std::make_unique<nts::ClockComponent>(); };
    _creators["logger"] = []() { return std::make_unique<nts::LoggerComponent>(); };

    _creators["or"] = []() { return std::make_unique<nts::OrComponent>(); };
    _creators["nor"] = []() { return std::make_unique<nts::NorComponent>(); };
    _creators["xor"] = []() { return std::make_unique<nts::XorComponent>(); };
    _creators["not"] = []() { return std::make_unique<nts::NotComponent>(); };
    _creators["and"] = []() { return std::make_unique<nts::AndComponent>(); };
    _creators["nand"] = []() { return std::make_unique<nts::NandComponent>(); };
}
// create

std::unique_ptr<nts::IComponent> nts::Factory::createComponent(const std::string &type) {
    auto it = _creators.find(type);
    if (it != _creators.end())
        return it->second();

    throw nts::Error("Unknown component type: " + type);
}
