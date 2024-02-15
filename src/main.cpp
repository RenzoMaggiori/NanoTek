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

void loopProgram(std::string line, nts::Circuit *circuit)
{
    while (std::getline(std::cin, line)) {
        if (line == "display")
            circuit->display();
        if (line == "simulate")
            circuit->simulate(circuit->getTicks() + 1);
        if (std::strstr(line.c_str(), "="))
            circuit->setComponentsStatus(line);
        if (line == "loop") {
            while (1) {
                circuit->simulate(circuit->getTicks() + 1);
                circuit->display();
            }
        }
        if (line == "exit")
            break;
        std::cout << "> ";
    }
}

int initProgram(const char *argv[])
{
    try {
        nts::Parser parser = nts::Parser((argv[1] ? argv[1] : ""));
        nts::Factory factory = nts::Factory();
        nts::Circuit *circuit = new nts::Circuit();
        std::deque<std::pair<std::string, std::string>> chipsets = parser.getChipsets();
        std::string line;
        //Create components and links
        for (auto &chip: chipsets)
            circuit->addComponent(chip.second, factory.createComponent(chip.first));
        std::cout << "> ";
        circuit->createLinks(parser.getLinks());
        //loop program
        loopProgram(line, circuit);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

int main(int argc, const char *argv[])
{
    return (initProgram(argv));
}
