/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser(const std::string &file) {
    parseFile(file);
}

void Parser::parseChipset(const std::string &line) {
    if (line.empty()) return;

    std::istringstream iss(line);
    std::string type, name;

    if (!(iss >> type >> name)) throw Error("Invalid chipset format");

    _chipsets.push_back({type, name});
}

void Parser::parseLink(const std::string &line) {
    if (line.empty()) return;
    std::istringstream iss(line);
    std::string source, destination, token;
    size_t pin, destinationPin;

    if (std::getline(iss, token, ' ')) {
        auto colonPos = token.find(':');
        if (colonPos != std::string::npos) {
            source = token.substr(0, colonPos);
            pin = std::stoull(token.substr(colonPos + 1));
        }
    }

    if (std::getline(iss, token, ' ')) {
        auto colonPos = token.find(':');
        if (colonPos != std::string::npos) {
            destination = token.substr(0, colonPos);
            destinationPin = std::stoull(token.substr(colonPos + 1));
        }
    }

    _links.push_back({{source, pin}, {destination, destinationPin}});
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