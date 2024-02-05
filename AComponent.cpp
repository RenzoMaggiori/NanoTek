/*
** EPITECH PROJECT, 2024
** nanoTek
** File description:
** AComponent
*/

#include "AComponent.hpp"
#include <memory>

std::map<std::size_t, std::shared_ptr<nts::Tristate>> &nts::AComponent::getPins() {
    return _pins;
}

std::map<std::size_t, std::shared_ptr<nts::Link>> &nts::AComponent::getLinks() {
    return _links;
}


void nts::AComponent::setLink(std::size_t pin, IComponent &component, std::size_t componentPin) {
   AComponent *componentCast = dynamic_cast<AComponent *>(&component);
    if (pin > _pins.size()) throw Error("Pin outside of bounds.");
    if (componentPin > componentCast->getPins().size()) throw Error("Component pin outside of bounds.");

    std::map<std::size_t, std::shared_ptr<Link>> componentLinks = componentCast->getLinks();
    std::shared_ptr<Link> newLink = std::make_shared<Link>(*this, component, componentPin, pin);

    _links[pin] = newLink;
    componentLinks[componentPin] = newLink;

    this->updateOutputPin();
}

nts::Tristate nts::AComponent::compute(std::size_t pin) {
    if (pin > _pins.size()) Error("Invalid pin.");
    return *(_pins[pin]);
}

