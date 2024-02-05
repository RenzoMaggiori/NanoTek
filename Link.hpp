/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** Link
*/

#ifndef LINK_HPP_
#define LINK_HPP_

#include "IComponent.hpp"
#include <memory>

namespace nts
{
    class Link {
        public:
            Link(IComponent &inputComponent, IComponent &outputComponent, std::size_t outputPin, std::size_t inputPin);

        protected:
            std::shared_ptr<Tristate> _status;
            IComponent &_inputComponent;
            IComponent &_outputComponent;
        private:
    };
}

#endif /* !LINK_HPP_ */
