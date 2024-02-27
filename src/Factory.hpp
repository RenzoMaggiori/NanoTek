/*
** EPITECH PROJECT, 2024
** B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "IComponent.hpp"
#include "circuits/Circuit.hpp"

#include "components/elementary/OrComponent.hpp"
#include "components/elementary/NorComponent.hpp"
#include "components/elementary/AndComponent.hpp"
#include "components/elementary/NandComponent.hpp"
#include "components/elementary/NotComponent.hpp"
#include "components/elementary/XorComponent.hpp"
#include "components/elementary/LoggerComponent.hpp"

#include "components/chipsets/Chipset4001.hpp"
#include "components/chipsets/Chipset4011.hpp"
#include "components/chipsets/Chipset4013.hpp"
#include "components/chipsets/Chipset4030.hpp"
#include "components/chipsets/Chipset4040.hpp"
#include "components/chipsets/Chipset4069.hpp"
#include "components/chipsets/Chipset4071.hpp"
#include "components/chipsets/Chipset4081.hpp"
#include "components/chipsets/Chipset4008.hpp"
#include "components/chipsets/Chipset4512.hpp"
#include "components/chipsets/single/Chipset2716.hpp"
#include "components/chipsets/single/Chipset4801.hpp"

#include "components/special/InputComponent.hpp"
#include "components/special/OutputComponent.hpp"
#include "components/special/TrueComponent.hpp"
#include "components/special/FalseComponent.hpp"
#include "components/special/ClockComponent.hpp"

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
