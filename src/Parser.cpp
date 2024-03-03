/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Parser
*/

#include "Parser.hpp"
#include "IComponent.hpp"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

nts::Parser::Parser(const std::string &file) {
    if (file == "") throw nts::Error("File does not exist");
    parseFile(file);
}

void nts::Parser::parseChipset(const std::string &line) {
    if (line.empty() || line[0] == '#') return;

    std::istringstream iss(line);
    std::string type, name;

    if (!(iss >> type >> name)) throw nts::Error("Invalid chipset format");

    for (auto &it: _chipsets) {
        if (it.second == name) throw nts::Error("Invalid chipset format");
    }
    _chipsets.push_back({type, name});
}

std::string& ltrim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](char ch) {
        return !std::isspace(ch, std::locale::classic());
    }));
    return str;
}

std::string& rtrim(std::string& str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](char ch) {
        return !std::isspace(ch, std::locale::classic());
    }).base(), str.end());
    return str;
}

void nts::Parser::existingComponent(std::string source, std::string destination)
{
    bool destinationName = false;
    bool sourceName = false;

    for (auto &it: _chipsets) {
        if (it.second == source)
            sourceName = true;
        if (it.second == destination)
            destinationName = true;
    }
    if (!sourceName || !destinationName) throw nts::Error("Invalid chipset format");

}

std::pair<std::string, std::size_t> nts::Parser::parseChipsetLink(std::istringstream &iss)
{
    std::string token;
    std::pair<std::string, std::size_t> link;

    if (std::getline(iss, token, ' ')) {
        auto colonPos = token.find(':');
        if (colonPos != std::string::npos) {
            link.first = token.substr(0, colonPos);
            link.second = std::stoull(token.substr(colonPos + 1));
        }
    }
    return link;
}

void nts::Parser::parseLink(const std::string& line) {
    if (line.empty() || line[0] == '#') return;
    std::istringstream iss(line);
    std::pair<std::string, std::size_t> source = parseChipsetLink(iss);
    std::pair<std::string, std::size_t> destination = parseChipsetLink(iss);

    existingComponent(source.first, destination.first);
    _links.push_back({{source.first, source.second}, {destination.first, destination.second}});
}


void nts::Parser::parseFile(const std::string &file)
{
    std::ifstream parseFile(file);
    std::string line;
    ParseState state = ParseState::NONE;
    if (!parseFile.is_open())
        throw nts::Error("File does not exist.");
    if (std::strstr(file.c_str(), ".nts") == nullptr)
        throw nts::Error("Invalid file: not a .nts file.");
    while (std::getline(parseFile, line)) {
        ltrim(rtrim(line));
        if (line == ".chipsets:" || std::strncmp(line.c_str(), ".chipsets:#", 11) == 0) {
            state = ParseState::CHIPSETS;
            continue;
        } else if (line == ".links:" || std::strncmp(line.c_str(), ".links:#", 8) == 0) {
            state = ParseState::LINKS;
            continue;
        }
        if (state == ParseState::CHIPSETS)
            parseChipset(line);
        else if (state == ParseState::LINKS)
            parseLink(line);
    }
    if (_chipsets.size() == 0) throw nts::Error("Invalid file: no chipsets");
    if (_links.size() == 0) throw nts::Error("Invalid file: no chipsets");
}

nts::listChipsetsType nts::Parser::getChipsets() const {
    return _chipsets;
}

std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> nts::Parser::getLinks() const {
    return _links;
}
