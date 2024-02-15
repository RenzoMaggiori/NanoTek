/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <string>
#include <cstring>

namespace nts
{
    enum Tristate {
        Undefined = (-true),
        True = true,
        False = false
    };
    class Error: public std::exception {
        private:
            std::string _msg;
        public:
            Error(std::string msg): _msg(msg) {}
            const char *what() const noexcept override { return _msg.c_str(); }
    };
    class IComponent
    {
        public :
        virtual ~IComponent() = default;
        virtual void simulate(std::size_t tick) = 0;
        virtual nts::Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, nts::IComponent & other, std ::size_t otherPin) = 0;
};
}

#endif
