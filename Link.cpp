/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** Link
*/

#include "Link.hpp"
#include "AComponent.hpp"

nts::Link::Link(IComponent &inputComponent, IComponent &outputComponent, std::size_t outputPin, std::size_t inputPin)
: _outputComponent(outputComponent), _inputComponent(inputComponent)
{
    AComponent *inputComponentCast = dynamic_cast<AComponent *>(&inputComponent);
    AComponent *outputComponentCast = dynamic_cast<AComponent *>(&outputComponent);

    inputComponentCast->getPins()[inputPin] = outputComponentCast->getPins()[outputPin];
}