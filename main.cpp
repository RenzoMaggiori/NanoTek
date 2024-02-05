/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** main
*/

#include "Parser.hpp"
#include "Factory.hpp"
#include "circuits/Circuit.hpp"

int main(int argc, const char *argv[]) {
    Parser *parser = new Parser((argv[1] ? argv[1] : ""));
    Factory *factory = new Factory();
    nts::Circuit *circuit = new nts::Circuit();
    std::deque<std::pair<std::string, std::string>> chipsets = parser->getChipsets();

    std::string line;

    for (auto &chip: chipsets)
        circuit->addComponent(chip.second, factory->createComponent(chip.first));
    factory->createLinks(circuit->getComponents(), parser->getLinks());
    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        if (line == "display") {
            circuit->display();
        }
        std::cout << "> ";
    }

    delete parser;
    delete factory;
    delete circuit;
    return 0;
}
