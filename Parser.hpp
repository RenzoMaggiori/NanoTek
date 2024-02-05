/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <exception>
#include <fstream>
#include <iostream>
#include <deque>
#include <sstream>
#include <vector>
#include <utility>
#include "IComponent.hpp"

class Parser {
    public:
        enum class ParseState {
            NONE,
            CHIPSETS,
            LINKS
        };
        class Error: public std::exception
        {
            private:
                std::string _msg;
            public:
                Error(std::string msg): _msg(msg) {}
                const char *what() const noexcept override {
                    return _msg.c_str();
                }
        };

        Parser(const std::string &file);
        void parseFile(const std::string &file);
        void parseChipset(const std::string &line);
        void parseLink(const std::string &line);

        std::deque<std::pair<std::string, std::string>> getChipsets() const;
        std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> getLinks() const;

    protected:
        std::deque<std::pair<std::string, std::string>> _chipsets;
        std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> _links;
    private:
};

#endif /* !PARSER_HPP_ */
