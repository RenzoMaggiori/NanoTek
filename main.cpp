/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** main
*/

#include "Parser.hpp"
#include "Factory.hpp"
#include "circuits/Circuit.hpp"
#include <cstring>
#include <iostream>
int main(int argc, const char *argv[]) {
    Parser *parser = new Parser((argv[1] ? argv[1] : ""));
    Factory *factory = new Factory();
    nts::Circuit *circuit = new nts::Circuit();
    std::deque<std::pair<std::string, std::string>> chipsets = parser->getChipsets();

    std::string line;

    for (auto &chip: chipsets)
        circuit->addComponent(chip.second, factory->createComponent(chip.first));
    std::cout << "> ";
    circuit->createLinks(parser->getLinks());
    while (std::getline(std::cin, line)) {
        if (line == "display")
            circuit->display();
        if (line == "simulate")
            circuit->simulate(circuit->getTicks() + 1);
        if (std::strstr(line.c_str(), "="))
            circuit->setComponentsStatus(line);
        if (line == "exit")
            break;
        std::cout << "> ";
    }

    delete parser;
    delete factory;
    delete circuit;
    return 0;
}
