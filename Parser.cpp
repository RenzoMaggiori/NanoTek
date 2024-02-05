/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser(const std::string &file) {
    
}

void Parser::parseChipset(const std::string &line) {
    if (line.empty()) return;

    std::istringstream iss(line);
    std::string type, name;

    if (!(iss >> type >> name)) throw Error("Invalid chipset format");

    _chipsets.push_back({name, type});
}

void Parser::parseLink(const std::string &line) {
    if (line.empty()) return;

    std::istringstream iss(line);
    std::string source, destination;
    char delimiter;
    size_t sourcePin, destinationPin;

    if (!(iss >> source >> sourcePin >> delimiter >> destination >> destinationPin)) throw Error("Invalid link format");

    _links.push_back({{source, sourcePin}, {destination, destinationPin}});
}

void Parser::parseFile(const std::string &file) {
    std::ifstream parseFile(file);
    std::string line;
    ParseState state = ParseState::NONE;

    if (!parseFile.is_open()) throw Error("File does not exist.");

    bool parsingChipsets = false, parsingLinks = false;

    while (std::getline(parseFile, line)) {
        if (line == ".chipsets:") {
            parsingChipsets = true;
            parsingLinks = false;
            continue;
        } else if (line == ".links:") {
            parsingChipsets = false;
            parsingLinks = true;
            continue;
        }

        if (parsingChipsets)
            parseChipset(line);
        else if (parsingLinks)
            parseLink(line);
    }
}