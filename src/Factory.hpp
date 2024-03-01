/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "IComponent.hpp"
#include "Circuit.hpp"

#include "OrComponent.hpp"
#include "NorComponent.hpp"
#include "AndComponent.hpp"
#include "NandComponent.hpp"
#include "NotComponent.hpp"
#include "XorComponent.hpp"
#include "LoggerComponent.hpp"

#include "Chipset4001.hpp"
#include "Chipset4011.hpp"
#include "Chipset4013.hpp"
#include "Chipset4017.hpp"
#include "Chipset4030.hpp"
#include "Chipset4040.hpp"
#include "Chipset4069.hpp"
#include "Chipset4071.hpp"
#include "Chipset4081.hpp"
#include "Chipset4008.hpp"
#include "Chipset4512.hpp"
#include "Chipset2716.hpp"
#include "Chipset4801.hpp"

#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "ClockComponent.hpp"

#include <memory>
#include <map>
#include <functional>

namespace nts {
    class Factory {
        public:
            class Error;

            Factory();

            std::unique_ptr<nts::IComponent> createComponent(const std::string &type);

        protected:
        private:
            std::map<std::string, std::function<std::unique_ptr<nts::IComponent>()>> _creators;
    };
}
#endif /* !FACTORY_HPP_ */
