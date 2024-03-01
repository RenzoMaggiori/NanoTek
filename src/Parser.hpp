/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <cstddef>
#include <deque>
#include <sstream>
#include <utility>


 ;
namespace nts {
    typedef std::pair<std::string, std::string> chipsetType;
    typedef std::deque<chipsetType> listChipsetsType;
    class Parser {
        public:
            enum class ParseState {
                NONE,
                CHIPSETS,
                LINKS
            };
            class Error;

            Parser(const std::string &file);
            void parseFile(const std::string &file);
            void parseChipset(const std::string &line);
            void parseLink(const std::string &line);

            std::deque<std::pair<std::string, std::string>> getChipsets() const;
            std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> getLinks() const;
            void existingComponent(std::string source, std::string destination);
        std::pair<std::string, std::size_t> parseChipsetLink(std::istringstream &iss);
        protected:
            std::deque<std::pair<std::string, std::string>> _chipsets;
            std::deque<std::pair<std::pair<std::string, size_t>, std::pair<std::string, size_t>>> _links;
        private:
    };
}
#endif /* !PARSER_HPP_ */
